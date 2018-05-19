#pragma once

typedef enum TYPE{INT, STRING} TYPE;

typedef struct FieldHeader {
	char * name;
	TYPE type;
} FieldHeader;

typedef struct TableHeader {
	FieldHeader * FieldsArr;
	int fieldsCount;
} TableHeader;

typedef struct Cell {
	FieldHeader * field;
	void * value;
} Cell;

TableHeader global_tableHeader;

void CreateTable(char * name, TableHeader columns);
void InsertTable(char * name, Cell * values);
void DeleteWhere(char * name, FieldHeader field, void * value);
TYPE StringToType(char * typeStr);

int Test(char * name);