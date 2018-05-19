#include "sql.h"
#include <string.h>
#include <stdlib.h>

// Ќачало обработки запроса
int queryHandler(char * query) {
	char * context;
	char * token;

	char * copy;

	copy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(copy, strlen(query) + 1, query);

	token = strtok_s(copy, " ", &context);
	if (!strcmp(token, "CREATE"))
		return queryCreate(query);

	if (!strcmp(token, "INSERT"))
		return queryInsert(query);

	free(copy);
	return 0;
}

// «апрос на создание таблицы
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
	tableHeader.fieldsArr = fieldHeaderArr;
	tableHeader.fieldsCount = fieldCount;

	CreateTable(tableName, tableHeader);

	free(tableName);
	free(queryCopy);
	free(fieldHeaderArr); // глубоко почистить
	return 0;
}

//«апрос на вставку данных в таблицу
int queryInsert(char * query) {

	char * context;
	char * token;
	char * tableName;
	char * queryCopy;
	char * fields;

	char * p1;
	char * p2;

	Row row;

	TableHeader tableHeader;
	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, " ", &context);
	if (strcmp(token, "INSERT")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "INTO")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	tableName = calloc(strlen(token) + 1, sizeof(char));
	strcpy_s(tableName, strlen(token) + 1, token);

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "(")) {
		free(tableName);
		free(queryCopy);
		return -1;
	}

	p1 = strstr(query, "(");// Ќашли скобочку
	p1++;
	p2 = strstr(query, ")");
	p2;
	if (p1 >= p2 || p2 == NULL) {
		free(tableName);
		free(queryCopy);
		return -1;
	}

	fields = calloc(p2-p1+1, sizeof(char));
	memcpy_s(fields, p2 - p1, p1, p2 - p1);
	fields[p2 - p1] = '\0';

	tableHeader = GetTableHeader(tableName);
	FitDataWithHeader(&row, tableHeader, fields);
	InsertTable(tableName, row);

	free(fields);
	free(tableName);
	free(queryCopy);
	return 0;
}

// ѕровер€ем соответствие вставл€емых данных с заголовком таблицы(возврат Row)
int FitDataWithHeader(Row * row, TableHeader tableHeader, char * fields) {
	Cell * cellsArr;
	int i = 0;
	char * context;
	char * token;
	void * tempData;
	int tempDataSize = 0;

	cellsArr = calloc(tableHeader.fieldsCount, sizeof(Cell));
	token = strtok_s(fields, ",", &context);
	
	while (token != NULL)
	{
		tempData = StringValueToBinary(token, tableHeader.fieldsArr[i].type, &tempDataSize);

		cellsArr[i].value = calloc(tempDataSize, 1);
		memcpy_s(cellsArr[i].value, tempDataSize, tempData, tempDataSize);
		cellsArr[i].size = tempDataSize;

		i++;
		token = strtok_s(NULL, ",", &context);
		free(tempData);
	}

	if (i != tableHeader.fieldsCount) {
		row = NULL;
		return 0;
	}

	row->cellsArr = cellsArr;
	row->cellsCount = tableHeader.fieldsCount;

	return 0;
}