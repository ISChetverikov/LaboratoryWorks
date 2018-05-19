#include "sql.h"
#include <string.h>
#include <stdlib.h>

// Начало обработки запроса
int queryHandler(char * query) {
	char * context;
	char * token;

	char * copy;

	copy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(copy, strlen(query) + 1, query);

	token = strtok_s(copy, " ", &context);
	if (!strcmp(token, "CREATE"))
		return queryCreate(query);

	free(copy);
	return 0;
}

// Запрос на создание таблицы
int queryCreate(char * query) {

	char * context;
	char * token;
	char * tableName;
	char * queryCopy;

	FieldHeader * fieldHeaderArr;
	int fieldCount = 0;
	TableHeader tableHeader;

	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, ", ", &context);
	if (strcmp(token, "CREATE")) {
		free(queryCopy);
		return -1;
	}
		
	token = strtok_s(NULL, ", ", &context);
	if (strcmp(token, "TABLE")) {
		free(queryCopy);
		return -1;
	}
		

	token = strtok_s(NULL, ", ", &context);
	tableName = calloc(strlen(token) + 1, sizeof(char));
	strcpy_s(tableName, strlen(token) + 1, token);

	token = strtok_s(NULL, ", ", &context);
	if (strcmp(token, "(")) {
		free(tableName);
		free(queryCopy);
		return -1;
	}
	
	fieldHeaderArr = calloc(0, sizeof(FieldHeader));
	token = strtok_s(NULL, ", ", &context);

	while (token != NULL && strcmp(token, ")"))
	{
		fieldHeaderArr = realloc(fieldHeaderArr, sizeof(FieldHeader) * (fieldCount + 1));

		fieldHeaderArr[fieldCount].name = calloc(strlen(token) + 1 , sizeof(char));
		strcpy_s(fieldHeaderArr[fieldCount].name, strlen(token) + 1, token);

		token = strtok_s(NULL, ", ", &context);
		fieldHeaderArr[fieldCount].type = StringToType(token);

		token = strtok_s(NULL, ", ", &context);
		fieldCount++;
	}
	tableHeader.FieldsArr = fieldHeaderArr;
	tableHeader.fieldsCount = fieldCount;

	CreateTable(tableName, tableHeader);

	free(tableName);
	free(queryCopy);

	return 0;
}