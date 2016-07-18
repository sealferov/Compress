#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>


// Byte changer function
char encryptorMain(char tempChar, char tempLetter)
{
	for (int cntW = 0; cntW < 8; cntW++)
	{
		tempLetter << 1;
		tempChar << 1;
		tempChar ^= tempLetter;
	}
	return tempChar;
}


// Encryption/Decryption function
void endecryptor(char *passwordString, char *filenameString)
{
	int passwordLength = strlen(passwordString); // длина пароля
	char currentSym; // текущий символ
	int passwordPosition = 0; // номер символа в пароле
	char *tempPart = { ".tmp" }; // хвост temp файла
	char* namebuf = (char*)malloc(strlen(filenameString) + 1);
	strcpy(namebuf, filenameString);
	char *tempFilenameString = strcat(filenameString, tempPart); // создание имени temp файла
	if (0 != rename(namebuf, tempFilenameString))
	{
		printf("lol");
	}// переименование исходника в temp формат
	FILE *fr = fopen(tempFilenameString, "rb"); // открытие исходника
	FILE *fw = fopen(namebuf, "wb"); // создание файла с оригинальным именем исходника
	fread(&currentSym, 1, 1, fr); // пропуск байта шифрования
	fwrite(&currentSym, 1, 1, fw); // пропуск байта шифрования
	free(namebuf);
	fread(&currentSym, 1, 1, fr);
	while (!feof(fr))
	{
		currentSym = encryptorMain(currentSym, passwordString[passwordPosition]); // xor через соотв. символ пароля
		if (passwordPosition == passwordLength - 1) // проверка на конец пароля
			passwordPosition = 0; // если конец - переходим в начало
		else
			passwordPosition++; // не конец пароля - идем дальше
		fwrite(&currentSym, 1, 1, fw); // пишем
		fread(&currentSym, 1, 1, fr); //читаем еще один
	}
	fclose(fr); // закрываем
	fclose(fw); // закрываем
	remove(tempFilenameString); // удаляем temp файл
}