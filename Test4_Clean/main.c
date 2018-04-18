#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024


#pragma region FirstTask
char * DeleteRepeats(char * str) {

	char buffer[BUFFER_SIZE];
	char * result;
	int flags[10];
	int j = 0;
	int digit = 0;

	for (int i = 0; i < 10; i++)
	{
		flags[i] = 0;
	}

	for (int i = 0; i <= strlen(str); i++)
	{
		if (str[i] >= '0' && str[i] <= '9') {

			digit = (int)str[i] - 0x30;

			if (flags[digit] == 0) {

				flags[digit] = 1;
				buffer[j] = str[i];
				j++;
			}
		}
		else {
			buffer[j] = str[i];
			j++;
		}

	}
	buffer[j] = '\0';
	j++;
	result = calloc(j, sizeof(char));
	strcpy_s(result, j, buffer);

	return result;
}

int First() {
	FILE * pFileIn, *pFileOut;
	char str[BUFFER_SIZE];
	char * readStr;

	fopen_s(&pFileIn, "input.txt", "r");
	fopen_s(&pFileOut, "output.txt", "w");

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

		readStr = DeleteRepeats(readStr);
		fputs(readStr, pFileOut);
		free(readStr);
	}
	fclose(pFileIn);
	fclose(pFileOut);

	return 0;
}

#pragma endregion

#pragma region SecondTask
int CreateFile(int count) {
	time_t t;
	FILE * pFile;
	int number = 0;

	srand((unsigned)time(&t));
	if (fopen_s(&pFile, "binary.bin", "wb")) {
		return -1;
	}

	for (int i = 0; i < count; i++)
	{
		number = rand() % 10 - 5 ;
		fwrite(&number, sizeof(int), 1, pFile);
	}

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

	int firstNegativePosition = 0;
	int positiveCounter = 0;
	int position = 0;
	int int_size = sizeof(int);

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

		if (number < 0 && firstNegativePosition == 0)
		{
			firstNegativePosition = ftell(pFile);
		}
	}

	fseek(pFile, fileSize, SEEK_SET);
	position = ftell(pFile) - int_size;

	while (position >= firstNegativePosition) {
		fseek(pFile, position , SEEK_SET);
		fread(&number, int_size, 1, pFile);
		fseek(pFile, position + int_size, SEEK_SET);
		fwrite(&number, int_size, 1, pFile);
		position -= int_size;
	}
	fseek(pFile, position + int_size, SEEK_SET);
	fwrite(&positiveCounter, sizeof(int), 1, pFile);
	
	fclose(pFile);
	return 0;
}

int Second() {
	CreateFile(10);
	printf_s("Binary file:\n");
	PrintFile();
	DoRoutine();
	printf_s("Binary file after modification:\n");
	PrintFile();
}

#pragma endregion

int main() {
	printf_s("First task is working...\n");
	First();
	printf_s("Second task is working...\n");
	Second();

	return 0;
}

