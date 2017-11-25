#include <stdio.h>
#include <stdlib.h>

double * inputArray1(int * pLength) {
	double* array;
	
	printf_s("¬ведите количество элементов дл€ одномерного массива:\n");
	scanf_s("%d", pLength);

	array = calloc(*pLength, sizeof(double));

	printf_s("¬ведите элементы массива:\n");
	for (int i = 0; i < *pLength; i++)
	{
		scanf_s("%lf", array+i);
	}

	return array;
}

void printArray1(double * arr, int length) {
	for (int i = 0; i < length; i++)
	{
		printf_s("%.3lf ", *(arr+i));
	}
	printf_s("\n");

	return;
}

double avgBeforeFirstMax(double* array, int length) {
	double avg = array[0];
	double currentAvg = avg;
	double max = array[0];

	for (int i = 1; i < length; i++)
	{
		currentAvg = (currentAvg*i + array[i]) / (i + 1);
		if (max < array[i])
		{
			avg = currentAvg;
			max = array[i];
		}
	}

	return avg;
}

void reverseEnd(double* array, int length, int reversingCount) {

	if (reversingCount > length)
		return;

	double temp = 0;
	for (int i = length - reversingCount, j = length - 1; i < j; i++, j--)
	{
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}