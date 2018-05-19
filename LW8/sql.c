#include "sql.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_NAME_EXT ".tdb"
#define DELIMITER ';'

// поле1(тип)
void WriteFields(FILE * pFile, TableHeader columns) {

	char * buffer;
	
	void * p = NULL;
	int nameLength = 0;
	int TYPE_LENGTH = sizeof(TYPE);
	int buffer_inc = 0;
	int newBufferSize = 0;

	buffer = calloc(1, sizeof(char));
	newBufferSize = 1;

	for (int i = 0; i < columns.fieldsCount; i++)
	{
		nameLength = strlen(columns.fieldsArr[i].name);
		buffer_inc = nameLength + TYPE_LENGTH + 2;
		newBufferSize += buffer_inc;
		buffer = realloc(buffer,  newBufferSize * sizeof(char));
		p = buffer + newBufferSize - buffer_inc - 1; // -1 because it started with 1
		
		memcpy_s(p, newBufferSize, columns.fieldsArr[i].name, nameLength);
		p = (char *)p + nameLength;

		memcpy_s(p, newBufferSize, "(", 1);
		p = (char*)p + 1;

		int * pType = &columns.fieldsArr[i].type;
		memcpy_s(p, newBufferSize, pType, TYPE_LENGTH);
		p = (char *)p + TYPE_LENGTH;

		memcpy_s(p, newBufferSize, ")", 1);
		p = (char*)p + 1;
	}
	memcpy_s(p, newBufferSize, "\n", 1);
	fwrite(buffer, sizeof(char), newBufferSize, pFile);

	free(buffer);
	return;
}

// Запись самих данных
void AppendData(FILE * pFile, Row data) {
	char * buffer;

	void * p = NULL;
	//int tempDataSize= 0;
	//void * tempData;
	int buffer_inc = 0;
	int newBufferSize = 0;

	buffer = calloc(1, sizeof(char));
	newBufferSize = 1;

	for (int i = 0; i < data.cellsCount; i++)
	{
		//tempData = ValueToBinary(data.cellsArr[i].value,  data.cellsArr[i].field->type, &tempDataSize);
		
		buffer_inc = data.cellsArr[i].size + 1;
		newBufferSize += buffer_inc;
		buffer = realloc(buffer, newBufferSize * sizeof(char));
		p = buffer + newBufferSize - buffer_inc - 1;

		memcpy_s(p, newBufferSize, data.cellsArr[i].value, data.cellsArr[i].size);
		p = (char *)p + data.cellsArr[i].size;

		memcpy_s(p, newBufferSize, ";", 1);
		p = (char*)p + 1;
	}
	memcpy_s(p, newBufferSize, "\n", 1);
	fwrite(buffer, sizeof(char), newBufferSize, pFile);

	free(buffer);
	return;
}

// Шапка таблицы: поле1(тип), поле2(тип),...(одна строчка)
// Затем сами данные
void CreateTable(char * name, TableHeader columns) {
	FILE * pFile;
	char * filename;
	int bufferSize = 0;

	bufferSize = strnlen_s(name, FILENAME_MAX) + sizeof(TABLE_NAME_EXT) + 1;
	filename = calloc(bufferSize, sizeof(char));
	strcpy_s(filename, bufferSize, name);
	strcat_s(filename, bufferSize, TABLE_NAME_EXT);

	fopen_s(&pFile, filename, "wb");

	WriteFields(pFile, columns);

	free(filename);
	fclose(pFile);
}

void InsertTable(char * name, Row data) {
	FILE * pFile;
	char * filename;
	int bufferSize = 0;

	bufferSize = strnlen_s(name, FILENAME_MAX) + sizeof(TABLE_NAME_EXT) + 1;
	filename = calloc(bufferSize, sizeof(char));
	strcpy_s(filename, bufferSize, name);
	strcat_s(filename, bufferSize, TABLE_NAME_EXT);

	int er = fopen_s(&pFile, filename, "ab+");
	fseek(pFile, 0, SEEK_END);
	
	AppendData(pFile, data);
	
	free(filename);
	fclose(pFile);
}

