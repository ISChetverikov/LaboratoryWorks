#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// —труктура, описывающа€ точку на плоскости
typedef struct Point {
	double x;
	double y;
} Point;

// ѕолучение проекции точки на пр€мую, заданую двум€ точками
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

// ƒл€ точек, лежащих на пр€мой, провер€ет находитс€ ли трет€€ между двум€ другими
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

// –ассто€ние между точками
double getDistance(Point first, Point second) {
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

// ¬ысчитывает рассто€ние до контура
double getDistanceToPolygon(Point * polygonVerticesArr, int count, Point point) {
	Point* pProjection;
	double result = 0;
	double distance = 0;

	// –ассто€ние до пр€мой между первой и последней точкой
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

	// ¬се остальные стороны
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

	return result;
}

int main() {
	Point p = { -1, -1 };
	Point A[3] = { { 0,0 }, { 0,1 }, { 1,0 } };
	double d = getDistanceToPolygon(A, 3, p);

	printf_s("%lf\n", d);

	return 0;
}