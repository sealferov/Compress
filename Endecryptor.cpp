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
	int passwordLength = strlen(passwordString); // ����� ������
	char currentSym; // ������� ������
	int passwordPosition = 0; // ����� ������� � ������
	char *tempPart = { ".tmp" }; // ����� temp �����
	char* namebuf = (char*)malloc(strlen(filenameString) + 1);
	strcpy(namebuf, filenameString);
	char *tempFilenameString = strcat(filenameString, tempPart); // �������� ����� temp �����
	if (0 != rename(namebuf, tempFilenameString))
	{
		printf("lol");
	}// �������������� ��������� � temp ������
	FILE *fr = fopen(tempFilenameString, "rb"); // �������� ���������
	FILE *fw = fopen(namebuf, "wb"); // �������� ����� � ������������ ������ ���������
	fread(&currentSym, 1, 1, fr); // ������� ����� ����������
	fwrite(&currentSym, 1, 1, fw); // ������� ����� ����������
	free(namebuf);
	fread(&currentSym, 1, 1, fr);
	while (!feof(fr))
	{
		currentSym = encryptorMain(currentSym, passwordString[passwordPosition]); // xor ����� �����. ������ ������
		if (passwordPosition == passwordLength - 1) // �������� �� ����� ������
			passwordPosition = 0; // ���� ����� - ��������� � ������
		else
			passwordPosition++; // �� ����� ������ - ���� ������
		fwrite(&currentSym, 1, 1, fw); // �����
		fread(&currentSym, 1, 1, fr); //������ ��� ����
	}
	fclose(fr); // ���������
	fclose(fw); // ���������
	remove(tempFilenameString); // ������� temp ����
}