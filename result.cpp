#define _CRT_SECURE_NO_WARNINGS
#include <sys/stat.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <malloc.h>

#define msk 0x000000FF

struct Code
{
	int Length;
	char CodeItself[32];
};

struct codeLine
{
	int codeLength;
	char codeItself[256];
};

struct frequencyLine
{
	char charItself[256];
	double charFrequency;
	int strLength;
};

struct codeByteLine
{
	int codeLength;
	char codeItself[32];
};

void bubbleSorter(frequencyLine *frequencyArrayPointer)
{
	frequencyLine tempFrequencyHolder;
	for (int cntFunctionSorter1 = 0; cntFunctionSorter1 < 256; cntFunctionSorter1++)
	{
		for (int cntFunctionSorter2 = cntFunctionSorter1 + 1; cntFunctionSorter2 < 256; cntFunctionSorter2++)
		{
			if (frequencyArrayPointer[cntFunctionSorter1].charFrequency < frequencyArrayPointer[cntFunctionSorter2].charFrequency)
			{
				tempFrequencyHolder = frequencyArrayPointer[cntFunctionSorter2];
				frequencyArrayPointer[cntFunctionSorter2] = frequencyArrayPointer[cntFunctionSorter1];
				frequencyArrayPointer[cntFunctionSorter1] = tempFrequencyHolder;
			}
		}
	}
}

void codeMaker(frequencyLine *frequencyArrayPointer, codeLine *codeLineArrayPointer, int elementCounter)
{
	int tempLen;
	int tempSymbol;
	int tempLen1;
	int codeTempLength = 0;
	tempLen = frequencyArrayPointer[elementCounter].strLength;
	tempLen1 = frequencyArrayPointer[elementCounter].strLength;
	int tempStr1 = frequencyArrayPointer[elementCounter - 1].strLength;
	int tempStr = frequencyArrayPointer[elementCounter - 1].strLength;
	//
	for (int cnt9 = 0; cnt9 < tempLen1; cnt9++)
	{
		tempSymbol = frequencyArrayPointer[elementCounter].charItself[cnt9];
		tempSymbol &= msk;
		frequencyArrayPointer[elementCounter - 1].charItself[tempStr1 + cnt9] = tempSymbol;
	}
	//
	for (int cntA = 0; cntA < tempLen; cntA++)
	{
		tempSymbol = frequencyArrayPointer[elementCounter].charItself[cntA];
		tempSymbol &= msk;
		codeTempLength = codeLineArrayPointer[tempSymbol].codeLength;
		codeLineArrayPointer[tempSymbol].codeItself[255 - codeTempLength] = '0';
		codeLineArrayPointer[tempSymbol].codeLength++;
	}
	for (int cntB = 0; cntB < tempStr; cntB++)
	{
		tempSymbol = frequencyArrayPointer[elementCounter - 1].charItself[cntB];
		tempSymbol &= msk;
		codeTempLength = codeLineArrayPointer[tempSymbol].codeLength;
		codeLineArrayPointer[tempSymbol].codeItself[255 - codeTempLength] = '1';
		codeLineArrayPointer[tempSymbol].codeLength++;
	}
	//

	//
	frequencyArrayPointer[elementCounter - 1].strLength += frequencyArrayPointer[elementCounter].strLength;
	frequencyArrayPointer[elementCounter].strLength = 0;
	frequencyArrayPointer[elementCounter - 1].charFrequency += frequencyArrayPointer[elementCounter].charFrequency;
	frequencyArrayPointer[elementCounter].charFrequency = 0;
	bubbleSorter(frequencyArrayPointer);
}

void swapperFunction(codeLine *codeLineArrayPointer)
{
	int tempSwapLength = 0;
	int tempLn1 = 0;
	char tempCharHolder1;
	for (int cntZ = 0; cntZ < 256; cntZ++)
	{
		tempSwapLength = codeLineArrayPointer[cntZ].codeLength;
		if (tempSwapLength != 0)
		{
			tempLn1 = tempSwapLength;
			for (int cntY = 0; cntY < tempSwapLength; cntY++)
			{
				tempCharHolder1 = codeLineArrayPointer[cntZ].codeItself[256 - tempLn1];
				codeLineArrayPointer[cntZ].codeItself[256 - tempLn1] = 0;
				codeLineArrayPointer[cntZ].codeItself[cntY] = tempCharHolder1;
				tempLn1--;
			}
		}
	}
}

char GETMYCHAR(char* fromhere)
{
	char res = 0;
	for (int i = 0; i < 8; i++)
	{
		res <<= 1;
		res += (fromhere[i] == '1');
	}
	return res;
}

