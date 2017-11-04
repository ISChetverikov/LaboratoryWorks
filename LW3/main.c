#include <stdio.h>
#include "arrays.h"
#include "assignment.h"

int main() {
	int K;
	double X = 0, Y = 0;
	double min = 0, avg = 0;
	int returnCode = 0;
	double * arr = (double *) 0; // инициализация нулевым указателем

	// Создание и вывод массива
	K = createArray(&arr);
	printArray(arr, K);

	// Ввод ограничений для поиска минимума
	printf_s("Please input range of elements for seeking minima:");
	scanf_s("%lf %lf", &X, &Y);

	// Вывод результата работы функции поиска минимума
	if (minima(arr, K, X, Y, &min) == 0) {
		printf_s(
			"There is no elements greater or equal than %lf and less or equal %lf!\n",
			X,
			Y
		);
	}
	else {
		printf_s("Minima is %lf\n", min);
	}

	// Вывод результата работы функции поиска среднего
	if (average(arr, K, &avg) == 0) {
		printf_s("There is no elements after first maxima!\n");
	}
	else {
		printf_s("Average value is %lf\n", avg);
	}

	// Очистка памяти, занятого массивом
	freeArray(arr);
	return;
}