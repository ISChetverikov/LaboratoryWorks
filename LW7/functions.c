#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#pragma region  FirstTaskImplementation

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

errno_t DoFirstTask(char * filename, int numbersCount, int N, double * result) {
	FILE * pFile;
	errno_t errorCode;
	double number;
	long position = 0;
	long fileSize = 0;
	char * buffer;
	*result = 1;

    // Open file
	errorCode = fopen_s(&pFile, filename, "r+");
	if (errorCode != 0)
		return errorCode;

	// Estimetion of file size
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// Reading numbers, finding position after Nth element 
	for (int i = 0; i < numbersCount; i++) {
		fscanf_s(pFile, "%lf ", &number);

		if (i == N - 1)
			position = ftell(pFile);

		*result *= number;
	}

	// If Nth element does not exist then position will be in the end
	if (position == 0)
		position = ftell(pFile);

	// Copy remaing part of file into buffer
	fseek(pFile, position, SEEK_SET);
	buffer = calloc(fileSize + 1, sizeof(char));
	fread_s(buffer, fileSize, sizeof(char), fileSize, pFile);
	buffer[fileSize] = '\0';

	// Output production after Nth element and then remaining part as char *
	fseek(pFile, position, SEEK_SET);
	fprintf_s(pFile, "++Production = %lf++ %s", *result, buffer);

	fclose(pFile);

	return 0;
}

#pragma endregion


