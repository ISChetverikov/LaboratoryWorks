#include <stdlib.h>
#include "Node.h"

#define L1_COUNT 3
#define L2_COUNT 4

int main() {
	Node * l1 = NULL;
	Node * l2 = NULL;

	int l1_coeffs[L1_COUNT] = { 7, -4, 2 };
	int l1_degrees[L1_COUNT] = { 0, 5, 2 };

	int l2_coeffs[L2_COUNT] = { -3, -5, 1, 1 };
	int l2_degrees[L2_COUNT] = { 5, 2, 3, 1 };

	l1 = Create(l1_coeffs, l1_degrees, L1_COUNT);
	l2 = Create(l2_coeffs, l2_degrees, L2_COUNT);

	Print(l1);
	Print(l2);
	Print(Sum(l1, l2));


	FreeAvl(l1);
	FreeAvl(l2);

	return 0;
}