#include "stdafx.h"
#include <conio.h>
#include <string>
#include <stdio.h>
int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		char* key = argv[1];
		char* name = argv[2];
		char namebuf[256] = {""};
		char* nameb = {"r"};
		strcat(namebuf, name);
		strcat(namebuf, nameb);
		FILE *f;
		FILE *nf;
		if (strcmp("-c", key) == 0)
		{
			if ((f = fopen(name, "r+b")) == NULL)
			{
				printf("Cannot open file.\n");
				return 0;
			}
			if ((nf = fopen(namebuf, "w+b")) == NULL)
			{
				printf("Cannot create file.\n");
				return 0;
			}

			//code(f,nf);
			fclose(f);
			fclose(nf);
			return 0;
		}
		else
		{
			if (strcmp("-d", key) == 0)
			{
				if ((f = fopen(name, "r+b")) == NULL)
				{
					printf("Cannot open file\n");
					return 0;
				}
				if ((nf = fopen(namebuf, "w+b")) == NULL)
				{
					printf("Cannot create file.\n");
					return 0;
				}
				//decode(f,nf);
				fclose(f);
				fclose(nf);
				return 0;
			}
			else
			{
				printf("Incorrect key\n");
				return 0;
			}
		}
	}
	else
	{
		if (argc == 4)
		{
			char* key = argv[1];
			char* name = argv[2];
			char* name2 = argv[3];
			FILE *f;
			FILE *nf;
			if (strcmp("-c2", key) == 0)
			{
				if ((f = fopen(name, "r+b")) == NULL)
				{
					printf("Cannot open a file.\n");
					return 0;
				}
				if ((nf = fopen(name2, "w+b")) == NULL)
				{
					printf("Cannot create a file\n");
					return 0;
				}
				//code(f,nf);
				fclose(f);
				fclose(nf);
				return 0;
			}
			else
			{
				if (strcmp("-d2", key) == 0)
				{
					if ((f = fopen(name, "r+b")) == NULL)
					{
						printf("Cannot open a file\n");
						return 0;
					}
					if ((nf = fopen(name2, "w+b")) == NULL)
					{
						printf("Cannot create a file\n");
						return 0;
					}
					//decode(f,nf);
					fclose(f);
					fclose(nf);
					return 0;
				}
				else
				{
					printf("Incorrect key\n");
				}
			}
		}
	}
	printf("Problem with arguments");
	getch();
	return 0;
}