void byteMaker(codeByteLine* codeByteLinePointer, codeLine *codeLineArrayPointer)
{

	int tempLn = 0;
	for (int cntC = 0; cntC < 256; cntC++)
	{
		for (int i = 0; i < 32; i++)
		{
			codeByteLinePointer[cntC].codeItself[i] = GETMYCHAR(&(codeLineArrayPointer[cntC].codeItself[8 * i]));
		}
		codeByteLinePointer[cntC].codeLength = codeLineArrayPointer[cntC].codeLength;

	}
}

int huffFunction(frequencyLine *frequencyArrayPointer)
{
	struct codeLine codeLineArray[256] = { 0 };
	struct codeByteLine codeByteLineArray[256] = { 0 };
	int elementCounter = 0;
	double blockAmount = 0;
	codeLine *codeLineArrayPointer = codeLineArray;
	codeByteLine *codeByteLinePointer = codeByteLineArray;
	for (int cnt2 = 0; cnt2 < 256; cnt2++)
	{
		if (frequencyArrayPointer[cnt2].charFrequency != 0)
		{
			elementCounter++;
			blockAmount += frequencyArrayPointer[cnt2].charFrequency;
		}
	}

	for (int cnt3 = 0; cnt3 < 256; cnt3++)
	{
		frequencyArrayPointer[cnt3].charFrequency /= blockAmount;
		frequencyArrayPointer[cnt3].strLength++;
	}

	bubbleSorter(frequencyArrayPointer);
	int backUpCounter = elementCounter;
	elementCounter--;

	if (backUpCounter > 1)
	{
		while (elementCounter != 0)
		{
			codeMaker(frequencyArrayPointer, codeLineArrayPointer, elementCounter);
			elementCounter--;
		}



		swapperFunction(codeLineArrayPointer);


		byteMaker(codeByteLinePointer, codeLineArrayPointer);
	}

	else
	{
		char tempSingleChar = frequencyArrayPointer[0].charItself[0];
		codeByteLinePointer[tempSingleChar].codeItself[0] = 128;
		codeByteLinePointer[tempSingleChar].codeLength = 1;
	}

	int arrayAddress = (int)codeByteLinePointer;

	return arrayAddress;
}

int huffCenterLinkFunction(char* filenameString)
{
	FILE *fr = fopen(filenameString, "rb");
	char character;
	int tempAddress;
	int currentChar;

	struct frequencyLine frequencyArray[256] = { 0 };
	fread(&character, 1, 1, fr);
	frequencyLine *frequencyArrayPointer = frequencyArray;
	while (!feof(fr))
	{
		currentChar = character;

		currentChar &= msk;
		frequencyArray[currentChar].charItself[0] = currentChar;
		frequencyArray[currentChar].charFrequency++;
		fread(&character, 1, 1, fr);
	}
	tempAddress = huffFunction(frequencyArrayPointer);
	return tempAddress;
}


int GetLengthInBytes(int BitCount)
{
	return (BitCount / 8) + ((BitCount % 8 != 0) ? 1 : 0);
}

struct Writer
{
	bool buf[513];
	int bufLength;
	FILE *fw;
	Writer(FILE *_fw)
	{
		fw = _fw;
		bufLength = 0;
	}
	void Add(bool b)
	{
		buf[bufLength++] = b;
	}
	void Add(char a, int length)
	{
		if (length > 8) length = 8;
		char _mask = 1;
		int cnt = 7;
		char mask = _mask << cnt;
		for (int i = 0; i < length; i++, --cnt, mask = _mask << cnt)
		{
			Add((a & mask) != 0);
		}
	}
	void Add(Code a)
	{
		int t = GetLengthInBytes(a.Length);
		for (int i = 0; i < t; i++, a.Length -= 8)
		{
			Add(a.CodeItself[i], a.Length);
		}
	}
	void Left()
	{
		for (int i = 8; i < bufLength; i++)
		{
			buf[i - 8] = buf[i];
		}
		bufLength -= 8;
	}
	void Print()
	{
		char tmp;
		while (bufLength >= 8)
		{
			tmp = GetFirstChar();
			Left();
			fwrite(&tmp, 1, 1, fw);
		}
	}
	char GetFirstChar()
	{
		char tmp = 0;
		for (int i = 0; i < 8; i++)
		{
			tmp <<= 1;
			tmp += (buf[i] ? 1 : 0);
		}
		return tmp;
	}
	char PrintEnd()
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

void CreateCompressedFile(char* FileToCompress, char* NameOfCompressedFile, int pointer)
{
	FILE *fw = fopen(NameOfCompressedFile, "wb");
	FILE *fr = fopen(FileToCompress, "rb");
	Code* Codes = (Code*)pointer;
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
		int tm = c;
		tm &= msk;

		writer.Add(Codes[tm]);
		writer.Print();
		fread(&c, 1, 1, fr);
	}
	c = writer.PrintEnd();
	fwrite(&c, 1, 1, fw);
	fclose(fr);
	fclose(fw);
}

