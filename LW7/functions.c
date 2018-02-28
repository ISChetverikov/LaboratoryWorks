#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

#pragma region  FirstTaskImplementation

errno_t ReadFirstFile(char * filename, double ** resultArr, int * numbersCount) {
	FILE * pFile;
	double number;
	double buffer[1024]; // const
	errno_t errorCode;
	int i = 0;

	errorCode = fopen_s(&pFile, filename, "r+");
	if (errorCode != 0)
		return errorCode;

	while (fscanf_s(pFile, "%lf ", &number) != EOF)
	{
		buffer[i] = number;
		i++;
	}

	*numbersCount = i;
	*resultArr = calloc(*numbersCount, sizeof(double));
	errorCode = memcpy_s(*resultArr, (*numbersCount) * sizeof(double), buffer, (*numbersCount) * sizeof(double));
	if (errorCode != 0)
		return errorCode;

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

errno_t WriteFirstResult(char * filename, double result, int N) {

	FILE * pFile;
	errno_t errorCode;
	long position = 0;
	long fileSize = 0;
	char * buffer;
	int i = 0;
	double number;

	errorCode = fopen_s(&pFile, filename, "r+");
	if (errorCode != 0)
		return errorCode;

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

	// Output production after Nth element and then remaining part as char *
	fseek(pFile, position, SEEK_SET);
	fprintf_s(pFile, "{RESULT = %lf} %s", result, buffer);

	fclose(pFile);

	return 0;
}

errno_t CreateFirstFile(char * filename, int numbersCount) {
	FILE * pFile;
	errno_t errorCode;
	time_t t;

	srand((unsigned)time(&t));

	errorCode = fopen_s(&pFile, filename, "w+");
	if (errorCode != 0)
		return errorCode;

	for (int i = 0; i < numbersCount; i++) {
		fprintf_s(pFile, "%lf ", (double)rand() / RAND_MAX * 2.0 - 1.0);
	}

	fclose(pFile);

	return 0;
}

errno_t DoFirstTask(char * filename, int N, double * result) {

	double* arr;
	int numbersCount;
	
	ReadFirstFile(filename, &arr, &numbersCount);
	*result = MulArrElements(arr, numbersCount);
	WriteFirstResult(filename, *result, N);

	return 0;
}

#pragma endregion


