#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

// символ паддинга
#define SYMBOL '*'
// маршруты вписывания и выписывания
#define LEFT_TO_RIGHT 0
#define TOP_TO_BOTTOM 1

// структура ключа
typedef struct Key {
	char rowsCount;
	char columnsCount;
	char * rows;
	char * columns;
	char inputRoute;
	char outpuRoute;
} Key;

// Перевод перестановки с человеческого на удобный
char * getOrder(char * arr, char count) {
	char * result;
	result = calloc(count, sizeof(char));

	for (int i = 0; i < count; i++) {
		result[arr[i]-1] = i;
	}

	return result;
}

// Шифрование
char * encode(char * str, Key key) {
	int length = 0;
	char * tempFrame1;
	char * tempFrame2;
	char * rowsOrder;
	char * columnsOrder;
	int newLength = 0;
	char * result;

	char frameSize = 0;
	char framesCount = 0;

	length = strlen(str);

	frameSize = key.rowsCount*key.columnsCount;
	framesCount = length / frameSize;
	if (length % frameSize != 0) {
		framesCount++;
	}
	newLength = framesCount * frameSize;

	result = calloc(newLength+1, sizeof(char));
	strcpy_s(result, newLength+1, str);
	for (int i = length; i < newLength; i++) {
		result[i] = SYMBOL;
	}
	result[newLength] = '\0';

	tempFrame1 = calloc(frameSize, sizeof(char));
	tempFrame2 = calloc(frameSize, sizeof(char));

	rowsOrder = getOrder(key.rows, key.rowsCount);
	columnsOrder = getOrder(key.columns, key.columnsCount);

	for (int f = 0; f < framesCount; f++) {       

		// Маршрут вписывания
		if (key.inputRoute == TOP_TO_BOTTOM) {
			for (int j = 0; j < key.columnsCount; j++) {
				for (int i = 0; i < key.rowsCount; i++) {
					tempFrame1[j * key.rowsCount + i] = result[f * frameSize +  i * key.columnsCount + j];
				}
			}
		}
		else {
			memcpy(tempFrame1, result + f * frameSize, frameSize);
		}

		// Перестановка столбцов
		for (int i = 0; i < key.rowsCount; i++)
		{
			for (int j = 0; j < key.columnsCount; j++)
			{
				tempFrame2[key.columnsCount * i + j] = tempFrame1[key.columnsCount * i + columnsOrder[j]];
			}
		}

		// Перестановка строк
		for (int i = 0; i < key.rowsCount; i++) {
			for (int j = 0; j < key.columnsCount; j++) {
				tempFrame1[key.columnsCount * i + j] = tempFrame2[key.columnsCount * rowsOrder[i] + j];
			}
		}

		// Маршрут выписывания
		if (key.outpuRoute == TOP_TO_BOTTOM) {
			for (int j = 0; j < key.columnsCount; j++) {
				for (int i = 0; i < key.rowsCount; i++) {
					tempFrame2[j*key.rowsCount+i] = tempFrame1[i*key.columnsCount+j];
				}
			}
		}
		else {
			memcpy(tempFrame2, tempFrame1, frameSize);
		}

		memcpy(result + f * frameSize, tempFrame2, frameSize);
	}
	
	free(rowsOrder);
	free(columnsOrder);
	free(tempFrame1);
	free(tempFrame2);

	return result;
}

int main() {

	char str[1024] = "двойнаяперестановка";
	char columns[4] = {3, 1, 4, 2};
	char rows[5] = {3,2,4,1,5};
	char * encodedStr;
	Key key;

	key.columnsCount = 4;
	key.rowsCount = 5;
	key.columns = columns;
	key.rows = rows;
	key.inputRoute = LEFT_TO_RIGHT;
	key.outpuRoute = TOP_TO_BOTTOM;

	setlocale(LC_CTYPE, "Russian");

	gets(str);
	encodedStr = encode(str, key);
	puts(encodedStr);

	free(encodedStr);
	return 0;
}