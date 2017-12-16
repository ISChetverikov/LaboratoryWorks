#include <stdio.h>
#include <stdlib.h>

#pragma region Assignement

int minima(double * arr, int N, double X, double Y, double * result)
{
	double min = Y;
	int minIndex = -1;

	for (int i = 0; i < N; i++)
	{
		if (arr[i] <= min && arr[i] >= X) {
			min = arr[i];
			minIndex = i;
		}
	}

	if (minIndex == -1)
		return 0;

	*result = min;
	return 1;
}

int average(double * arr, int N, double * result) {
	double sum = 0;
	int indexOfMax = 0;
	double max = arr[0];

	for (int i = 1; i < N; i++)
	{
		if (max < arr[i]) {
			max = arr[i];
			indexOfMax = i;
		}
	}

	if (indexOfMax == N - 1)
		return 0;

	for (int i = indexOfMax + 1; i < N; i++)
	{
		sum += arr[i];
	}

	*result = sum / (N - indexOfMax - 1);
	return 1;
}

#pragma endregion

#pragma region Arrays

int createArray(double ** arr) {
	int N = 0;

	printf_s("Please input length of array:\n");
	scanf_s("%d", &N);
	*arr = calloc(N, sizeof(double));

	printf_s("Please input elements of array:\n");
	for (int i = 0; i < N; i++)
	{
		scanf_s("%lf", &(*arr)[i]);
	}

	return N;
}

void freeArray(double * arr) {
	free(arr);
}

void printArray(double * arr, int length) {
	for (int i = 0; i < length; i++)
	{
		printf_s("%f\t", arr[i]);
	}
	printf_s("\n");
}

#pragma endregion

int main() {
	int K;
	double X = 0, Y = 0;
	double min = 0, avg = 0;
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