#include "sql.h"
#include <string.h>
#include <stdlib.h>
#include "queryHandler.h"

// Ќачало обработки запроса
int queryHandler(char * query) {
	char * context;
	char * token;

	char * copy;

	if (!strcmp(query, ""))
		return -1;

	copy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(copy, strlen(query) + 1, query);

	token = strtok_s(copy, " ", &context);
	if (!strcmp(token, "CREATE"))
		return queryCreate(query);

	if (!strcmp(token, "INSERT"))
		return queryInsert(query);

	if (!strcmp(token, "SELECT"))
		return querySelect(query);

	if (!strcmp(token, "DELETE"))
		return queryDelete(query);

	if (!strcmp(token, "UPDATE"))
		return queryUpdate(query);

	if (!strcmp(token, "FILE"))
		return queryExecuteScript(query);

	if (!strcmp(token, "SORT"))
		return querySort(query);

	free(copy);
	return 0;
}

// «апрос на создание таблицы
int queryCreate(char * query) {

	char * context, *context2, *context3;
	char * token, *token2, *copyToken;// токен 1 по пробелам, затем по зап€тым; токен2 по пробелам в названи€х полей
	char * tableName;
	char * queryCopy;
	char * p;

	char buffer[BUFFER_SIZE];

	FieldHeader * fieldHeaderArr;
	int fieldCount = 0;
	TableHeader tableHeader;

	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, " ", &context);
	if (strcmp(token, "CREATE")) {
		free(queryCopy);
		return -1;
	}
		
	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "TABLE")) {
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
	
	p = strstr(context, ")");
	if (p == NULL) 
	{
		free(tableName);
		free(queryCopy);
		return -1;
	}
	p[0] = '\0';

	// в контексте пол€ с типами через зап€тую без скобочек
	fieldHeaderArr = calloc(0, sizeof(FieldHeader));
	
	token = strtok_s(context, ",", &context2);

	while (token != NULL)
	{
		fieldHeaderArr = realloc(fieldHeaderArr, sizeof(FieldHeader) * (fieldCount + 1));
		buffer[0] = '\0';

		token2 = strtok_s(token, " ", &context3);
		while (strcmp(context3, ""))
		{
			strcat_s(buffer, BUFFER_SIZE, token2);
			strcat_s(buffer, BUFFER_SIZE, " ");
			token2 = strtok_s(NULL, " ", &context3);
		}
		buffer[strlen(buffer) - 1] = '\0';
		// токен2 указывает на тип
		fieldHeaderArr[fieldCount].name = calloc(strlen(buffer)  + 1 , sizeof(char));
		strcpy_s(fieldHeaderArr[fieldCount].name, strlen(buffer) + 1, buffer);

		fieldHeaderArr[fieldCount].type = StringToType(token2);
		fieldCount++;

		token = strtok_s(NULL, ",", &context2);
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
		Select(tableName, &rows, &rowsCount, NULL);
		PrintTable(tableHeader, rows, rowsCount);

		free(tableName);
		free(queryCopy);
		return 0;
	}
	if (strcmp(token, "WHERE")) {
		free(tableName);
		free(queryCopy);
		return 1;
	}

	// Context - указатель на след токен
	ConditionFromText(context, tableHeader, &condition);
	Select(tableName, &rows, &rowsCount, &condition);

	PrintTable(tableHeader, rows, rowsCount);
	free(tableName);
	free(queryCopy);
	return 0;
}

int queryDelete(char * query) {
	char * context, *context2;
	char * token, *token2;
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
	if (strcmp(token, "DELETE")) {
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
		Delete(tableName, &rowsCount, NULL);

		free(tableName);
		free(queryCopy);
		return 0;
	}
	if (strcmp(token, "WHERE")) {
		free(tableName);
		free(queryCopy);
		return -1;
	}

	// Context - указатель на след токен
	ConditionFromText(context, tableHeader, &condition);
	Delete(tableName, &rowsCount, &condition);

	free(tableName);
	free(queryCopy);
	return 0;
}

