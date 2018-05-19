#include <stdlib.h>
#include <stdio.h>
#include "sql.h"
#include "queryHandler.h"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Russian");
	printf_s("Test program!\n");

	char text[512] = "CREATE TABLE test ( Name STRING, age INT, sex INT )";
	char text2[512] = "INSERT INTO test ( 'Крошка Крошкович Крошков', 18, 0)";
	char text3[512] = "SELECT * FROM test";

	int r = queryHandler(text3);

	printf_s("\n%d\n", r);

	return 0;
}

