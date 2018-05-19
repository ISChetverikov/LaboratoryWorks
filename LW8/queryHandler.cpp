#include "sql.h"
#include <string.h>
#include <stdlib.h>
#include "queryHandler.h"

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

	if (!strcmp(token, "INSERT"))
		return queryInsert(query);

	if (!strcmp(token, "SELECT"))
		return querySelect(query);

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
	tableHeader.fieldsArr = fieldHeaderArr;
	tableHeader.fieldsCount = fieldCount;

	CreateTable(tableName, tableHeader);

	free(tableName);
	free(queryCopy);
	free(fieldHeaderArr); // глубоко почистить
	return 0;
}

//Запрос на вставку данных в таблицу
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

	p1 = strstr(query, "(");// Нашли скобочку
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

	tableHeader = GetTableHeader(tableName, NULL);
	FitDataWithHeader(&row, tableHeader, fields);
	InsertTable(tableName, row);

	free(fields);
	free(tableName);
	free(queryCopy);
	return 0;
}

int querySelect(char * query) {

	char * context, * context2;
	char * token, * token2;
	char * tableName;
	char * queryCopy;
	char * fields;
	TableHeader tableHeader;
	Condition condition;

	Row * rows;
	int rowsCount = 0;

	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, " ", &context);
	if (strcmp(token, "SELECT")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "*")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "FROM")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	tableName = calloc(strlen(token) + 1, sizeof(char));
	strcpy_s(tableName, strlen(token) + 1, token);

	tableHeader = GetTableHeader(tableName, NULL);

	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		Select(tableName, &rows, &rowsCount);
		PrintTable(tableHeader, rows, rowsCount);
		free(tableName);
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	ConditionFromText(token, tableHeader, &condition);
	SelectWhere(tableName, condition);

	return 0;
}

void PrintTable(TableHeader tableheader, Row * rows, int rowsCount) {

	TYPE type;
	int width;
	int columnsCount = tableheader.fieldsCount;
	int * widths = calloc(columnsCount, sizeof(int));
	int tableWidth = 81;
	int maxWidth = 0;
	int maxWidthIndex = 0;
	char * cellText;

	int margin = 0;
	int leftMargin = 0;
	int rightMargin = 0;

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnsCount; j++)
		{
			width = GetLength(rows[i].cellsArr[j], tableheader.fieldsArr[j].type);

			if (width > widths[j])
				widths[j] = width;
		}
	}

	while (tableWidth > 80) {
		tableWidth = 0;

		for (int i = 0; i < columnsCount; i++)
		{
			if (maxWidth < widths[i]) {
				maxWidth = widths[i];
				maxWidthIndex = i;
			}
				
			tableWidth += widths[i] + 2; // За черточку с пробелом
		}
		tableWidth += 2;

		if (tableWidth > 80)
			widths[maxWidthIndex] = (maxWidth % 2 == 0) ? maxWidth / 2 : maxWidth / 2 + 1;
	}
	
	// Линия
	printf_s("\n+");
	for (int i = 0; i < columnsCount; i++)
	{
		for (int j = 0; j < widths[i] + 2; j++)
		{
			printf_s("-");
		}
		printf_s("+");
	}
	printf_s("\n");

	// Шапка
	printf_s("|");

	for (int j = 0; j < columnsCount; j++)
	{
		cellText = tableheader.fieldsArr[j].name;

		margin = widths[j] + 2 - strlen(cellText);
		leftMargin = margin/2;
		rightMargin = (margin % 2 == 0) ? margin/2 : margin/2 + 1;

		for (int k = 0; k < leftMargin; k++) {
			printf_s(" ");
		}
		printf_s("%s", cellText);
		for (int k = 0; k < rightMargin; k++) {
			printf_s(" ");
		}
		printf_s("|");

		free(cellText);
	}
	printf_s("\n");
	
	// Линия
	printf_s("+");
	for (int i = 0; i < columnsCount; i++)
	{
		for (int j = 0; j < widths[i] + 2; j++)
		{
			printf_s("-");
		}
		printf_s("+");
	}
	printf_s("\n");

	// Сама таблица
	for (int i = 0; i < rowsCount; i++)
	{
		printf_s("|");
		
		for (int j = 0; j < columnsCount; j++)
		{
			cellText = BinaryToStringValue(rows[i].cellsArr[j], tableheader.fieldsArr[j].type);
			printf_s(" %s", cellText);
			for (int k = 0; k < widths[j] + 2 - strlen(cellText) - 1; k++) {
				printf_s(" ");
			}
			printf_s("|");
			free(cellText);
		}
		printf_s("\n");
	}

	// Линия
	printf_s("+");
	for (int i = 0; i < columnsCount; i++)
	{
		for (int j = 0; j < widths[i] + 2; j++)
		{
			printf_s("-");
		}
		printf_s("+");
	}
	printf_s("\n");

	return;
}