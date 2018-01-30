#pragma once

#define MIN_RAND_INT 0
#define MAX_RAND_INT 10

typedef struct Matrix {
	int ** arr;
	int m;
	int n;
} Matrix;

Matrix createRandomMatrix(int m, int n);
Matrix createManualMatrix();

void clearMatrix(Matrix matrix);
void printMatrix(Matrix matrix);

Matrix add(Matrix matrix1, Matrix matrix2);
Matrix mul(Matrix matrix1, Matrix matrix2);
Matrix sub(Matrix matrix1, Matrix matrix2);