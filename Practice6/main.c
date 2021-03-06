#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���������, ����������� ����� �� ���������
typedef struct Point {
	double x;
	double y;
} Point;

// ��������� �������� ����� �� ������, ������� ����� �������
Point * getProjection(Point first, Point second, Point point) {
	Point* result;
	double a = second.y - first.y;
	double b = first.x - second.x;
	double c = second.x*first.y - first.x*second.y;
	double d = a*point.y - b * point.x;

	if (a == 0 && b == 0)
		return NULL;

	result = calloc(1, sizeof(Point));
	if (a == 0)
	{
		result->y = -c / b;
		result->x = -d / b;
	}
	else
	{
		result->y = (a*d - b*c) / (a*a + b*b);
		result->x = (-b*result->y - c) / a;
	}
	return result;
}

// ��� �����, ������� �� ������, ��������� ��������� �� ������ ����� ����� �������
char isPointLiesBetween(Point first, Point second, Point point) {

	if (first.x == second.x && first.y == second.y) {
		return 0;
	}

	if (first.x == second.x) {
		if (first.y < point.y && second.y > point.y || first.y > point.y && second.y < point.y)
			return 1;
	}
	else {
		if (first.x < point.x && second.x > point.x || first.x > point.x && second.x < point.x)
			return 1;
	}

	return 0;
}

// ���������� ����� �������
double getDistance(Point first, Point second) {
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

// ����������� ���������� �� �������
double getDistanceToPolygon(Point * polygonVerticesArr, int count, Point point) {
	Point* pProjection;
	double result = 0;
	double distance = 0;

	// ���������� �� ������ ����� ������ � ��������� ������
	pProjection = getProjection(polygonVerticesArr[0], polygonVerticesArr[count - 1], point);

	if (isPointLiesBetween(polygonVerticesArr[0], polygonVerticesArr[count - 1], *pProjection)) {
		distance = getDistance(*pProjection, point);
			result = distance;
	}
	else {
		distance = getDistance(polygonVerticesArr[0], point);
			result = distance;

		distance = getDistance(polygonVerticesArr[count - 1], point);
		if (distance < result)
			result = distance;
	}

	// ��� ��������� �������
	for (int i = 1; i < count; i++)
	{
		pProjection = getProjection(polygonVerticesArr[i], polygonVerticesArr[i - 1], point);

		if (isPointLiesBetween(polygonVerticesArr[i], polygonVerticesArr[i - 1], *pProjection)) {
			distance = getDistance(*pProjection, point);
			if (distance < result)
				result = distance;
		}
		else {
			distance = getDistance(polygonVerticesArr[i], point);
			if (distance < result)
				result = distance;

			distance = getDistance(polygonVerticesArr[i - 1], point);
			if (distance < result)
				result = distance;
		}
			
	}

	free(pProjection);
	return result;
}

Point * inputPolygon(int * count) {
	Point * arr;

	printf_s("Please input count of polygon points:\n");
	scanf_s("%d", count);
	
	arr = calloc(*count, sizeof(Point));

	for (int i = 0; i < *count; i++) {
		printf_s("Input point of polygon:\t");
		scanf_s("%lf", &arr[i].x);
		scanf_s("%lf", &arr[i].y);
	}

	return arr;
}

int main() {
	int count;
	double d;
	Point * poly;
	Point p;
	
	printf_s("Please input point:\t");
	scanf_s("%lf", &p.x);
	scanf_s("%lf", &p.y);
	poly = inputPolygon(&count);

	d= getDistanceToPolygon(poly, count, p);

	printf_s("\nDistance:\t%lf\n", d);

	free(poly);
	return 0;
}