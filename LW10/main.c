#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

#define BUFFER_SIZE 1024


int main() {
	char str[BUFFER_SIZE];
	Node* list = NULL;
	gets(str);
	
	list = CreateFromString(str);
	printf_s("Before:\n");
	PrintList(list);
	DoTask(&list);

	printf_s("After:\n");
	PrintList(list);

	Free(list);
	return 0;
}