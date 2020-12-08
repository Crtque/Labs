// UnitTest.cpp
// Лабораторная работа №2.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год
#include "MatrixClass.h"
#include <iostream>

using namespace std;

bool LaunchTest(int Width,int Height,int Req,int SwapIndexV,int SwapIndexH,bool PrintError=false) {
	Matrix* TestMatrix = new Matrix(Width, Height, Req);
	Matrix* ControlMatrix = new Matrix(Width, Height, Req);
	for (int i = 0; i < (Width * Height); i++) {
		TestMatrix->Append(i + 1);
		ControlMatrix->Append(i + 1);
	}
	ControlMatrix->Swap(SwapIndexV, SwapIndexH);

	TestMatrix->CheckEachCell(&Matrix::EqualsToComparing, &Matrix::Swap);
	if (TestMatrix->EqualsTo(ControlMatrix, false, false)) {
		return true;
	}
	else {
		if (PrintError) {
			cout << endl << "Несоотвествие значения " << TestMatrix->GetValueOfCell(SwapIndexV, SwapIndexH, false) << " ячейки строки: "
				<< SwapIndexV + 1 << " столбца: " << SwapIndexH + 1 << " со значением " << ControlMatrix->GetValueOfCell(SwapIndexV, SwapIndexH, false) << endl;
		}
		return false;
	}

}

bool Test_Matrix_3x3(bool PrintError=false)
{
	int Width = 3;
	int Height = 3;
	int Req = 5;

	int SwapIndexV = 1;
	int SwapIndexH = 1;

	return LaunchTest(Width,Height,Req,SwapIndexV,SwapIndexH,PrintError);

}

bool Test_Matrix_5x5(bool PrintError = false)
{
	int Width = 5;
	int Height = 5;
	int Req = 9;
	int SwapIndexV = 1;
	int SwapIndexH = 3;

	return LaunchTest(Width, Height, Req, SwapIndexV, SwapIndexH, PrintError);
}

bool Test_Matrix_9x9(bool PrintError = false)
{
	int Width = 9;
	int Height = 9;
	int Req = 81;
	int SwapIndexV = 8;
	int SwapIndexH = 8;

	return LaunchTest(Width, Height, Req, SwapIndexV, SwapIndexH, PrintError);
}

bool Test_Matrix_1x5(bool PrintError = false)
{
	int Width = 1;
	int Height = 5;
	int Req = 5;
	int SwapIndexV = 4;
	int SwapIndexH = 0;

	return LaunchTest(Width, Height, Req, SwapIndexV, SwapIndexH, PrintError);
}

bool Test_Matrix_5x2(bool PrintError = false)
{
	int Width = 5;
	int Height = 2;
	int Req = 7;
	int SwapIndexV = 1;
	int SwapIndexH = 1;

	return LaunchTest(Width, Height, Req, SwapIndexV, SwapIndexH, PrintError);
}

bool StartTest() {
	bool Result = true;
	typedef bool(*FunctionArr)(bool);
	FunctionArr Functions[] = { Test_Matrix_3x3, Test_Matrix_5x5,Test_Matrix_9x9,Test_Matrix_1x5,Test_Matrix_5x2 };
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
