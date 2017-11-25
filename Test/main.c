#include <stdio.h>
#include <locale.h>
#include "firstTask.h"

int main() {
	double * firstArray;
	int length;
	int reversingCount = 0;
	double avg = 0;
	setlocale(LC_CTYPE, "Russian");

	printf_s("=====================================\n");
	printf_s("========= Задача 1 ==================\n\n");

	firstArray = inputArray1(&length);
	printf_s("Веведенный массив:\n");
	printArray1(firstArray, length);

	avg = avgBeforeFirstMax(firstArray, length);
	printf_s("Среднее значение до первого максимального включительно: %0.4lf\n", avg);

	printf_s("Введите количество элементов для разворота конца массива:\n");
	scanf_s("%d", &reversingCount);
	reverseEnd(firstArray, length, reversingCount);
	printf_s("Массив с развернутым хвостом:\n");
	printArray1(firstArray, length);

	printf_s("=====================================\n");

	return 0;
}