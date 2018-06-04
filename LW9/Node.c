#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

Node* Create(int * coefs, int * degrees, int count) {
	int i = 0;
	int j = 0;
	int temp = 0;
	Node* current = NULL;
	Node* start = NULL;
	Node* previous = NULL;

	if (count < 0) {

		return NULL;
	}

	for (i = 1; i < count; i++)
	{
		for (j = 0; j < count - i; j++) {
			if (degrees[j] > degrees[j + 1]) {
				temp = degrees[j];
				degrees[j] = degrees[j + 1];
				degrees[j + 1] = temp;

				temp = coefs[j];
				coefs[j] = coefs[j + 1];
				coefs[j + 1] = temp;
			}
		}
	}

	start = (Node *)calloc(1, sizeof(Node));
	start->value = (count != 0) ? coefs[0] : 0;
	start->degree = (count != 0) ? degrees[0] : 0;
	start->next = NULL;
	previous = start;

	for (i = 1; i < count; i++)
	{
		if (degrees[i] == previous->degree)
			return NULL;

		current = (Node *)calloc(1, sizeof(Node));
		current->value = coefs[i];
		current->degree = degrees[i];
		current->next = NULL;

		previous->next = current;
		previous = current;
	}

	return start;
}

Node * Sum(Node * left, Node * right) {

	Node * result = NULL;
	Node * current = NULL;
	Node * previous = NULL;

	Node * currentLeft = left;
	Node * currentRight = right;
	Node * temp = NULL;

	if (left == NULL || right == NULL) {
		return NULL;
	}

	result = (Node *)calloc(1, sizeof(Node));
	result->degree = 0;
	result->value = 0;
	previous = result;

	while (1) {
		
		if (currentLeft == NULL) {
			if (currentRight == NULL) {
				break;
			}
			else
			{
				temp = currentRight;
			}
		}
		else {
			if (currentRight == NULL) {
				temp = currentLeft;
			}
			else
			{
				temp = (currentLeft->degree < currentRight->degree) ? currentLeft : currentRight;
			}
		}

		if (previous->degree == temp->degree) {
			previous->value += temp->value;
		}
		else
		{
			current = (Node *)calloc(1, sizeof(Node));
			current->degree = temp->degree;
			current->value = temp->value;
			previous->next = current;
			previous = current;
		}
		
		if (temp == currentRight) {
			currentRight = currentRight->next;
		}
		else
		{
			currentLeft = currentLeft->next;
		}

	}

	return result;
}


void Print(Node * l) {
	Node * current = l;
	
	if (l == NULL) {
		printf_s("Polynomial does not exist!\n");
		return;
	}

	do
	{
		printf_s("%+ix^%d", current->value, current->degree);
		current = current->next;
	}
	while (current->next != NULL);
	printf_s("%+ix^%d", current->value, current->degree);

	printf_s("\n");
}

void FreeAvl(Node * l) {
	Node * current = l;
	Node * next = NULL;

	if (l == NULL) {
		return;
	}

	while (current->next != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	
	return;
}