#pragma once

typedef struct Node {
	int value;
	int degree;
	struct Node * next;
} Node;

Node * Create(int * coefs, int * degrees, int count);
Node * Sum(Node * left, Node * right);
void Print(Node * l);
void FreeAvl(Node * l);