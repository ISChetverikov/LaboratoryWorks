#pragma once

#pragma region ‘ункции дл€ работы с массивами

// —оздание массива и заполнение массива с клавиатуры
// params:
//     arr - (out) адрес указател€, в котором будет находитс€ адрес выделенного в пам€ти массива 
// return: длина созданного массива
int createArray(double ** arr);

// ќчистка пам€ти, выделенного под массив
// params:
//     arr - указатель на массив
void freeArray(double * arr);

// ¬ывод массива в консоль
// params:
//     arr - указатель на массив
//     N   - длина массива
void printArray(double * arr, int N);

#pragma endregion