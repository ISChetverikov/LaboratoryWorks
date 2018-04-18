#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 80

char * AddBrackets(char * str) {
	
	char buffer[BUFFER_SIZE * 3];
	char * result;
	int length = (int)strlen(str);
	int j = 0;
	int flag = 0;

	for (int i = 0; i <= length; i++)
	{
		if (str[i] >= '0' && str[i] <= '9') {

			if (flag == 0) {

				flag = 1;
				buffer[j] = '(';
				buffer[j + 1] = str[i];
				j += 2;
			}
			else {
				buffer[j] = str[i];
				j++;
			}
		}
		else {

			if (flag == 1) {

				flag = 0;
				buffer[j] = ')';
				buffer[j + 1] = str[i];
				j += 2;
			}
			else {

				buffer[j] = str[i];
				j++;
			}
		}
		
	}
	buffer[j] = '\0';
	j++;
	result = calloc(j, sizeof(char));
	strcpy_s(result, j, buffer);

	return result;
}

int first() {
	FILE * pFileIn, *pFileOut;
	fopen_s(&pFileIn, "input.txt", "r");
	fopen_s(&pFileOut, "output.txt", "w");

	char str[BUFFER_SIZE];
	char * readStr;
	int i = 1;

	while (1) {
		readStr = fgets(str, BUFFER_SIZE, pFileIn);

		if (readStr == NULL)
		{
			if (feof(pFileIn) != 0)
			{
				break;
			}
			else
			{
				fclose(pFileIn);
				return -1;
			}
		}

		if (i % 2 == 1) {
			readStr = AddBrackets(readStr);
			fputs(readStr, pFileOut);
			free(readStr);
		}
		i++;
			
	}
	fclose(pFileIn);
	fclose(pFileOut);

	return 0;
}

int firstValera() {
	FILE * pFileIn, *pFileOut;
	fopen_s(&pFileIn, "input.txt", "r");
	fopen_s(&pFileOut, "output.txt", "w");

	int last = 0;
	int lastButOne = 0;

	char str[BUFFER_SIZE];
	char * readStr;
	int i = 0;

	while (1) {
		readStr = fgets(str, BUFFER_SIZE, pFileIn);
		
		if (readStr == NULL)
		{
			if (feof(pFileIn) != 0)
			{
				fseek(pFileIn, lastButOne, SEEK_SET);
				break;
			}
			else
			{
				fclose(pFileIn);
				return -1;
			}
		}

		i++;
	}

	fseek(pFileIn, 0 , SEEK_SET);
	i--;
	while (1) {
		readStr = fgets(str, BUFFER_SIZE, pFileIn);
		
		if (readStr == NULL)
		{
			if (feof(pFileIn) != 0)
			{
				fseek(pFileIn, lastButOne, SEEK_SET);
				break;
			}
			else
			{
				fclose(pFileIn);
				return -1;
			}
		}

		i--;
		if (i != 0) {
			fputs(readStr, pFileOut);
		}
		else {
			readStr = AddBrackets(readStr);
			fputs(readStr, pFileOut);
			free(readStr);
		}

	}

	fclose(pFileIn);
	fclose(pFileOut);

	return 0;
}

int CreateFile() {
	time_t t;
	FILE * pFile;
	int number = 0;

	srand((unsigned)time(&t));
	if (fopen_s(&pFile, "binary.bin", "wb")) {
		return -1;
	}

	printf_s("\n");
	for (int i = 0; i < 10; i++)
	{
		number = rand() % 10;// -RAND_MAX / 2;
		printf_s("%d ", number);
		fwrite(&number, sizeof(int), 1, pFile);
	}
	printf_s("\n");
	
	fclose(pFile);
	return 0;
}

int PrintFile() {
	FILE * pFile;
	int fileSize;
	int number;

	if (fopen_s(&pFile, "binary.bin", "rb")) {
		return -1;
	}

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	for (int i = 0; i < fileSize / 4; i++)
	{
		fread(&number, sizeof(int), 1, pFile);
		printf_s("%d ", number);
	}
	printf_s("\n");

	fclose(pFile);
	return 0;
}

int DoRoutine() {
	FILE * pFile;
	int fileSize;
	int number;

	int max = INT_MIN;
	int positionMax = 0;
	int positiveCounter = 0;
	 
	if (fopen_s(&pFile, "binary.bin", "rb+")) {
		return -1;
	}

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	for (int i = 0; i < fileSize / 4; i++)
	{
		fread(&number, sizeof(int), 1, pFile);
		if (number > 0)
			positiveCounter++;

		if (number > max)
		{
			max = number;
			positionMax = ftell(pFile);
		}
	}
	
	fseek(pFile, positionMax, SEEK_SET);
	void * buffer = calloc(fileSize - positionMax, sizeof(char));
	fread(buffer, sizeof(int), (fileSize - positionMax)/4, pFile);

	fseek(pFile, positionMax, SEEK_SET);
	fwrite(&positiveCounter, sizeof(int), 1, pFile);
	fwrite(buffer, sizeof(int), (fileSize - positionMax) / 4, pFile);

	fclose(pFile);
	return 0;
}

int second() {
	CreateFile();
	PrintFile();
	DoRoutine();
	PrintFile();
}

int main() {

	second();
	
	return 0;
}