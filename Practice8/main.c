#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"

int main() {
	Matrix m1, m2, m3;

	srand(time(NULL));

	printf("Program for testing operations with matrices\n");

	printf_s("\nManual matrix input test\n");
	printf_s("=============================================\n");
	m1 = createManualMatrix();
	printf_s("Inputted matrix:\n");
	printMatrix(m1);

	clearMatrix(m1);

	printf_s("\nAdding and substracting test for correct dimensions\n");
	printf_s("=============================================\n");
	printf_s("\nFirst matrix:\n");
	m1 = createRandomMatrix(4, 3);
	printMatrix(m1);

	printf_s("\nSecond matrix:\n");
	m2 = createRandomMatrix(4, 3);
	printMatrix(m2);

	printf_s("\nAdding result:\n");
	m3 = add(m1, m2);
	printMatrix(m3);
	clearMatrix(m3);

	printf_s("\nSubstracting result:\n");
	m3 = sub(m1, m2);
	printMatrix(m3);

	clearMatrix(m1);
	clearMatrix(m2);
	clearMatrix(m3);

	printf_s("\nAdding and substracting test for incorrect dimensions\n");
	printf_s("=============================================\n");
	printf_s("\nFirst matrix:\n");
	m1 = createRandomMatrix(4, 3);
	printMatrix(m1);

	printf_s("\nSecond matrix:\n");
	m2 = createRandomMatrix(2, 1);
	printMatrix(m2);

	printf_s("\nAdding result:\n");
	m3 = add(m1, m2);
	printMatrix(m3);
	clearMatrix(m3);

	printf_s("\nSubstracting result:\n");
	m3 = sub(m1, m2);
	printMatrix(m3);

	clearMatrix(m1);
	clearMatrix(m2);
	clearMatrix(m3);

	printf_s("\nMultiplying test for correct dimensions\n");
	printf_s("=============================================\n");
	printf_s("\nFirst matrix:\n");
	m1 = createRandomMatrix(3, 2);
	printMatrix(m1);

	printf_s("\nSecond matrix:\n");
	m2 = createRandomMatrix(2, 4);
	printMatrix(m2);

	printf_s("\nMultiplying result:\n");
	m3 = mul(m1, m2);
	printMatrix(m3);

	clearMatrix(m1);
	clearMatrix(m2);
	clearMatrix(m3);

	printf_s("\nMultiplying test for incorrect dimensions\n");
	printf_s("=============================================\n");
	printf_s("\nFirst matrix:\n");
	m1 = createRandomMatrix(3, 2);
	printMatrix(m1);

	printf_s("\nSecond matrix:\n");
	m2 = createRandomMatrix(3, 4);
	printMatrix(m2);

	printf_s("\nMultiplying result:\n");
	m3 = mul(m1, m2);
	printMatrix(m3);

	printf_s("\n");

	clearMatrix(m1);
	clearMatrix(m2);
	clearMatrix(m3);

	return 0;
}