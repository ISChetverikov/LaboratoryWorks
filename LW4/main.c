#include<stdio.h>
#include<stdlib.h>

void printArray(double *, int);
int inputArray(double **);
int deleteElements(double ** pArr, int length);

int main() {
	int length = 0;

	double * arr = NULL;
	length = inputArray(&arr);
	if (length == -1)
	{
		printf("Input array error has occured! Terminate programm...\n");
		return -1;
	}
	printf("\nInputed array:\n");
	printArray(arr, length);

	length = deleteElements(&arr, length);
	
	printf("\nResult array:\n");
	printArray(arr, length);

	free(arr);

	return 0;
}

void printArray(double * arr, int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%8.4lf ", *(arr + i));
	}
	printf("\n");
}

int inputArray(double ** pArr) {
	int n = 0;

	printf("Please input length:\n");
	scanf_s("%d", &n);

	if (n > 20 || n < 1) {
		*pArr = NULL;
		return -1;
	}

	if (*pArr == NULL)
		*pArr = calloc(n, sizeof(double));
	else
		*pArr = realloc(*pArr, n * sizeof(double));

	printf("Please input elements:\n");
	for (int i = 0; i < n; i++) {
		scanf_s("%lf", *pArr + i);
	}
}

int deleteElements(double ** pArr, int length) {
	int newLength = length;
	int temp = 0;
	double * arr = *pArr;

	for (int i = 1; i < newLength; i++)
	{
		if (arr[i] > 0 && arr[i - 1] < 0 && arr[i + 1] < 0) {
			temp = arr[i];
			for (int j = i + 1; j < newLength; j++) {
				arr[j - 1] = arr[j];
			}
			arr[newLength - 1] = temp;
			newLength--;
		}
	}

	*pArr = realloc(*pArr, newLength * sizeof(double));
	return newLength;
}