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
	char c = '\n';

	printf_s("Laboratory work ¹7\n");
	printf_s("Choose what you want:\n");
	printf_s("1 - Launch First task\n");
	printf_s("2 - Launch Second task\n");
	printf_s("0 - Close this programm\n");

	while (c != '0') {

		switch (c)
		{
		case '1':
			printf_s("Please input N:\t");
			scanf_s("%d", &N);

			CreateFirstFile(FIRST_FILENAME, FIRST_FILE_NUMBERS_COUNT);
			DoFirstTask(FIRST_FILENAME, N, &result);
			printf_s("Result of multiplication of all elements in the first file is %lf and"
				" it has written after element which has number %d\n", result, N);
			break;

		case '2':
			CreateSecondFile(SECOND_INPUT_FILENAME, SECOND_FILE_STRINGS_COUNT);
			DoSecondTask(SECOND_INPUT_FILENAME, SECOND_OUTPUT_FILENAME);
			printf_s(
				"File \"%s\" has been created from file \"%s\" according to task conditions\n",
				SECOND_OUTPUT_FILENAME,
				SECOND_INPUT_FILENAME
			);
			break;
		default:
			break;
		}
		
		c = getchar();
	}
	printf_s("Bye!\n");
	
	return 0;
}