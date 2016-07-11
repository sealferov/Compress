#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>

struct codeLine // структура для длины кодов и самих кодов (строка "таблицы")
{
	int codeLength; // длина
	char codeItself[256]; // сам код
};

struct frequencyLine // структура для частоты блоков и самих блоков
{
	char charItself[256]; // блок (символ)
	double charFrequency; // частота повторения блока
	int strLength;
};

struct codeByteLine
{
	int codeLength;
	char codeItself[32];
};

void bubbleSorter(frequencyLine *frequencyArrayPointer) // функция сортировки пузырьком
{
	frequencyLine tempFrequencyHolder;
	for (int cntFunctionSorter1 = 0; cntFunctionSorter1 < 256; cntFunctionSorter1++)
	{
		for(int cntFunctionSorter2 = cntFunctionSorter1 + 1; cntFunctionSorter2 < 256; cntFunctionSorter2++)
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
	char tempSymbol;
	int tempLen1;
	int codeTempLength = 0;
	tempLen = frequencyArrayPointer[elementCounter].strLength;
	tempLen1 = frequencyArrayPointer[elementCounter].strLength;
	int tempStr1 = frequencyArrayPointer[elementCounter-1].strLength;
	int tempStr = frequencyArrayPointer[elementCounter-1].strLength;
	//
	for (int cntA = 0; cntA < tempLen; cntA++)
	{
		tempSymbol = frequencyArrayPointer[elementCounter].charItself[cntA];
		codeTempLength = codeLineArrayPointer[tempSymbol].codeLength;
		codeLineArrayPointer[tempSymbol].codeItself[255-codeTempLength] = '0';
		codeLineArrayPointer[tempSymbol].codeLength++;
	}
	for(int cntB = 0; cntB < tempStr; cntB++)
	{
		tempSymbol = frequencyArrayPointer[elementCounter-1].charItself[cntB];
		codeTempLength = codeLineArrayPointer[tempSymbol].codeLength;
		codeLineArrayPointer[tempSymbol].codeItself[255-codeTempLength] = '1';
		codeLineArrayPointer[tempSymbol].codeLength++;
	}
	//
	for (int cnt9 = 0; cnt9 < tempLen1; cnt9++)
	{
		tempSymbol = frequencyArrayPointer[elementCounter].charItself[cnt9];
		frequencyArrayPointer[elementCounter-1].charItself[tempStr1 + cnt9] = tempSymbol;
	}
	//
	frequencyArrayPointer[elementCounter-1].strLength += frequencyArrayPointer[elementCounter].strLength;
	frequencyArrayPointer[elementCounter].strLength = 0;
	frequencyArrayPointer[elementCounter-1].charFrequency += frequencyArrayPointer[elementCounter].charFrequency;
	frequencyArrayPointer[elementCounter].charFrequency = 0;
	bubbleSorter(frequencyArrayPointer);
}

void byteMaker(codeByteLine* codeByteLinePointer,  codeLine *codeLineArrayPointer)
{
	char* tempCode; // указатель на строку байтов для переделывания
	int tempLn = 0; // длина "старого кода"
	char bite_f = 0; // переменная в которой копятся биты
	int tempCnt; // переменаая для формулы счетчика
	int flagZero = 0; // флаг нулевой длины, т.е. в байт можно сразу писать NULL
	for (int cntC = 0; cntC < 256; cntC++)
	{
		tempLn = codeLineArrayPointer[cntC].codeLength;
		tempCode = codeLineArrayPointer[cntC].codeItself;
		for (int cntD = 31; cntD >= 0; cntD--) // цикл по байтам
		{
			for (int cntE = 7; cntE >= 0;cntE--)  // цикл по битам
			{ 
				tempCnt = 8 * cntD + cntE; // формула счетчка
				if (tempLn != 0)
				{
				
					bite_f = bite_f | (tempCode[tempCnt]); 
					bite_f <<= 1;
				}
				else
					flagZero++;
			}
			if (flagZero == 0)
			{
				codeByteLinePointer[cntC].codeItself[cntD] = bite_f; // записываю получившийся байт в соотв. ячейку
				codeByteLinePointer[cntC].codeLength = tempLn; // 
			}
			else
				codeByteLinePointer[cntC].codeItself[cntD] = NULL;
			flagZero = 0;
			bite_f = 0;
		}
		

		//printf("%c \n", codeByteLinePointer[cntC].codeItself[31]);
		
	}
}

int huffFunction(char character)
{
	struct frequencyLine frequencyArray[256] = {0}; // массив структур частот
	struct codeLine codeLineArray[256] = {0}; // массив структур с длиной кодов и самими кодами
	struct codeByteLine codeByteLineArray[256] = {0};
	int elementCounter = 0; // кол-во типов блоков
	char currentChar; // текущий символ
	double blockAmount = 0; // всего блоков
	frequencyLine *frequencyArrayPointer = frequencyArray; // указатель на массив структур частот
	codeLine *codeLineArrayPointer = codeLineArray; //указатель на массив структур кодов
	codeByteLine *codeByteLinePointer = codeByteLineArray;

	currentChar = character;
	frequencyArray[currentChar].charItself[0] = currentChar;
	frequencyArray[currentChar].charFrequency++;

	for (int cnt2 = 0; cnt2 < 256; cnt2++) // узнаем кол-во блоков
	{
		if (frequencyArray[cnt2].charFrequency != 0)
		{
			elementCounter++;
			blockAmount += frequencyArray[cnt2].charFrequency;
		}
	}
	
	for (int cnt3 = 0; cnt3 < 256; cnt3++) // получаем отношение частот к кол-ву блоков
	{
		frequencyArray[cnt3].charFrequency /= blockAmount;
		frequencyArray[cnt3].strLength++;
	}

	bubbleSorter(frequencyArrayPointer); // вызов функции сортировки
	int backUpCounter = elementCounter;
	
	while(elementCounter != 0)
	{
		codeMaker(frequencyArrayPointer, codeLineArrayPointer, elementCounter);
		elementCounter--;
	}
	
	byteMaker(codeByteLinePointer, codeLineArrayPointer);

	int arrayAddress = &codeByteLinePointer;

	return arrayAddress;
}
// это связующая функция. Она будет вызываться первой из моего участка, а затем вызывать главную функцию этого участка. В эту link-функцию надо будет подавать имя файла.
int huffCenterLinkFunction(char* filenameString)
{
	FILE *fr = fopen(filenameString, "rb"); // открываем и читаем
	char character; // символ
	int tempAddress;
	while(character = fgetc(fr) != EOF)
	{
		tempAddress = huffFunction(character);
	}
	return tempAddress;
}