void DeleteWhere(char * name, FieldHeader field, void * value) {


	return;
}

int Select(char * name, Row ** rows, int * rowsCount) {

	FILE * pFile;
	char * filename;
	TableHeader tableHeader;
	Row row;
	int i = 0;

	*rows = calloc(0, sizeof(Row));
	filename = GetFileName(name);

	fopen_s(&pFile, filename, "rb");

	fseek(pFile, 0, SEEK_END);
	int fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	tableHeader = GetTableHeader(name, pFile);

	while(ftell(pFile)< fileSize)
	{
		GetDataFromFile(pFile, tableHeader, &row);
		*rows = realloc(*rows, (i + 1)* sizeof(Row));
		(*rows)[i] = row;
		i++;
	}
	((int *)rowsCount)[0] = i;

	free(filename);
	fclose(pFile);

	return i;
}

void SelectWhere(char * name, Condition condition) {

	FILE * pFile;
	char * filename;
	
	filename = GetFileName(name);

	int er = fopen_s(&pFile, filename, "rb");
	GetTableHeader(name, pFile);
	
	free(filename);
	fclose(pFile);
	
	return;
}

TableHeader GetTableHeader(char * tableName, FILE * pFile) {

	char * filename;
	int numberOfField = 0;
	TableHeader tableHeader;

	char buffer[BUFFER_SIZE];
	char name[BUFFER_SIZE];
	char c;
	int  type;
	int i, j;
	FieldHeader * arr;
	int fieldsCount;
	int isNeedOpenFile = 0;
	//tableHeader.tableName = calloc(strlen(tableName) + 1, sizeof(char));
	//strcpy_s(tableHeader.tableName, strlen(tableName) + 1, tableName);

	isNeedOpenFile = (pFile == NULL);

	arr = calloc(0, sizeof(FieldHeader));
	fieldsCount = 0;

	filename = GetFileName(tableName);

	if (isNeedOpenFile)
		fopen_s(&pFile, filename, "rb");
	fread_s(buffer, BUFFER_SIZE, sizeof(char), BUFFER_SIZE, pFile);
	
	j = 0;
	c = buffer[j];

	while (c != '\n') {
		i = 0;

		while (c != '(')
		{
			name[i] = c;
			i++;

			j++;
			c = buffer[j];
		}
		name[i] = '\0';
		j++;
		type = *(int *)(buffer + j);
		j += 5;
		c = buffer[j];

		arr = realloc(arr, (fieldsCount + 1) * sizeof(FieldHeader));
		arr[fieldsCount].name = calloc(strlen(name) + 1, sizeof(char));
		strcpy_s(arr[fieldsCount].name, strlen(name) + 1, name);
		arr[fieldsCount].type = type;
		fieldsCount++;
	}
	fseek(pFile, j + 1, SEEK_SET);

	tableHeader.fieldsArr = arr;
	tableHeader.fieldsCount = fieldsCount;

	free(filename);
	if (isNeedOpenFile)
		fclose(pFile);

	return tableHeader;
}

int GetDataFromFile(FILE * pFile, TableHeader tableHeader, Row * row) {
	
	char buffer[BUFFER_SIZE];
	TYPE type;
	int size;
	void * tempValue;
	Cell * arr;
	int i = 0;
	char * p;
	long position;

	arr = calloc(tableHeader.fieldsCount, sizeof(Cell));

	position = ftell(pFile);
	fread_s(buffer, BUFFER_SIZE, sizeof(char), BUFFER_SIZE, pFile);
	p = buffer;

	while (*p != '\n') 
	{
		tempValue = GetValueFromString(p, tableHeader.fieldsArr[i].type, &size);
		arr[i].value = tempValue;
		arr[i].size = size;

		p = p + size + 1;
		i++;
	}
	row->cellsCount = i;
	row->cellsArr = arr;

	fseek(pFile, position + p - buffer + 1, SEEK_SET);
	return 0;
}

