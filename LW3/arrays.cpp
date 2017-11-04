#include <stdio.h>
#include <stdlib.h>

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