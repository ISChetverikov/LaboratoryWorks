#include "sql.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_NAME_EXT ".tdb"

// поле1(тип);
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
	global_tableHeader = columns;

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

void SelectWhere(char * name, char * fieldName, void * value) {

	FILE * pFile;
	char * filename;
	int bufferSize = 0;
	int numberOfField = 0;

	bufferSize = strnlen_s(name, FILENAME_MAX) + sizeof(TABLE_NAME_EXT) + 1;
	filename = calloc(bufferSize, sizeof(char));
	strcpy_s(filename, bufferSize, name);
	strcat_s(filename, bufferSize, TABLE_NAME_EXT);

	int er = fopen_s(&pFile, filename, "rb");
	
	for (int i = 0; i < global_tableHeader.fieldsCount; i++)
	{
		if (strcmp(global_tableHeader.fieldsArr[i].name, fieldName))
			numberOfField = i;
	}
	
	free(filename);
	fclose(pFile);
	
	return;
}

TableHeader GetTableHeader(char * tableName) {

	FILE * pFile;
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

	arr = calloc(0, sizeof(FieldHeader));
	fieldsCount = 0;

	filename = GetFileName(tableName);

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

	tableHeader.fieldsArr = arr;
	tableHeader.fieldsCount = fieldsCount;

	free(filename);
	fclose(pFile);

	return tableHeader;
}

char * GetDataFromFile(FILE * pFile) {

	return;
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