void * GetValueFromString(char * str, TYPE type, int * size) {
	void * result;
	int length = 0;
	void * p;

	if (type == STRING) {
		p = memchr(str, DELIMITER, BUFFER_SIZE);
		length = (char*)p - str;
		size[0] = length;

		result = calloc(length, sizeof(char));
		memcpy_s(result, length, str, length);

		return result;
	}

	if (type == INT) {
		result = calloc(1, sizeof(int));
		size[0] = sizeof(int);
		((int*)result)[0] = (int *)str[0];

		return result;
	}

	return NULL;
}

// Helpers
char * GetFileName(char * tableName) {
	char * filename;
	int bufferSize = 0;

	bufferSize = strnlen_s(tableName, FILENAME_MAX) + sizeof(TABLE_NAME_EXT) + 1;
	filename = calloc(bufferSize, sizeof(char));
	strcpy_s(filename, bufferSize, tableName);
	strcat_s(filename, bufferSize, TABLE_NAME_EXT);

	return filename;
}

TYPE StringToType(char * typeStr) {

	if (!strcmp(typeStr, "STRING"))
		return STRING;

	if (!strcmp(typeStr, "INT"))
		return INT;

	return -1;
}

// Текстовые поля превращает в бинарные
void * StringValueToBinary(char * text, TYPE type, int * dataSize) {
	void * result;
	int length = 0;
	char * p1;
	char * p2;

	if (type == STRING) {
		p1 = strchr(text, '\'');
		p1++;
		p2 = strrchr(text, '\'');

		length = p2-p1;
		dataSize[0] = length;

		result = calloc(length, sizeof(char));
		memcpy_s(result, length, p1, length);
		return result;
	}

	if (type == INT) {
		result = calloc(1, sizeof(int));
		dataSize[0] = sizeof(int);
		((int*)result)[0] = atoi(text);
		return result;
	}

	return NULL;

}

// Проверяем соответствие вставляемых данных с заголовком таблицы(возврат Row)
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

// Перевод условия из текста в тип COndition
int ConditionFromText(char * conditionText, TableHeader tableHeader, Condition * condition) {
	char * copy;
	char * context;
	char * name, * valueStr;
	int i = 0;

	FieldHeader fieldHeader;
	Cell cell;

	copy = calloc(strlen(conditionText) + 1, sizeof(char));
	strcpy_s(copy, strlen(conditionText) + 1, conditionText);

	name = strtok_s(copy, "=", &context);
	if (name == NULL) {
		free(copy);
		return -1;
	}
	
	for (i = 0; i < tableHeader.fieldsCount; i++)
	{
		if (!strcmp(tableHeader.fieldsArr[i].name, name))
			break;
	}
	if(i == tableHeader.fieldsCount) {
		free(copy);
		return -1;
	}
	fieldHeader = tableHeader.fieldsArr[i];

	valueStr = strtok_s(NULL, "=", &context);
	if (valueStr == NULL) {
		free(copy);
		return -1;
	}
	cell.value = StringValueToBinary(valueStr, fieldHeader.type, &cell.size);
	condition->cell = cell;
	condition->fieldHeader = fieldHeader;

	free(copy);
	return 0;
}

int GetLength(Cell cell, TYPE type) {
	int result = 0;
	int remain = 0;

	switch (type)
	{
	case STRING:
		return cell.size;
	case INT:
		
		remain = *((int*)cell.value);
		if (remain == 0)
			return 1;

		while (remain != 0)
		{
			remain = remain / 10;
			result++;
		}

		return result;
	default:
		return result;
	}
}

char * BinaryToStringValue(Cell cell, TYPE type) {
	char * result = NULL;
	char buffer[33];
	switch (type)
	{
	case STRING:
		result = calloc(cell.size + 1, sizeof(char));
		memcpy_s(result, cell.size, cell.value, cell.size);
		result[cell.size] = '\0';

		break;
	case INT:
		_itoa_s(*(int *)cell.value, buffer, 33, 10);
		result = calloc(strlen(buffer) + 1, sizeof(char));
		strcpy_s(result, strlen(buffer) + 1, buffer);
	default:
		break;
	}

	return result;
}