#include <stdlib.h>
#include <stdio.h>
#include "sql.h"
#include "queryHandler.h"
#include <locale.h>
#include <string.h>


int main() {
	int r = 0;
	char query[1024];

	setlocale(LC_ALL, "Russian");
	printf_s("Test program!\n");
	system("chcp 1251");
	
	char text[512] = "CREATE TABLE test1 ( Name STRING, Age INT, publisher STRING )";
	char text2[512] = "INSERT INTO test1 ( '������ ��������� �������', 10, '������� asdf asdf asdf asdf asdf asdf asdf')";
	char text3[512] = "INSERT INTO test1 ( '����', 121, '������ asdf asdf��sdf asdf asdf asdf asdf')";
	char text4[512] = "INSERT INTO test1 ( '���-���', 18, '������ asdf ����sdf asdf asdf asdf')";
	char text5[512] = "INSERT INTO test1 ( '�������������', 180, '��������asdf')";

	char text6[512] = "SELECT * FROM test1";
	char text7[512] = "DELETE FROM test1 WHERE publisher='������ asdf ����sdf asdf asdf asdf'";
	char text8[512] = "UPDATE TABLE test1 WHERE Name='��� ���' SET Name='��� ��� ��'";

	r = queryHandler(text);
	r = queryHandler(text2);
	//r = queryHandler(text3);
	//r = queryHandler(text4);
	//r = queryHandler(text5);

	//r = queryHandler(text8);
	//r = queryHandler(text6);

	while (1) {
		gets(query);
		queryHandler(query);

		if (!strcmp(query, "quit"))
			break;
	}

	printf_s("\n\nThe end...\n");

	return 0;
}