char bite;
int left_bit = 0;
int bit_shift = 8;

long int filesize(FILE *fp)
{
	long int save_pos, size_of_file;

	save_pos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	size_of_file = ftell(fp);
	fseek(fp, save_pos, SEEK_SET);
	return(size_of_file);
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
	char mask = 0x01;
	int sdvig = 7 - (code.Length % 8);
	mask <<= sdvig;
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

void decoder(char* Name);
bool _read(bool *c);
FILE *f;
void decoder(char* Name)
{
	char _Name[256];
	Code Codes[256];
	int length_of_table = 256;
	f = fopen(Name, "rb");

	int size = filesize(f);
	char last_b;
	fread(&last_b, sizeof(char), 1, f);

	for (int i = 0; i < size; i++)
	{
		fread(&last_b, sizeof(char), 1, f);
	}
	int last_a = (int)last_b;
	rewind(f);
	fread(_Name, sizeof(char), 256, f);
	FILE *f_2 = fopen(_Name, "wb");
	char tmp;
	for (int i = 0; i < 256; i++) { //parcing table

		fread(&(tmp), sizeof(char), 1, f);
		Codes[i].Length = tmp;
		int length_of_bite = GetLengthInBytes(Codes[i].Length);
		fread(&(Codes[i].CodeItself), sizeof(char), length_of_bite, f);
		length_of_table = length_of_table + length_of_bite;
	}

	int length_of_code = size - 256 - length_of_table;

	left_bit = (length_of_code - 1) * 8 - last_a;

	bool bit;

	Code buf;
	for (int i = 0; i < 32; i++)
	{
		buf.CodeItself[i] = 0;

	}

	Clear(buf);



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
}

bool _read(bool *c) //partition bytes to bits 
{

	if (left_bit != 0)
	{
		if (bit_shift == 8)
		{
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
int isitreal(char* Name)
{
	FILE*f;
	if ((f = fopen(Name, "rb")) == NULL)
	{
		return 0;
	}
	else
	{
		fclose(f);
		return 1;
	}
}

int canitreal(char* Name)
{
	FILE*f;
	if ((f = fopen(Name, "wb")) == NULL)
	{
		return 0;
	}
	else
	{
		fclose(f);
		return 1;
	}
}

int main(int argc, char * argv[])
{
	if ((argc == 2) && (strcmp("\h", argv[1]) == 0))
	{
		printf("Key -c to compress file.\nKey -d to decompress file.\nexample:-c D:\\test.txt\nYou can choose where to save the compressed file if after you specify the start directory, specify the following\nExample:-c D:\\test.txt D:\\example\\Test.txd\n");
		return 0;
	}
	else
	{
		if (strcmp("-c", argv[1]) == 0)
		{
			if (argc == 4)
			{
				int adres;
				if (isitreal(argv[2]) == 0)
				{
					printf("Cannot open file\n");
					return 0;
				}
				if (canitreal(argv[3]) == 0)
				{
					printf("Cannot create file\n");
					return 0;
				}
				adres = huffCenterLinkFunction(argv[2]);
				CreateCompressedFile(argv[2], argv[3], adres);
				return 0;
			}
			if (argc == 3)
			{
				char* name = argv[2];
				char* nameb = { "r" };
				char namebuf[256] = { "" };
				strcat(namebuf, name);
				strcat(namebuf, nameb);
				if (isitreal(name) == 0)
				{
					printf("Cannot open file\n");
					return 0;
				}
				if (canitreal(namebuf) == 0)
				{
					printf("Cannot create file\n");
					return 0;
				}
				int adres;
				adres = huffCenterLinkFunction(name);
				CreateCompressedFile(name, namebuf, adres);
				return 0;
			}
		}
		else
		{
			if (strcmp(argv[1], "-d") == 0)
			{
				if (isitreal(argv[2]) == 0)
				{
					printf("Cannot open file\n");
					return 0;
				}
				decoder(argv[2]);
				return 0;
			}
			else
			{
				printf("Incorrect key\n");
				return 0;
			}
		}
	}
	printf("Problem with arguments\nKey \\h to help\nkey -c to compress file.\nKey -d to decompress file.\nExample:-c D:\\test.txt\nYou can choose where to save the compressed file if after you specify the start directory, specify the following\nExample:-c D:\\test.txt D:\\example\\Test.txd\n");
	return 0;
}
