#pragma once

typedef struct FullName {
	char * name;
	char * secondName;
	char * middleName;
} FullName;

typedef struct Date {
	short year;
	unsigned char month;
	unsigned char day;
} Date;

typedef struct Patient {
	FullName fullName;
	Date date;
	char * diagnosis;
} Patient;

void PrintPatient(Patient p);
Patient InputPatient(void);
void FreePatient(Patient p);
Patient* SearchPatient(Patient * patients, int count, char * diagnosis);