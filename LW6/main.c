#include "Patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define LAZY_USER1

int main() {
	Patient patient;
	Patient* pPatient;
	int count = 0;
	Patient patients[20];
	char * line[256];

	setlocale(LC_CTYPE, "Russian");
	system("chcp 1251");

#ifdef LAZY_USER

	patient.fullName.name = "Иван";
	patient.fullName.secondName = "Иванов";
	patient.fullName.middleName = "Иванович";
	patient.date.year = 1960;
	patient.date.month = 03;
	patient.date.day = 01;
	patient.diagnosis = "Рак";
	patients[0] = patient;

	patient.fullName.name = "Сидор";
	patient.fullName.secondName = "Сидоров";
	patient.fullName.middleName = "Сидорович";
	patient.date.year = 1970;
	patient.date.month = 11;
	patient.date.day = 21;
	patient.diagnosis = "ВИЧ";
	patients[1] = patient;

	patient.fullName.name = "Петр";
	patient.fullName.secondName = "Петров";
	patient.fullName.middleName = "Петрович";
	patient.date.year = 1980;
	patient.date.month = 10;
	patient.date.day = 10;
	patient.diagnosis = "Депрессия";
	patients[2] = patient;

	patient.fullName.name = "Михаил";
	patient.fullName.secondName = "Михайлов";
	patient.fullName.middleName = "Михайлович";
	patient.date.year = 1985;
	patient.date.month = 02;
	patient.date.day = 03;
	patient.diagnosis = "Волчанка";
	patients[3] = patient;

	patient.fullName.name = "Павел";
	patient.fullName.secondName = "Павлов";
	patient.fullName.middleName = "Павлович";
	patient.date.year = 1990;
	patient.date.month = 05;
	patient.date.day = 15;
	patient.diagnosis = "Пограничное расстройство личности";
	patients[4] = patient;

	patient.fullName.name = "Фэнь";
	patient.fullName.secondName = "Ли";
	patient.fullName.middleName = "Хао";
	patient.date.year = 1969;
	patient.date.month = 06;
	patient.date.day = 18;
	patient.diagnosis = "Рак";
	patients[5] = patient;

	patient.fullName.name = "Сюин";
	patient.fullName.secondName = "Тай";
	patient.fullName.middleName = "Бхэй";
	patient.date.year = 1969;
	patient.date.month = 6;
	patient.date.day = 19;
	patient.diagnosis = "Рак";
	patients[6] = patient;

	count = 7;
#else
	printf_s("Manual input of patients.\n\n");
	printf_s("Please input count of patients: ");
	
	gets(line);
	sscanf_s(line, "%d\n", &count);


	for (int i = 0; i < count; i++)
	{
		patients[i] = InputPatient();
	}

#endif

	printf_s("\n+--------------------------+");
	printf_s("\n|                          |");
	printf_s("\n|        PATIENTS          |");
	printf_s("\n|                          |");
	printf_s("\n+--------------------------+\n");

	for (int i = 0; i < count; i++)
	{
		PrintPatient(patients[i]);
	}

	printf_s("\n\nSearching the youngest patient with specified diagnosis:\n");
	printf_s("\nPlease input diagnosis: ");
	gets(line);

	pPatient = SearchPatient(patients, count, line);
	if (pPatient == NULL) {
		printf_s("Patient with this diagnosis have not come in...\n");
	}
	else {
		PrintPatient(*pPatient);
	}

#ifndef LAZY_USER

	for (int i = 0; i < count; i++)
	{
		FreePatient(patients[i]);
	}

	return 0;

#endif
}


