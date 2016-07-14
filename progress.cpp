#define _CRT_SECURE_NO_WARNINGS
#include <sys/stat.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <stdint.h>
#include <malloc.h>

#define msk 0x000000FF

// crc-32
unsigned int checkSummBuilder(char * filenamePointer)
{
	const uint_least32_t crc32Table[256] = {
		0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
		0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
		0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
		0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
		0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
		0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
		0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
		0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
		0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
		0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
		0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
		0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
		0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
		0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
		0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
		0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
		0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
		0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
		0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
		0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
		0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
		0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
		0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
		0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
		0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
		0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
		0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
		0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
		0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
		0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
		0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
		0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
		0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
		0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
		0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
		0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
		0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
		0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
		0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
		0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
		0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
		0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
		0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
		0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
		0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
		0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
		0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
		0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
		0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
		0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
		0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
		0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
		0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
		0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
		0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
		0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
		0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
		0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
		0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
		0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
		0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
		0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
		0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
		0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
	};
	uint_least32_t crc = 0xFFFFFFFF; // начальное значение
	char currentSym; // текущий символ
	FILE *fr = fopen(filenamePointer, "rb");
	fread(&currentSym, 1, 1, fr);

	while (!feof(fr))
	{
		crc = (crc >> 8) ^ crc32Table[(crc ^ currentSym) & 0xFF]; //по 8 бит за цикл строим сумму с помощью тпблицы и идем дальше
		fread(&currentSym, 1, 1, fr);
	}

	unsigned int returnValue = crc ^ 0xFFFFFFFF; // возвращаемое значение в виде unsigned
	return returnValue;
}

char* givethisname(char* name, char* nameoffile)
{
	int d = strlen(name);
	int c;
	for (int i = 0; i < d; i++)
	{
		if (name[d - 1 - i] == '\\')
		{
			c = d - i - 1;
			break;
		}
	}
	char * result = (char*)malloc(strlen(name) + strlen(nameoffile));
	if (result == NULL)
	{
		return NULL;
	}
	strncpy(result, name, c + 1);
	result[c + 1] = '\0';
	strcat(result, nameoffile);
	FILE* f;
	if ((f = fopen(result, "wb")) == NULL)
	{
		return NULL;
	}
	else
	{
		fclose(f);
		return result;
	}	
}

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

void CreateCompressedFile(FILE* PointerToCompressingFile, char* NameOfCompressingFile, FILE *PointerToCompressedFile, int pointer) //ôóíêöèÿ ñîçäàíèÿ ñæàòîãî ôàéëà
{
	FILE *fw = PointerToCompressedFile;
	FILE *fr = PointerToCompressingFile;
	Code* Codes = (Code*)pointer;
	//fwrite encryption byte
	//fwrite hash-summ
	int slen = strlen(NameOfCompressingFile);
	fwrite(&slen, 4, 1, fw);
	fwrite(NameOfCompressingFile, 1, slen + 1, fw);
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

void decoder(FILE *Name, char* Address)
{
	Code Codes[256];
	int length_of_table = 256;
	int length_of_name;
	int size = filesize(Name);
	char last_b;
	fread(&last_b, sizeof(char), 1, Name);
	if (last_b == '1') {
		//there is password
	}
	for (int i = 0; i < size; i++)
	{
		fread(&last_b, sizeof(char), 1, Name);
	}
	int last_a = (int)last_b;
	rewind(Name);
	fread(&last_b, sizeof(char), 1, Name);
	last_b = NULL;
	char checksum;
	fread(&checksum, 1, 1, Name);
	fread(&length_of_name, 1, 4, Name);
	char *_Name = (char*)malloc(length_of_name);
	fread(_Name, 1, length_of_name, Name);
	char* name = givethisname(Address, _Name);
	if (name == NULL)
	{
		printf("Not enough memory");
		return;
	}
	FILE *f_2 = fopen(name, "wb");
	free(name);
	char tmp;
	for (int i = 0; i < 256; i++) { //parcing table

		fread(&(tmp), sizeof(char), 1, Name);
		Codes[i].Length = tmp;
		int length_of_bite = GetLengthInBytes(Codes[i].Length);
		fread(&(Codes[i].CodeItself), sizeof(char), length_of_bite, Name);
		length_of_table = length_of_table + length_of_bite;
	}

	int length_of_code = size - 5 - length_of_name - length_of_table;

	left_bit = (length_of_code - 1) * 8 - last_a;

	bool bit;

	Code buf;
	for (int i = 0; i < 32; i++)
	{
		buf.CodeItself[i] = 0;

	}

	Clear(buf);

	f = Name;

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
	fclose(f_2);
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

char* strcut(char* example)
{
	int d = strlen(example);
	int c;
	for (int i = 0; i < strlen(example); i++)
	{
		if (example[d - 1 - i] == '\\')
		{
			c = d - i - 1;
			break;
		}
	}
	int l = 0;
	char * result = (char*)malloc(d - c);
	if (result == NULL)
	{
		return NULL;
	}
	for (int i = c; i < d; i++)
	{
		result[l] = example[i + 1];
		l++;
	}
	return result;
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
				FILE *f;
				if ((f = fopen(argv[2], "rb")) == NULL)
				{
					printf("Cannot open file\n");
					return 0;
				}
				if (canitreal(argv[3]) == 0)
				{
					printf("Cannot create file\n");
					return 0;
				}
				char* nameoffile = strcut(argv[2]);
				if (nameoffile == NULL)
				{
					printf("Not enough memory");
				}
				//adres = huffCenterLinkFunction(f);
				//rewind(f);
				//FILE*fn;
				//CreateCompressedFile(f, nameoffile, fn=fopen(argv[2],"wb"), adres);
				//free(nameoffile);
				fclose(f);
				return 0;
			}
			if (argc == 3)
			{
				char* name = argv[2];
				char* nameb = { ".cmp" };
				char namebuf[256] = { "" };
				FILE *f;
				if ((f = fopen(name,"rb")) == NULL)
				{
					printf("Cannot open file\n");
					return 0;
				}
				strcat(namebuf, name);
				strcat(namebuf, nameb);
				char* nameoffile = strcut(argv[2]);
				if (nameoffile == NULL)
				{
					printf("Not enough memory");
				}
				if (canitreal(namebuf) == NULL)
				{
					printf("Cannot create file\n");
					return 0;
				}
				int adres;
				//adres = huffCenterLinkFunction(f);
				//rewind(f);
				FILE*fn;
				CreateCompressedFile(f, nameoffile, fn = fopen(argv[2], "wb"), adres);
				//CreateCompressedFile(f, nameoffile, namebuf, adres);
				free(nameoffile);
				fclose(f);
				return 0;
			}
		}
		else
		{
			if (strcmp(argv[1], "-d") == 0)
			{
				FILE *f;
				if ((f=fopen(argv[2],"rb")) == 0)
				{
					printf("Cannot open file\n");
					return 0;
				}
				decoder(f,argv[2]);
				return 0;
				fclose(f);
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