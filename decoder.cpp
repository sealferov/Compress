// ConsoleApplication8.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include <sys/stat.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

static char bite;
static int left_bit = 0;
static int bit_shift = 8;
FILE *f = fopen("D://test1.txt", "rb");

long int filesize(FILE *fp)
{
	long int save_pos, size_of_file;

	save_pos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	size_of_file = ftell(fp);
	fseek(fp, save_pos, SEEK_SET);
	return(size_of_file);
}
struct Code //ñòðóêòóðà, êîòîðàÿ õðàíèò äëèíó êîäà èç áèòîâ è ñàì êîä. íàçîâåì åå Êîä
{
	int Length; //äëèíà êîäà â áèòàõ
	char CodeItself[32]; //ñàì êîä
};
int GetLengthInBytes(int BitCount) //âîçâðàùàåò êîëè÷åñòâî áàéò, òðåáóåìîå äëÿ õðàíåíèÿ äàííîãî ÷èñëà áèò
{
	return (BitCount / 8) + ((BitCount % 8 != 0) ? 1 : 0);
}

void Clear(Code &a)
{
	int tmp = GetLengthInBytes(a.Length);
	for (int i = 0; i < tmp; i++)
	{
		a.CodeItself[i] = 0;
	}
	a.Length = 0;
}
void Add(Code &code, bool b)
{
	char mask = 0x80;
	int sdvig = 8 - (code.Length % 8);
	if (sdvig == 8) sdvig = 0;
	mask >>= sdvig;
	if (b)
	{
		code.CodeItself[code.Length / 8] |= mask;
	}
	else
	{
		code.CodeItself[code.Length / 8] &= ~mask;
	}
	code.Length++;
}
bool _Equal(Code a, Code b)
{
	if (a.Length != b.Length) return false; else
	{
		int tmp = GetLengthInBytes(a.Length);
		for (int i = 0; i < tmp; i++)
		{
			if (a.CodeItself[i] != b.CodeItself[i]) return false;
		}
		return true;
	}
}





void decoder();
bool _read(bool *c);

void main()
{
	decoder();
}



void decoder() {

	Code Codes[256];
	int length_of_table = 256;

	char  Name[256];
	int size = filesize(f);
	char last_b;
	fread(&last_b, sizeof(char), 1, f);

	for (int i = 0; i < size; i++) {
		fread(&last_b, sizeof(char), 1, f);


	}
	int last_a = (int)last_b;



	rewind(f);

	fread(Name, sizeof(char), 256, f);
	char tmp;
	for (int i = 0; i < 256; i++) {

		fread(&(tmp), sizeof(char), 1, f);
		Codes[i].Length = tmp;
		int length_of_bite = GetLengthInBytes(Codes[i].Length);
		fread(&(Codes[i].CodeItself), sizeof(char), length_of_bite, f);
		length_of_table = length_of_table + length_of_bite;
	}


	int length_of_code = size - sizeof(Name) - length_of_table;


	left_bit = (length_of_code - 1) * 8 - last_a;

	bool bit;



	FILE *f_2 = fopen("D://Test2.txt", "wb");

	Code buf;
	for (int i = 0; i < 32; i++)
	{
		buf.CodeItself[i] = 0;

	}

	buf.Length = 0;
	while (_read(&bit) != false)
	{
		Add(buf, bit);
		for (int i = 0; i < 256; i++)
		{
			if (_Equal(buf, Codes[i]))
			{
				Clear(buf);
				char temp = i;
				fwrite(&temp, sizeof(char), 1, f_2);
				break;
			}
		}

	}

	fclose(f);
}

bool _read(bool *c)
{

	if (left_bit != 0)
	{
		if (bit_shift == 8)
		{
			fread(&bite, sizeof(char), 1, f);
			bit_shift = 0;
		}

		*c = bite & 0x80;
		bite <<= 1;
		bit_shift++;
		left_bit--;
		return true;
	}
	else
		return false;

}

