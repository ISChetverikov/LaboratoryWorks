#include <stdio.h>
#include <stdlib.h>
#include "FirstTask.h"
#include "SecondTask.h"


#define FIRST_FILENAME "first.txt"
#define FIRST_FILE_NUMBERS_COUNT 10

#define SECOND_INPUT_FILENAME "second_input.txt"
#define SECOND_OUTPUT_FILENAME "second_output.txt"
#define SECOND_FILE_STRINGS_COUNT 20

int main() {
	
	double result;
	int N = 5;

	/*CreateFirstFile(FIRST_FILENAME, FIRST_FILE_NUMBERS_COUNT);
	DoFirstTask(FIRST_FILENAME, N, &result);
	printf_s("Result of multiplication of all elements in the first file is %lf and"
		" it has written after element which has number %d.\n\n", result, N);*/

	CreateSecondFile(SECOND_INPUT_FILENAME, SECOND_FILE_STRINGS_COUNT);
	DoSecondTask(SECOND_INPUT_FILENAME, SECOND_OUTPUT_FILENAME);

	return 0;
}