#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "queue.h"

TreeNode* CreateNode(char * key) {

	TreeNode* node;

	node = calloc(1, sizeof(TreeNode));
	node->word = calloc(strlen(key) + 1, sizeof(char));
	strcpy_s(node->word, strlen(key) + 1, key);

	node->count = 1;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

int GetHeight(TreeNode * p) {
	return p ? p->height : 0;
}

int GetFactor(TreeNode * p) {
	return GetHeight(p->right) - GetHeight(p->left);
}

void FixHeight(TreeNode * p) {
	int hl, hr;

	hl = GetHeight(p->left);
	hr = GetHeight(p->right);

	p->height = (hl > hr ? hl : hr) + 1;
}

TreeNode * RotateRight(TreeNode * p) {

	TreeNode * q;

	q = p->left;
	p->left = q->right;
	q->right = p;

	FixHeight(p);
	FixHeight(q);

	return q;
}

TreeNode * RotateLeft(TreeNode * q) {
	TreeNode* p;

	p = q->right;
	q->right = p->left;
	p->left = q;

	FixHeight(q);
	FixHeight(p);

	return p;

}
TreeNode * Balance(TreeNode * p) {

	TreeNode * result;
	FixHeight(p);

	if (GetFactor(p) == 2)
	{
		if (GetFactor(p->right) < 0)
			p->right = RotateRight(p->right);

		result = RotateLeft(p);
		return result;
	}
	if (GetFactor(p) == -2)
	{
		if (GetFactor(p->left) > 0)
			p->left = RotateLeft(p->left);

		return RotateRight(p);
	}

	return p;
}
TreeNode * Insert(TreeNode * p, char * key) {

	int compareResult = 0;

	if (!p) 
		return CreateNode(key);

	compareResult = strcmp(key, p->word);
	if (!compareResult) {
		p->count++;
		return p;
	}
		
	if (compareResult < 0)
		p->left = Insert(p->left, key);
	else
		p->right = Insert(p->right, key);

	return Balance(p);
}

void FreeAvl(TreeNode * p)
{
	if (!p)
		return;

	FreeAvl(p->left);
	FreeAvl(p->right);

	free(p->word);
	free(p);
}

int GetWordCount(TreeNode * p, unsigned char c) {
	int result = 0;

	if (!p)
		return 0;

	if (c == (unsigned char)p->word[0])
		result += p->count;

	if(c <= (unsigned char)p->word[0])
		result += GetWordCount(p->left, c);

	if (c >= (unsigned char)p->word[0])
		result += GetWordCount(p->right, c);

	return result;
}

void PrintDepth(TreeNode * p) {
	if (!p)
		return;

	PrintDepth(p->left);
	printf_s("(%s, %d) ", p->word, p->count);
	PrintDepth(p->right);
}

void PrintReverse(TreeNode * p) {
	if (!p)
		return;

	PrintReverse(p->left);
	PrintReverse(p->right);
	printf_s("(%s, %d) ", p->word, p->count);
}

void PrintWidth(TreeNode * p) {
	
	TreeNode * temp;
	QueueNode * q = NULL;

	if (!p)
		return;

	Enqueue(&q, p);
	while (!isQueueEmpty(q)) {
		temp = Dequeue(&q);
		printf_s("(%s, %d) ", temp->word, temp->count);
		if(temp->left != NULL)
			Enqueue(&q, temp->left);
		if (temp->right != NULL)
			Enqueue(&q, temp->right);
	}
}