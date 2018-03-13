#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "SecondTask.h"

#define STRING_BUFFER_SIZE 512
#define STRING_ARRAY_BUFFER_SIZE 100

#define SHORT_STRING_WORD_LENGTH_BOUND 20
#define SHORT_STRING_LENGTH_BOUND 20

#define LONG_STRING_WORD_LENGTH_BOUND 35
#define LONG_STRING_LENGTH_BOUND 100

#define SHORT_STRING_PROBABILITY 0.1
#define LONG_WORD_PROBABILITY 0.1
#define SIGN_PROBABILITY 0.05

#define UPPERCASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE_LETTERS "abcdefghijkilmnoprstuvwxyz"
#define ALPHABET_LENGTH 26

#pragma region SecondFileGeneration

char * GenerateWord(int length, int isNeedCapital) {
	char * word;
	int i = 0;

	word = calloc(length + 1, sizeof(char));
	word[length] = '\0';

	if (isNeedCapital) {
		word[i] = UPPERCASE_LETTERS[rand() % ALPHABET_LENGTH];
		i++;
	}

	for (; i < length; i++)
	{
		word[i] = LOWERCASE_LETTERS[rand() % ALPHABET_LENGTH];
	}

	return word;
}

char * GenerateString(int stringLengthBound, int wordLengthBound) {

	int stringLength;
	int wordLength;
	int remainStringLength;

	char * string;
	char * word;

	stringLength = 1 + rand() % stringLengthBound;
	string = calloc(stringLength + 1, sizeof(char));

	// First word
	wordLength = 1 + rand() % min(wordLengthBound, stringLength);
	word = GenerateWord(wordLength, 1);
	strcpy_s(string, stringLength + 1, word);
	free(word);
	remainStringLength = stringLength - wordLength;

	wordLength = 1 + rand() % wordLengthBound;
	while (remainStringLength > wordLength + 1) {

		word = GenerateWord(wordLength, 0);

		strcat_s(string, stringLength + 1, " ");
		strcat_s(string, stringLength + 1, word);
		free(word);

		remainStringLength -= (wordLength + 1);
		wordLength = 1 + rand() % wordLengthBound;
	}

	// Last word
	if (remainStringLength != 0) {
		word = GenerateWord(remainStringLength - 1, 0);

		strcat_s(string, stringLength + 1, " ");
		strcat_s(string, stringLength + 1, word);
		free(word);
	}

	return string;
}

char * GenerateShortString() {
	return GenerateString(SHORT_STRING_LENGTH_BOUND, SHORT_STRING_WORD_LENGTH_BOUND);
}

char * GenerateLongString() {
	return GenerateString(LONG_STRING_LENGTH_BOUND, LONG_STRING_WORD_LENGTH_BOUND);
}

int CreateSecondFile(char * filename, int stringsCount) {
	FILE * pFile;
	time_t t;
	char * string;

	srand(time(&t));

	if (fopen_s(&pFile, filename, "w+"))
		return -1;

	for (int i = 0; i < stringsCount; i++)
	{
		if (rand() % 100 < 100 * SHORT_STRING_PROBABILITY)
			string = GenerateShortString();
		else
			string = GenerateLongString();

		fprintf_s(pFile, "%s\n", string);
		free(string);
	}

	fclose(pFile);
	return 0;
}
#pragma endregion

int ReadSecondFile(char * filename, char *** resultArr, int * stringsCount) {
	FILE * pFile;

	char str[STRING_BUFFER_SIZE];
	char * readStr;
	char * resultBuffer[STRING_ARRAY_BUFFER_SIZE];

	int strLength = 0;
	int i = 0;

	if (fopen_s(&pFile, filename, "r"))
		return -1;

	while (1) {
		readStr = fgets(str, sizeof(str), pFile);

		if (readStr == NULL)
		{
			if (feof(pFile) != 0)
			{
				break;
			}
			else
			{
				fclose(pFile);
				return -1;
			}
		}

		strLength = strnlen_s(readStr, STRING_BUFFER_SIZE);
		resultBuffer[i] = calloc(strLength + 1, sizeof(char));
		strcpy_s(resultBuffer[i], strLength + 1, readStr);
		i++;
	}
	*stringsCount = i;

	*resultArr = calloc(*stringsCount, sizeof(char *));
	if (memcpy_s(*resultArr, (*stringsCount) * sizeof(char*), resultBuffer, (*stringsCount) * sizeof(char*)))
		return -1;

	fclose(pFile);
	return 0;
}

int WriteSecondFile(char * outputFilename, char ** strings, int stringsCount) {

	FILE * pFile;

	if (fopen_s(&pFile, outputFilename, "w+"))
		return -1;

	for (int i = 0; i < stringsCount; i++)
	{
		fprintf_s(pFile, "%s\n", strings[i]);
	}

	fclose(pFile);
}

int DoRoutine(char *** strings, int * stringsCount) {
	char * resultBuffer[STRING_ARRAY_BUFFER_SIZE];
	char ** result;
	int j = 0;
	int wordLength = 0;
	char * context;
	char * word;
	char * substring;
	int currentLength = 0;
	
	substring = calloc(SHORT_STRING_LENGTH_BOUND + 1, sizeof(char));

	for (int i = 0; i < *stringsCount; i++)
	{
		char * string = (*strings)[i];
		
		if (strnlen_s(string, STRING_BUFFER_SIZE) <= SHORT_STRING_LENGTH_BOUND) {
			continue;
		}
		
		word = strtok_s(string, " \n", &context);
		while (word != NULL) {
			wordLength = strlen(word);
			if (wordLength > SHORT_STRING_WORD_LENGTH_BOUND) {
				word = strtok_s(NULL, " \n", &context);
				continue;
			}

			if (currentLength + wordLength >= SHORT_STRING_LENGTH_BOUND && currentLength != 0) {
				resultBuffer[j] = calloc(strlen(substring) + 1, sizeof(char));
				strcpy_s(resultBuffer[j], strlen(substring) + 1, substring);

				j++;
				substring[0] = '\0';
				currentLength = 0;
			}

			if (currentLength != 0) {
				strcat_s(substring, SHORT_STRING_LENGTH_BOUND + 1, " ");
				currentLength++;
			}
			strcat_s(substring, SHORT_STRING_LENGTH_BOUND + 1, word);
			currentLength += wordLength;

			word = strtok_s(NULL, " \n", &context);
		}

		if (strlen(substring) != 0) {
			
			resultBuffer[j] = calloc(strlen(substring) + 1, sizeof(char));
			strcpy_s(resultBuffer[j], strlen(substring) + 1, substring);
			j++;
			substring[0] = '\0';
			currentLength = 0;
		}
	}


	for (int i = 0; i < *stringsCount; i++)
	{
		free((*strings)[i]);
	}
	free(*strings);

	*stringsCount = j;
	*strings = calloc(*stringsCount, sizeof(char *));
	if (memcpy_s(*strings, *stringsCount * sizeof(char*), resultBuffer, *stringsCount * sizeof(char*)))
		return -1;

	return 0;
}

int DoSecondTask(char * inputFilename, char * outputFilename) {
	char ** strings;
	int stringsCount = 0;

	ReadSecondFile(inputFilename, &strings, &stringsCount);
	DoRoutine(&strings, &stringsCount);
	WriteSecondFile(outputFilename, strings, stringsCount);

	for (int i = 0; i < stringsCount; i++)
	{
		free(strings[i]);
	}
	free(strings);

	return 0;
}