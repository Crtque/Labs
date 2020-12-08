// UnitTest.cpp
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include "MatrixClass.h"
#include <iostream>

using namespace std;

bool LaunchTest(Matrix& ControlMatrix,int Width,int Height,bool PrintError=false) {
	bool Result = true;
	Matrix* TestMatrix = new Matrix(Width,Height);
	for (int i = 0; i < (Width * Width); i++) {
		TestMatrix->Append(i + 1);
	}
	TestMatrix->Sort();
	for (int i = 0; i < TestMatrix->GetNumberOfSorts(); i++) {
		if (TestMatrix->EqualsTo(&ControlMatrix, i, -1, PrintError)) {
			Result = true;
		}
		else {
			Result = false;
			break;
		}
	}
	delete TestMatrix;
	delete& ControlMatrix;
	return Result;
}

bool Test_Matrix_3x3(bool PrintError=false)
{
	int Width = 3;
	Matrix* ControlMatrix = new Matrix(Width,Width);
	int arr[9] = {1,6,3,4,5,2,7,8,9};
	for (int i = 0; i < 9; i++) {
		ControlMatrix->Append(arr[i]);
	}
	return LaunchTest(*ControlMatrix,Width,Width,PrintError);

}

bool Test_Matrix_5x5(bool PrintError = false)
{
	int Width = 5;
	Matrix* ControlMatrix = new Matrix(Width, Width);
	int arr[25] = { 1,20,15,14,10,6,7,9,8,5,11,12,13,4,3,16,17,18,19,2,21,22,23,24,25 };
	for (int i = 0; i < 25; i++) {
		ControlMatrix->Append(arr[i]);
	}
	return LaunchTest(*ControlMatrix, Width,Width, PrintError);
}


bool StartTest() {
	bool Result = true;
	typedef bool(*FunctionArr)(bool);
	FunctionArr Functions[] = { Test_Matrix_3x3, Test_Matrix_5x5};
	size_t CountOfFunctions = sizeof(Functions) / sizeof(Functions[0]);
	for (unsigned int i = 0; i < CountOfFunctions; i++) {
		if (!Functions[i](true)) {
			Result = false;
			std::cout << "Тестирование завершено с ошибкой. Ошибка в тесте: " << i + 1 << endl;
			break;
		}
	}
	if (Result) {
		std::cout << "Тестирование прошло успешно." << endl;
	}
	return Result;
}
