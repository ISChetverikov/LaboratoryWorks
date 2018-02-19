#include "Patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintPatient(Patient p) {

	printf_s("==========================================================================\n");
	printf_s("Patient:\n");
	printf_s("\t%s %s %s\n", p.fullName.secondName, p.fullName.name, p.fullName.middleName);
	printf_s("\tDay of birth:\t%02d.%02d.%04d\n", p.date.day, p.date.month, p.date.year);
	printf_s("\tDiagnosis:\t%s\n", p.diagnosis);
	printf_s("==========================================================================\n");

	return;
}

Patient * SearchPatient(Patient * patients, int count, char * diagnosis) {
	Patient * pResult;
	char timeStr[9];
	char youngestTimeStr[9] = "00000000";

	pResult = NULL;

	for (size_t i = 0; i < count; i++)
	{
		if (!strcmp(patients[i].diagnosis, diagnosis)) {
			sprintf_s(
				timeStr,
				9,
				"%04d%02d%02d",
				patients[i].date.year,
				patients[i].date.month,
				patients[i].date.day
			);

			if (strcmp(timeStr, youngestTimeStr) > 0) {
				strcpy_s(youngestTimeStr, 9, timeStr);

				pResult = &patients[i];
			}
		}
	}

	return pResult;
}

Patient InputPatient(void) {
	char line[80];
	int number;
	Patient patient;

	printf_s("Patient input\n");
	printf_s("\tName: ");
	gets(line);
	patient.fullName.name = calloc(strlen(line) + 1, sizeof(char));
	strcpy_s(patient.fullName.name, strlen(line) + 1, line);

	printf_s("\tSecond name: ");
	gets(line);
	patient.fullName.secondName = calloc(strlen(line) + 1, sizeof(char));
	strcpy_s(patient.fullName.secondName, strlen(line) + 1, line);

	printf_s("\tMiddle name: ");
	gets(line);
	patient.fullName.middleName = calloc(strlen(line) + 1, sizeof(char));
	strcpy_s(patient.fullName.middleName, strlen(line) + 1, line);

	printf_s("\tYear: ");
	gets(line);
	sscanf_s(line, "%d\n", &number);
	patient.date.year = number;

	printf_s("\tMonth: ");
	gets(line);
	sscanf_s(line, "%d\n", &number);
	patient.date.month = number;

	printf_s("\tDay: ");
	gets(line);
	sscanf_s(line, "%d\n", &number);
	patient.date.day = number;
	
	printf_s("\tDiagnosis: ");
	gets(line);
	patient.diagnosis = calloc(strlen(line) + 1, sizeof(char));
	strcpy_s(patient.diagnosis, strlen(line) + 1, line);

	printf_s("\n");

	return patient;
}

void FreePatient(Patient p) {
	free(p.diagnosis);
	free(p.fullName.name);
	free(p.fullName.secondName);
	free(p.fullName.middleName);
}