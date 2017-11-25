#include <stdio.h>
#include <stdlib.h>

double ** inputArray2(int * pN) {
	double** array;

	printf_s("¬ведите количество строк квадратной матрицы:\n");
	scanf_s("%d", pN);

	array = calloc(*pN, sizeof(double *));
	for (int i = 0; i < *pN; i++)
	{
		array[i] = calloc(*pN, sizeof(double));
	}

	printf_s("¬ведите элементы массива:\n");
	for (int i = 0; i < *pN; i++)
	{
		for (int j = 0; j < *pN; j++)
		{
			scanf_s("%lf", &array[i][j]);
		}
	}

	return array;
}

void printArray2(double ** array, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf_s("%.3lf ", array[i][j]);
		}
		printf_s("\n");
	}

	return;
}

double getSumUnderDiagonal(double ** array, int n) {
	double result = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			result += array[i][j];
		}
	}

	return result;
}