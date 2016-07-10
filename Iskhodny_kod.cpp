#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

#define N 8

struct Code //���������, ������� ������ ����� ���� �� ����� � ��� ���. ������� �� ���
{
	int Length; //����� ���� � �����
	char CodeItself[32]; //��� ���
};

int GetLengthInBytes(int BitCount) //���������� ���������� ����, ��������� ��� �������� ������� ����� ���
{
	return (BitCount / 8) + ((BitCount % 8 != 0) ? 1 : 0);
}

struct Writer //���������, ����������� �������� ���� � ����
{
	bool buf[513]; //����� "�����"
	int bufLength = 0; //����� ������������ ������ (� "�����")
	FILE *fw; //��������� �� ����, ���� ����� ������
	Writer(FILE *_fw) //����������� ���������
	{
		fw = _fw;
	}
	void Add(bool b) //���������� "����" � ����� (����� ������������ ������ �������������� ������������� �� 1)
	{
		buf[bufLength++] = b;
	}
	void Add(char a, int length) //���������� � ����� ������ ����� ��� ��� ����� (������������ ���������� length - ������ ����������� ���)
		//���� length >= 8, �� �� ��������� ����� ���
	{
		if (length > 8) length = 8;
		char mask = 1;
		mask <<= 7;
		for (int i = 0; i < length; i++, mask>>=1) //��� �� �� ���� ����� �������, ���� ����� ������������ ���� ����� ����� � ��������� �� � ����� �� �������
		{
			Add((a & mask)!=0);
		}
	}
	void Add(Code a) //���������� ���� � �����
	{
		int t = GetLengthInBytes(a.Length); //�������, ������� ���� ������������� ��������� � ����
		for (int i = 0; i < t; i++, a.Length -= 8) //���������� �� ������� �� ���� ���� � ��������� �� � �����
		{
			Add(a.CodeItself[i], a.Length);
		}
	}
	void Left() //����� ������ �� ���� ���� �����
	{
		for (int i = 8; i < bufLength; i++)
		{
			buf[i - 8] = buf[i];
		}
		bufLength -= 8;
	}
	void Print() //����� � ����� (������� �����) ����� ������ (����� ������������ �����, ������� ������)
	{
		char tmp;
		while (bufLength>=8)
		{
			tmp = GetFirstChar();
			Left();
			fwrite(&tmp, 1, 1, fw);
		}
	}
	char GetFirstChar() //��������� ������ ������ ����� ������
	{
		char tmp = 0;
		for (int i = 0; i < 8; i++)
		{
			tmp <<= 1;
			tmp+=buf[i];
		}
		return tmp;
	}
	char PrintEnd() //����� �����, ��� �������� � ������ � ����� (����� ������� ������)
	{
		char c = 0;
		while (bufLength % 8 != 0)
		{
			Add(0);
			c++;
		}
		Print();
		return c;
	}
	
};

void CreateCompressedFile(char* FileToCompress, char* NameOfCompressedFile, Code Codes[256]) //������� �������� ������� �����
{
	FILE *fw = fopen(NameOfCompressedFile, "wb");
	FILE *fr = fopen(FileToCompress, "rb");
	fwrite(FileToCompress, 1, 256, fw);
	char tmp;
	int powN = 256;
	for (int i = 0; i < powN; i++)
	{
		tmp = (char)Codes[i].Length;
		fwrite(&tmp, 1, 1, fw);
		tmp = GetLengthInBytes(Codes[i].Length);
		fwrite(Codes[i].CodeItself, 1, GetLengthInBytes(Codes[i].Length), fw);
	}
	char c;
	Writer writer(fw);
	fread(&c, 1, 1, fr);
	while (!feof(fr))
	{
		writer.Add(Codes[c]);
		writer.Print();
		fread(&c, 1, 1, fr);
	}
	c = writer.PrintEnd();
	fwrite(&c, 1, 1, fw);
	fclose(fr);
	fclose(fw);
}

int main()
{
	Code Codes[256];
	for (int i = 0; i < 256; i++)
	{
		Codes[i].Length = 0;
	}
	Codes['1'].Length = 1;
	Codes['1'].CodeItself[0] = 1;
	Codes['1'].CodeItself[0] <<= 7;
	char a[256] = "e://test.txt";
	char b[256] = "e://test1.txt";
	CreateCompressedFile(a, b, Codes);
	return 0;
}
