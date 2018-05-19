#include <stdlib.h>
#include <stdio.h>
#include "sql.h"
#include "queryHandler.h"

int main() {
	printf_s("Test program!\n");

	char text[512] = "CREATE TABLE test ( Name STRING, age INT, sex INT )";
	int r = queryHandler(text);

	printf_s("%d", r);

	return 0;
}

