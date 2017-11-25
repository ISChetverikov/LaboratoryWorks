#include <stdio.h>
#include <locale.h>
#include "firstTask.h"
#include "secondTask.h"

int main() {
	double * firstArray;
	int length;
	int reversingCount = 0;
	double avg = 0;

	double ** secondArray;
	int n;
	double sumUnderDiagonal = 0;

	setlocale(LC_CTYPE, "Russian");

	printf_s("=====================================\n");
	printf_s("========= ������ 1 ==================\n\n");

	firstArray = inputArray1(&length);
	printf_s("\n��������� ������:\n");
	printArray1(firstArray, length);

	avg = avgBeforeFirstMax(firstArray, length);
	printf_s("\n������� �������� �� ������� ������������� ������������: %0.4lf\n", avg);

	printf_s("\n������� ���������� ��������� ��� ��������� ����� �������:\n");
	scanf_s("%d", &reversingCount);
	reverseEnd(firstArray, length, reversingCount);
	printf_s("\n������ � ����������� �������:\n");
	printArray1(firstArray, length);

	printf_s("\n=====================================\n\n");

	printf_s("=====================================\n");
	printf_s("========= ������ 2 ==================\n\n");

	secondArray = inputArray2(&n);
	printf_s("\n��������� ������:\n");
	printArray2(secondArray, n);

	sumUnderDiagonal = getSumUnderDiagonal(secondArray, n);
	printf_s("\n����� ��������� ��� ������� ����������, ������� ���������: %.4lf\n", sumUnderDiagonal);
	printf_s("\n=====================================\n");

	return 0;
}