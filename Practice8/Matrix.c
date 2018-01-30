#include "Matrix.h"

#include <stdlib.h>
#include <stdio.h>

Matrix createNullMatrix() {
	Matrix matrix;

	matrix.m = 0;
	matrix.n = 0;
	matrix.arr = NULL;

	return matrix;
}

int isNullMatrix(Matrix matrix) {
	int result = 0;

	if (matrix.n == 0 && matrix.m == 0 && matrix.arr == NULL)
		result = 1;

	return result;
}

Matrix createRandomMatrix(int m, int n) {
	Matrix matrix;
	matrix.m = m;
	matrix.n = n;

	matrix.arr = calloc(m, sizeof(int*));
	for (int i = 0; i < m; i++)
		matrix.arr[i] = calloc(n, sizeof(int));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix.arr[i][j] = MIN_RAND_INT + rand() % (MAX_RAND_INT - MIN_RAND_INT);
		}
	}

	return matrix;
}
Matrix createManualMatrix() {
	Matrix matrix;

	printf_s("Please input m and n for new matrix:\n");
	scanf_s("%d %d", &matrix.m, &matrix.n);

	matrix.arr = calloc(matrix.m, sizeof(int*));
	for (int i = 0; i < matrix.m; i++)
		matrix.arr[i] = calloc(matrix.n, sizeof(int));

	printf_s("Please input elements of the matrix:\n");
	for (int i = 0; i < matrix.m; i++)
	{
		for (int j = 0; j < matrix.n; j++)
		{
			scanf_s("%d", &matrix.arr[i][j]);
		}
	}

	return matrix;
}

void clearMatrix(Matrix matrix) {
	for (int i = 0; i < matrix.m; i++)
	{
		free(matrix.arr[i]);
	}
	free(matrix.arr);

	return;
}

void printMatrix(Matrix matrix) {

	if (isNullMatrix(matrix)) {
		printf_s("{Dimensions of matrices was incorrect!}\n");
		return;
	}


	for (int i = 0; i < matrix.m; i++)
	{
		for (int j = 0; j < matrix.n; j++)
		{
			printf_s("\t%d", matrix.arr[i][j]);
		}

		printf_s("\n");
	}

	return;
}

Matrix addSubRoutine(Matrix matrix1, Matrix matrix2, int isAdd) {
	Matrix matrix;

	if (matrix1.m != matrix2.m && matrix1.n != matrix2.n)
		return createNullMatrix();

	matrix.m = matrix1.m;
	matrix.n = matrix1.n;

	matrix.arr = calloc(matrix.m, sizeof(int*));
	for (int i = 0; i < matrix.m; i++)
	{
		matrix.arr[i] = calloc(matrix.n, sizeof(int));
	}

	for (int i = 0; i < matrix.m; i++)
	{
		for (int j = 0; j < matrix.n; j++)
		{
			matrix.arr[i][j] = matrix1.arr[i][j];
			if (isAdd)
				matrix.arr[i][j] += matrix2.arr[i][j];
			else
				matrix.arr[i][j] -= matrix2.arr[i][j];
		}
	}

	return matrix;
}

Matrix add(Matrix matrix1, Matrix matrix2) {
	Matrix matrix;
	matrix = addSubRoutine(matrix1, matrix2, 1);
	return matrix;
}

Matrix sub(Matrix matrix1, Matrix matrix2) {
	Matrix matrix;
	matrix = addSubRoutine(matrix1, matrix2, 0);
	return matrix;
}

Matrix mul(Matrix matrix1, Matrix matrix2) {
	Matrix matrix;

	if (matrix1.n != matrix2.m)
		return createNullMatrix();

	matrix.m = matrix1.m;
	matrix.n = matrix2.n;

	matrix.arr = calloc(matrix.m, sizeof(int*));
	for (int i = 0; i < matrix.m; i++)
	{
		matrix.arr[i] = calloc(matrix.n, sizeof(int));
	}

	for (int i = 0; i < matrix.m; i++)
	{
		for (int j = 0; j < matrix.n; j++)
		{
			matrix.arr[i][j] = 0;
			for (int k = 0; k < matrix1.n; k++)
			{
				matrix.arr[i][j] += matrix1.arr[i][k] * matrix2.arr[k][j];
			}
		}
	}

	return matrix;
}
