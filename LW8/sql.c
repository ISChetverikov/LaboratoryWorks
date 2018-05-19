#include "sql.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		nameLength = strlen(columns.FieldsArr[i].name);
		buffer_inc = nameLength + TYPE_LENGTH + 2;
		newBufferSize += buffer_inc;
		buffer = realloc(buffer,  newBufferSize * sizeof(char));
		p = buffer + newBufferSize - buffer_inc - 1; // -1 because it started with 1
		
		memcpy_s(p, newBufferSize, columns.FieldsArr[i].name, nameLength);
		p = (char *)p + nameLength;

		memcpy_s(p, newBufferSize, "(", 1);
		p = (char*)p + 1;

		int * pType = &columns.FieldsArr[i].type;
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
void WriteData(FILE * pFile, Cell * data) {

	fwrite(data, sizeof(char), strlen(data), pFile);
	fwrite("\n", sizeof(char), 1, pFile);
	 
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

void InsertTable(char * name, Cell * data) {
	FILE * pFile;
	char * filename;
	int bufferSize = 0;

	bufferSize = strnlen_s(name, FILENAME_MAX) + sizeof(TABLE_NAME_EXT) + 1;
	filename = calloc(bufferSize, sizeof(char));
	strcpy_s(filename, bufferSize, name);
	strcat_s(filename, bufferSize, TABLE_NAME_EXT);

	int er = fopen_s(&pFile, filename, "ab+");
	fseek(pFile, 0, SEEK_END);
	//Preparing of Data needs
	WriteData(pFile, data);
	
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
		if (strcmp(global_tableHeader.FieldsArr[i].name, fieldName))
			numberOfField = i;
	}
	
	free(filename);
	fclose(pFile);
	
	return;
}

TYPE StringToType(char * typeStr) {

	if (!strcmp(typeStr, "STRING"))
		return STRING;

	if (!strcmp(typeStr, "INT"))
		return INT;

	return -1;
}

// Testing create table - don`t need
int Test(char * name) {
	FILE * pFile;
	char * filename;
	int bufferSize = 0;

	bufferSize = strnlen_s(name, FILENAME_MAX) + sizeof(TABLE_NAME_EXT) + 1;
	filename = calloc(bufferSize, sizeof(char));
	strcpy_s(filename, bufferSize, name);

	strcat_s(filename, bufferSize, TABLE_NAME_EXT);
	fopen_s(&pFile, filename, "rb");

	fread(&bufferSize, sizeof(bufferSize), 1, pFile);

	fclose(pFile);
	return bufferSize;
}