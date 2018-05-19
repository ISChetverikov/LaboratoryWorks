#include <stdlib.h>
#include <stdio.h>
#include "sql.h"
#include "queryHandler.h"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Russian");
	printf_s("Test program!\n");

	char text[512] = "CREATE TABLE test1 ( Name STRING, Age INT, publisher STRING )";
	char text2[512] = "INSERT INTO test1 ( 'Крошка Крошкович Крошков', 18, 'Москва asdf asdf asdf asdf asdf asdf asdf')";
	char text3[512] = "INSERT INTO test1 ( 'Крошка Крошкович Крошков', 121, 'Москва asdf asdf asdf asdf asdf asdf asdf')";
	char text4[512] = "INSERT INTO test1 ( 'Крошка Крошкович Крошков', 18, 'Москва asdf asdf asdf asdf asdf asdf asdf')";
	char text5[512] = "INSERT INTO test1 ( 'Крошка Крошкович Крошков', 180, 'Москва asdf asdf asdf asdf asdf asdf asdf')";
	char text6[512] = "SELECT * FROM test1 WHERE Age=180";

	int r = queryHandler(text6);
	/*r = queryHandler(text3);
	r = queryHandler(text4);
	r = queryHandler(text5);
	r = queryHandler(text4);*/


	printf_s("\n%d\n", r);

	return 0;
}

