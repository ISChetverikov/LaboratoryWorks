#pragma once
#include "tree.h"

typedef struct QueueNode{
	TreeNode * node;
	struct QueueNode* next;
	struct QueueNode* prev;
}QueueNode;

int isQueueEmpty(QueueNode * queue);
void Enqueue(QueueNode ** queue, TreeNode * node);
TreeNode * Dequeue(QueueNode ** queue);
void FreeQueue(QueueNode * queue);