#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "queue.h"

#define BUFFER_SIZE 1024
#define DELIMETER " .,\n;!?-�:"

TreeNode * AvlFromFile(char * fileName) {
	TreeNode * avl = NULL;
	FILE * pFile;
	char str[BUFFER_SIZE];
	char * readStr;
	char * word, * context;
	
	fopen_s(&pFile, fileName, "r");

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
				return NULL;
			}
		}

		for (int i = 0; i < strlen(readStr); i++)
		{
			if (readStr[i] >= '�' && readStr[i] <= '�')
				readStr[i] += 32;
		}
		
		word = strtok_s(readStr, DELIMETER, &context);
		while (word != NULL) {
			avl = Insert(avl, word);

			word = strtok_s(NULL, DELIMETER, &context);
		}
	}

	return avl;
}

int main() {
	TreeNode * avl;
	QueueNode * q = NULL;

	int count = 0;
	char c = '\0';
	char letter = 0;
	system("chcp 1251");

	avl = AvlFromFile("Text.txt");
	printf_s("���������� ������� ��������!\n");

	printf_s("1. ���������� ���� �� �����\n");
	printf_s("2. ����� � �������\n");
	printf_s("3. �������� �����\n");
	printf_s("4. ����� � ������\n");
	printf_s("q. Quit\n");


	while (c != 'q') {
		scanf_s("%c", &c);
		switch (c)
		{
		case '1':
			printf_s("�������� �����:\n");
			scanf_s("%c", &c);
			scanf_s("%c", &letter);

			count = GetWordCount(avl, letter);
			printf_s("\n���������� ����: %d\n", count);

			break;
		case '2':
			PrintDepth(avl);
			printf_s("\n");
			break;
		case '3':
			PrintReverse(avl);
			printf_s("\n");
			break;
		case '4':
			PrintWidth(avl);
			break;
		default:
			break;
		}
	}

	FreeAvl(avl);

	return 0;
}