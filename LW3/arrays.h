#pragma once

#pragma region ������� ��� ������ � ���������

// �������� ������� � ���������� ������� � ����������
// params:
//     arr - (out) ����� ���������, � ������� ����� ��������� ����� ����������� � ������ ������� 
// return: ����� ���������� �������
int createArray(double ** arr);

// ������� ������, ����������� ��� ������
// params:
//     arr - ��������� �� ������
void freeArray(double * arr);

// ����� ������� � �������
// params:
//     arr - ��������� �� ������
//     N   - ����� �������
void printArray(double * arr, int N);

#pragma endregion