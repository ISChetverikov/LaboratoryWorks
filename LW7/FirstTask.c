#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FirstTask.h"

#pragma region  FirstTaskImplementation

int ReadFirstFile(char * filename, double ** resultArr, int * numbersCount) {
	FILE * pFile;
	double number;
	double buffer[DOUBLE_ARRAY_BUFFER];
	int i = 0;

	if(fopen_s(&pFile, filename, "r+"))
		return -1;

	while (fscanf_s(pFile, "%lf ", &number) != EOF)
	{
		buffer[i] = number;
		i++;
	}

	*numbersCount = i;
	*resultArr = calloc(*numbersCount, sizeof(double));
	 
	if (memcpy_s(*resultArr, (*numbersCount) * sizeof(double), buffer, (*numbersCount) * sizeof(double)))
		return -1;

	fclose(pFile);
	return 0;
}

double MulArrElements(double * arr, int numbersCount) {
	double result = 1;
	for (int i = 0; i < numbersCount; i++)
	{
		result *= arr[i];
	}

	return result;
}

int WriteFirstResult(char * filename, double result, int N) {

	FILE * pFile;
	long position = 0;
	long fileSize = 0;
	char * buffer;
	int i = 0;
	double number;

	if (fopen_s(&pFile, filename, "r+"))
		return -1;
	
	// Estimetion of file size
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// Finding position after Nth element
	while (fscanf_s(pFile, "%lf ", &number) != EOF)
	{
		i++;

		if (i == N)
			position = ftell(pFile);
	}

	//// If Nth element does not exist then position will be in the end
	if (position == 0)
		position = ftell(pFile);

	// Copy remaing part of file into buffer
	fseek(pFile, position, SEEK_SET);
	buffer = calloc(fileSize + 1 - position, sizeof(char));
	fread_s(buffer, fileSize - position, sizeof(char), fileSize - position, pFile);
	buffer[fileSize - position] = '\0';

	// Output result after Nth element and then remaining part as char *
	fseek(pFile, position, SEEK_SET);
	fprintf_s(pFile, "{RESULT = %lf} %s", result, buffer);

	free(buffer);
	fclose(pFile);

	return 0;
}

int CreateFirstFile(char * filename, int numbersCount) {
	FILE * pFile;
	time_t t;
	srand((unsigned)time(&t));

	if (fopen_s(&pFile, filename, "w+"))
		return -1;

	for (int i = 0; i < numbersCount; i++) {
		fprintf_s(pFile, "%lf ", (double)rand() / RAND_MAX * DOUBLE_RAND_LENGTH + DOUBLE_RAND_MIN);
	}

	fclose(pFile);

	return 0;
}

int DoFirstTask(char * filename, int N, double * result) {

	double* arr;
	int numbersCount;
	
	ReadFirstFile(filename, &arr, &numbersCount);
	*result = MulArrElements(arr, numbersCount);
	WriteFirstResult(filename, *result, N);

	free(arr);
	return 0;
}

#pragma endregion


