#include "Node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VOWELS "AEUYIOaeyuio"

Node * CreateFromString(char * str) {
	char * copy;
	char * word, * context;
	
	Node * start = NULL;
	Node * current = NULL;
	Node * previous = NULL;

	copy = calloc(strlen(str) + 1, sizeof(char));
	strcpy_s(copy, strlen(str) + 1, str);

	word = strtok_s(copy, " .", &context);

	start = calloc(1, sizeof(Node));
	start->word = calloc(strlen(word) + 1, sizeof(char));
	strcpy_s(start->word, strlen(word) + 1, word);
	start->previous = NULL;
	start->next = NULL;
	previous = start;

	word = strtok_s(NULL, " .", &context);

	while (word != NULL) {
		current = calloc(1, sizeof(Node));

		current->word = calloc(strlen(word) + 1, sizeof(char));
		strcpy_s(current->word, strlen(word) + 1, word);

		current->next = NULL;
		current->previous = previous;
		previous->next = current;

		previous = current;

		word = strtok_s(NULL, " .", &context);
	}

	return start;
}
void PrintList(Node * l) {

	Node * current = l;
	
	if (l == NULL) {
		printf_s("List is empty!\n");
	}

	current = l;

	while (current != NULL)
	{
		printf_s("-> %s\n", current->word);
		current = current->next;
	}

	return;
}

int DoTask(Node ** l) {

	Node * current = *l;
	Node * temp = NULL;

	if (*l == NULL) {
		return -1;
	}

	while (current != NULL)
	{
		if (strchr(VOWELS, current->word[0]) != NULL) {

			if (current->previous != NULL) {
				current->previous->next = current->next;
			}
			else {
				*l = current->next;
			}
			
			if (current->next != NULL)
				current->next->previous = current->previous;

			free(current->word);
			temp = current->next;
			free(current);
		}
		else
		{
			temp = current->next;
		}
		current = temp;
	}

	return 0;
}

void Free(Node * l) {
	Node * current = l;
	Node * next = NULL;

	while (current != NULL)
	{
		free(current->word);
		next = current->next;
		free(current);
		current = next;
	}

	return;
}