#include <stdlib.h>
#include <stdio.h>
#include "sql.h"
#include "queryHandler.h"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Russian");
	printf_s("Test program!\n");
	int r = 0;
	char text[512] = "CREATE TABLE test1 ( Name STRING, Age INT, publisher STRING )";
	char text2[512] = "INSERT INTO test1 ( 'Крошка Крошкович Крошков', 18, 'Москвав asdf asdf asdf asdf asdf asdf asdf')";
	char text3[512] = "INSERT INTO test1 ( 'Хуй', 121, 'Москва asdf asdfывsdf asdf asdf asdf asdf')";
	char text4[512] = "INSERT INTO test1 ( 'Внешняя паркова', 18, 'Москва asdf фываsdf asdf asdf asdf')";
	char text5[512] = "INSERT INTO test1 ( 'Интеллегенция', 180, 'Моаыфываasdf')";
	char text6[512] = "SELECT * FROM test1";
	char text7[512] = "DELETE FROM test1 WHERE Age=180";

	
	//r = queryHandler(text);
	r = queryHandler(text2);
	r = queryHandler(text3);
	r = queryHandler(text4);
	r = queryHandler(text5);

	r = queryHandler(text7);
	r = queryHandler(text6);


	printf_s("\n%d\n", r);

	return 0;
}

