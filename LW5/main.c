#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

char** ProcessString(char * input, int * wordsCount) {

	char* last_word;
	char* word;
	char* context;
	char last_letter;
	int length;
	char * stringCopy;
	char ** result;

	strcpy(stringCopy, input);

	stringCopy[strlen(stringCopy) - 1] = '\0';

	// Finding the last word
	last_word = strrchr(stringCopy, ' ') + 1;
	printf_s("Last word:\t%s\n", last_word);

	printf_s("Words:\n");
	word = strtok_s(stringCopy, " ", &context);
	while (word != NULL) {
		length = strlen(word);
		if (strcmp(word, last_word)) {
			last_letter = word[length - 1];
			word[length - 1] = '\0';
			printf("\t%c%s\n", last_letter, word);
		}

		word = strtok_s(NULL, " ", &context);
	}

}

int main() {
	/*
	
	���� ������, ���������� �� 1 �� 30 ����, � ������ �� ������� �� 1 �� 10
	��������� ���� �/��� ����; ����� ��������� ������� � �� ����� ������ �������, 
	�� ��������� ������ � �����. ���������� ��� �����, �������� �� ���������� �����,
	�������������� ������������ ������ �� ��� �� ���������� �������: ��������� ��������� ����� � ������ �����.

	*/
	char str[1024];
	char** wordsArr;
	int wordsCount;

	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	printf_s("Please input string:\n");
	gets(str);

	wordsArr = ProcessString(str, &wordsCount);

	return 0;
}