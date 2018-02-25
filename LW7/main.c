#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define FIRST_FILENAME "first.txt"
#define SECOND_INPUT_FILENAME "second_input.txt"
#define SECOND_SECOND_FILENAME "second_output.txt"
#define FIRST_FILE_NUMBERS_COUNT 10

int main() {

	double result;
	int N = 1;

	CreateFirstFile(FIRST_FILENAME, FIRST_FILE_NUMBERS_COUNT);
	DoFirstTask(FIRST_FILENAME, FIRST_FILE_NUMBERS_COUNT, N, &result);

	return 0;
}