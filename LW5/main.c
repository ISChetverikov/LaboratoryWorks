#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	/*
	
	���� ������, ���������� �� 1 �� 30 ����, � ������ �� ������� �� 1 �� 10
	��������� ���� �/��� ����; ����� ��������� ������� � �� ����� ������ �������, 
	�� ��������� ������ � �����. ���������� ��� �����, �������� �� ���������� �����,
	�������������� ������������ ������ �� ��� �� ���������� �������: ��������� ��������� ����� � ������ �����.

	*/
	char str[1024];
	char* last_word;
	char* word;
	char* context;

	printf_s("Please input string:\n");
	gets(str);

	// Cutting the dot
	str[strlen(str) - 1] = '\0';

	// Finding the last word
	last_word = strrchr(str, ' ') + 1;
	printf_s("Last word:\t%s\n", last_word);

	printf_s("Words:\n");
	word = strtok_s(str, " ", &context);
	while (word != NULL) {
		
		if (strcmp(word, last_word)) {
			printf("\t%c%s\n", word[strlen(word)-1], word);
		}

		word = strtok_s(NULL, " ", &context);
	}

	return 0;
}