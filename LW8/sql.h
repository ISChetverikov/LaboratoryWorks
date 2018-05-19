#pragma once

#define BUFFER_SIZE 1024

typedef enum TYPE{INT, STRING} TYPE;

typedef struct FieldHeader {
	char * name;
	TYPE type;
} FieldHeader;

typedef struct TableHeader {
	FieldHeader * fieldsArr;
	int fieldsCount;
} TableHeader;

typedef struct Cell {
	void * value;
	int size;
} Cell;

typedef struct Row {
	Cell * cellsArr;
	int cellsCount;
} Row;


TableHeader global_tableHeader;

void CreateTable(char * name, TableHeader columns);
void InsertTable(char * name, Row values);
void DeleteWhere(char * name, FieldHeader field, void * value);
TableHeader GetTableHeader(char * tableName);
char * GetFileName(char * tableName);
TYPE StringToType(char * typeStr);
void * StringValueToBinary(char * text, TYPE type, int * dataSize);
void * ValueToBinary(void * value, TYPE type, int * dataSize);
