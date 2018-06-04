

#pragma once

#include <stdio.h>

#define BUFFER_SIZE 1024

typedef enum TYPE{INT, STRING} TYPE;

typedef struct FieldHeader {
	char * name;
	TYPE type;
} FieldHeader;

typedef struct TableHeader {
	FieldHeader * fieldsArr;
	int fieldsCount;
	//char * tableName;
} TableHeader;

typedef struct Cell {
	void * value;
	int size;
} Cell;


typedef struct Row {
	Cell * cellsArr;
	int cellsCount;
} Row;

typedef struct Condition {
	FieldHeader fieldHeader;
	// May be onli number of header?
	Cell cell;
} Condition;

void CreateTable(char * name, TableHeader columns);
void InsertTable(char * name, Row values);
int Select(char * name, Row ** rows, int * rowsCount, Condition * condition);
void Delete(char * name, int * rowsCount, Condition * condition);
void Update(char * name, int * rowsCount, Condition * conditionWhere, Condition * conditionSet);
int Sort(char * tableName, char * fieldName);

// Helpers
void WriteFields(FILE * pFile, TableHeader columns);
void AppendData(FILE * pFile, Row data);
TableHeader GetTableHeader(char * tableName, FILE * pFile);
char * GetFileName(char * tableName);
TYPE StringToType(char * typeStr);
void * StringValueToBinary(char * text, TYPE type, int * dataSize);
int FitDataWithHeader(Row * row, TableHeader tableHeader, char * fields);
int ConditionFromText(char * conditionText, TableHeader tableHeader, Condition * condition);
void * GetValueFromString(char * str, TYPE type, int * size);
int GetLength(Cell cell, TYPE type);
char * BinaryToStringValue(Cell cell, TYPE type);
int MoveFileMemory(FILE * pFile, int positionBefore, int positionAfter, int positionInsert);
int UpdateFileCell(FILE * pFile, int position, Cell oldCell, Cell newCell, int * newFileSize);
int Compare(Row left, Row right, int fieldNo, TYPE type);