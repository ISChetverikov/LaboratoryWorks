#include "queue.h"
#include <string.h>
#include <stdlib.h>

int isQueueEmpty(QueueNode * queue) {
	return queue == NULL;
}

// Вставка в очередь 
void Enqueue(QueueNode ** pQueue, TreeNode * node) {
	QueueNode * current;

	current = calloc(1, sizeof(QueueNode));
	current->node = node;

	if (isQueueEmpty(*pQueue)) {
		current->next = current;
		current->prev = current;
		(*pQueue) = current;
	}
	else {
		current->prev = (*pQueue)->prev;
		current->next = *pQueue;

		(*pQueue)->prev->next = current;
		(*pQueue)->prev = current;
		return;
	}
	
}

TreeNode * Dequeue(QueueNode ** pQueue) {
	TreeNode * result;
	QueueNode * temp;
	if (isQueueEmpty(*pQueue))
		return NULL;

	result = (*pQueue)->node;

	if ((*pQueue)->next == (*pQueue)) {
		free(*pQueue);
		*pQueue = NULL;
		
	}
	else {
		// Копируем след элемент на перове место, чтобы начало очереди было стационарным
		temp = (*pQueue)->next;
		(*pQueue)->next = temp->next;
		temp->next->prev = (*pQueue);
		(*pQueue)->node = temp->node;
		free(temp);
	}
	
	return result;
}

void FreeQueue(QueueNode * queue) {
	QueueNode * temp;
	temp = queue;
	while (temp != NULL)
	{
		temp = queue->next;
		queue = queue->next;
		free(temp);
	}

	return;
}