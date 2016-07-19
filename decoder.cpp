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

Node* Move(Node *node, bool b, bool &result) // result: true = not found and created; false = everything's fine;
{
	bool res = false;
	Node *ret;
	if (b)
	{
		if (res = (node->one == NULL))
		{
			node->one = new Node;
		}
		ret = node->one;
	}
	else
	{
		if (res = (node->zero == NULL))
		{
			node->zero = new Node;
		}
		ret = node->zero;
	}
	result = res;
	return ret;
}

void Create(Code code, Node *node, char index)
{
	Node *temp = node;
	if (code.Length == 0) return;
	bool usless;
	bool not_fin = true;
	bool go_there;
	for (int i = 0; not_fin; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i * 8 + j == code.Length)
			{
				not_fin = false;
				break;
			}
			go_there = (code.CodeItself[i] << j) & 0x80;
			temp = Move(temp, go_there, usless);
		}
	}
	temp->last = true;
	temp->encodedByte = index;
}

void decoder(FILE *Name, char* Address, int checkpassword)
{
	Code Codes[256];
	int length_of_table = 256;
	int length_of_name;
	int size = filesize(Name);
	char last_b;
	fread(&last_b, sizeof(char), 1, Name);
	if (checkpassword != last_b)
	{
		printf("File with password");
		return;
	}
	for (int i = 0; i < size; i++)
	{
		fread(&last_b, sizeof(char), 1, Name);
	}
	int last_a = (int)last_b;
	rewind(Name);
	fread(&last_b, sizeof(char), 1, Name);
	last_b = NULL;
	unsigned int checksum;
	fread(&checksum, 1, 4, Name);
	fread(&length_of_name, 1, 4, Name);
	length_of_name++;
	char *_Name = (char*)calloc(length_of_name, 1);
	fread(_Name, 1, length_of_name - 1, Name);
	char* Addres = (char*)malloc(strlen(Address) + 1);
	strcpy(Addres, Address);
	char* name = givethisname(Addres, _Name);
	free(Addres);
	if (name == NULL)
	{
		printf("Not enough memory");
		return;
	}
	FILE *f_2 = fopen(name, "wb");

	char tmp;
	for (int i = 0; i < 256; i++) { //parcing table

		fread(&(tmp), sizeof(char), 1, Name);
		Codes[i].Length = tmp;
		int length_of_bite = GetLengthInBytes(Codes[i].Length);
		fread(&(Codes[i].CodeItself), sizeof(char), length_of_bite, Name);
		length_of_table = length_of_table + length_of_bite;
	}

	length_of_code = size - 3 - length_of_name - length_of_table;
	length_of_code -= 5;
	left_bit = (length_of_code - 1) * 8 - last_a;
	//	left_bit--;
	bool bit;

	Node root, temp;
	root.last = false;

	for (int i = 0; i < 256; i++)
	{
		Create(Codes[i], &root, i);
	}

	f = Name;
	temp = root;
	bool err;
	byte_count = length_of_code / 100 * 5;
	while (_read(&bit) != false)
	{
		temp = *Move(&temp, bit, err);
		if (err)
		{
			//GENERAL ERROR! NOT FOUND BYTE COMBINATION! AAAAAAAAAAAAA!
			std::cout << "crap!";
			return;
		}
		if (temp.last)
		{
			fwrite(&(temp.encodedByte), 1, 1, f_2);
			temp = root;
		}
	}

	fclose(f_2);
	f_2 = fopen(name, "rb");

	unsigned int checksum2 = checkSummBuilder(f_2);
	if (checksum != checksum2)
	{
		printf("File was corrupted");
		fclose(f_2);
		free(name);
		return;
	}

	fclose(f_2);
	free(name);
}

bool _read(bool *c) //partition bytes to bits
{

	if (left_bit != 0)
	{
		if (bit_shift == 8)
		{
			byte_count++;
			byte_in_progress = progress_bar(byte_count, length_of_code);
			if (((int)byte_in_progress != (int)prev) && ((int)byte_in_progress % 5 == 0)) {
				printf("%d%%\n", (int)byte_in_progress);
			}
			prev = byte_in_progress;
			fread(&bite, sizeof(char), 1, f);//if byte is over, we begin the new
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
