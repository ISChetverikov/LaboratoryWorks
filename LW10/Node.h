#pragma once


typedef struct Node {
	char * word;
	struct Node * previous;
	struct Node * next;

} Node;

Node * CreateFromString(char * str);
void PrintList(Node * l);
int DoTask(Node ** l);
void FreeAvl(Node * l);