int queryUpdate(char * query) {
	char * context, *context2;
	char * token, *token2;
	char * tableName;
	char * queryCopy;
	char * fields;
	TableHeader tableHeader;
	Condition conditionWhere, conditionSet;

	char * p;

	Row * rows;
	int rowsCount = 0;

	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, " ", &context);
	if (strcmp(token, "UPDATE")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "TABLE")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	tableName = calloc(strlen(token) + 1, sizeof(char));
	strcpy_s(tableName, strlen(token) + 1, token);

	tableHeader = GetTableHeader(tableName, NULL);

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "WHERE")) {
		free(tableName);
		free(queryCopy);
		return -1;
	}

	// Context - указатель на след токен
	p = strstr(context, "SET");
	if (p == NULL) {
		free(tableName);
		free(queryCopy);
		return -1;
	}

	p[0] = '\0';
	p += 4; // ѕропуск оставшихс€ букв слова SET

	ConditionFromText(context, tableHeader, &conditionWhere);
	ConditionFromText(p, tableHeader, &conditionSet);
	Update(tableName, &rowsCount, &conditionWhere, &conditionSet);

	free(tableName);
	free(queryCopy);
	return 0;
}

int queryExecuteScript(char * query) {
	char * context;
	char * token;
	char * fileName;
	char * queryCopy;

	FILE * pFile;

	char str[BUFFER_SIZE];
	char * readStr;

	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, " ", &context);
	if (strcmp(token, "FILE")) {
		free(queryCopy);
		return -1;
	}
	
	token = strtok_s(NULL, " ", &context);
	fileName = calloc(strlen(token) + 1, sizeof(char));
	strcpy_s(fileName, strlen(token) + 1, token);
	fopen_s(&pFile, fileName, "r");

	while (1) {
		readStr = fgets(str, BUFFER_SIZE, pFile);

		if (readStr == NULL)
		{
			if (feof(pFile) != 0)
			{
				break;
			}
			else
			{
				fclose(pFile);
				return -1;
			}
		}

		queryHandler(readStr);
	}

	free(fileName);
	return 0;
}

int querySort(char * query) {

	char * context;
	char * token;
	char * queryCopy;
	char * tableName;
	
	queryCopy = calloc(strlen(query) + 1, sizeof(char));
	strcpy_s(queryCopy, strlen(query) + 1, query);

	token = strtok_s(queryCopy, " ", &context);
	if (strcmp(token, "SORT")) {
		free(queryCopy);
		return -1;
	}

	token = strtok_s(NULL, " ", &context);
	tableName = calloc(strlen(token) + 1, sizeof(char));
	strcpy_s(tableName, strlen(token) + 1, token);

	token = strtok_s(NULL, " ", &context);
	if (strcmp(token, "BY")) {
		free(queryCopy);
		return -1;
	}

	// в контексте лежит название пол€, по которому сортируем
	Sort(tableName, context);


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

	for (int j = 0; j < columnsCount; j++)
	{
		widths[j] = strlen(tableheader.fieldsArr[j].name);
	}

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnsCount; j++)
		{
			width = GetLength(rows[i].cellsArr[j], tableheader.fieldsArr[j].type);

			if (width > widths[j])
				widths[j] = width;
		}
	}

	//while (tableWidth > 120) {
	//	tableWidth = 0;
	//	maxWidth = 0;

	//	for (int i = 0; i < columnsCount; i++)
	//	{
	//		if (maxWidth < widths[i]) {
	//			maxWidth = widths[i];
	//			maxWidthIndex = i;
	//		}
	//			
	//		tableWidth += widths[i] + 2; // «а черточку с пробелом
	//	}
	//	tableWidth += 2;

	//	if (tableWidth > 80)
	//		widths[maxWidthIndex] = (maxWidth % 2 == 0) ? maxWidth / 2 : maxWidth / 2 + 1;
	//}
	//


	// Ћини€
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

	// Ўапка
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
	
	// Ћини€
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

	// —ама таблица
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

	// Ћини€
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