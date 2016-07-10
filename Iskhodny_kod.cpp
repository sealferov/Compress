#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

#define N 8

struct Code //структура, котора€ хранит длину кода из битов и сам код. назовем ее  од
{
	int Length; //длина кода в битах
	char CodeItself[32]; //сам код
};

int GetLengthInBytes(int BitCount) //возвращает количество байт, требуемое дл€ хранени€ данного числа бит
{
	return (BitCount / 8) + ((BitCount % 8 != 0) ? 1 : 0);
}

struct Writer //структура, позвол€юща€ выводить коды в файл
{
	bool buf[513]; //буфер "битов"
	int bufLength = 0; //длина заполненного буфера (в "битах")
	FILE *fw; //указатель на файл, куда будем писать
	Writer(FILE *_fw) //конструктор структуры
	{
		fw = _fw;
	}
	void Add(bool b) //добавление "бита" в буфер (длина заполненного буфера соответственно увеличиваетс€ на 1)
	{
		buf[bufLength++] = b;
	}
	void Add(char a, int length) //добавление в буфер одного байта или его части (определ€етс€ переменной length - числом добавл€емых бит)
		//если length >= 8, то мы добавл€ем целый бит
	{
		if (length > 8) length = 8;
		char mask = 1;
		mask <<= 7;
		for (int i = 0; i < length; i++, mask>>=1) //тут мы за счет маски смотрим, чему равны определенные биты этого байта и добавл€ем их в буфер по очереди
		{
			Add((a & mask)!=0);
		}
	}
	void Add(Code a) //добавление  ода в буфер
	{
		int t = GetLengthInBytes(a.Length); //смотрим, сколько байт действительно участвует в  оде
		for (int i = 0; i < t; i++, a.Length -= 8) //проходимс€ по каждому из этих байт и добавл€ем их в буфер
		{
			Add(a.CodeItself[i], a.Length);
		}
	}
	void Left() //сдвиг буфера на один байт влево
	{
		for (int i = 8; i < bufLength; i++)
		{
			buf[i - 8] = buf[i];
		}
		bufLength -= 8;
	}
	void Print() //вывод и сброс (сдвигом влево) части буфера (части максимальной длины, кратной восьми)
	{
		char tmp;
		while (bufLength>=8)
		{
			tmp = GetFirstChar();
			Left();
			fwrite(&tmp, 1, 1, fw);
		}
	}
	char GetFirstChar() //получение самого левого байта буфера
	{
		char tmp = 0;
		for (int i = 0; i < 8; i++)
		{
			tmp <<= 1;
			tmp+=buf[i];
		}
		return tmp;
	}
	char PrintEnd() //вывод всего, что осталось в буфере в конце (забив остаток нул€ми)
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

void CreateCompressedFile(char* FileToCompress, char* NameOfCompressedFile, Code Codes[256]) //функци€ создани€ сжатого файла
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
