// UnitTest.cpp
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год
#include "MathFunction.h"
#include <iostream>

using namespace std;

bool DoubleIsEqual(double x, double y) {
	return std::fabs(x - y) < 0.01;
}

const double HighRange = 10.0;
const double LowRange = 0;
const int Divides = 9000;
bool TestX_IN_Power5_Trap()
{
	const int HighDeegreeOfX = 5;
	double* x = new double[HighDeegreeOfX + 1];
	x[5] = 1.0;
	x[4] = 0;
	x[3] = 0;
	x[2] = 0;
	x[1] = 0;
	x[0] = 0;
	MathFunction* TestFunc = new MathFunction(x, HighDeegreeOfX, HighRange, LowRange, Divides);
	TestFunc->ValueOfRealInt(LowRange, HighRange);
	TestFunc->TrapInt(LowRange, HighRange, Divides);
	return DoubleIsEqual(TestFunc->RealIntValue, TestFunc->ValueOfTrapInt);
}
bool TestX_IN_Power4_Trap()
{
	const int HighDeegreeOfX = 4;
	double* x = new double[HighDeegreeOfX + 1];
	x[4] = 1.0;
	x[3] = 0;
	x[2] = 0;
	x[1] = 0;
	x[0] = 0;
	MathFunction* TestFunc = new MathFunction(x, HighDeegreeOfX, HighRange, LowRange, Divides);
	TestFunc->ValueOfRealInt(LowRange, HighRange);
	TestFunc->TrapInt(LowRange, HighRange, Divides);
	return DoubleIsEqual(TestFunc->RealIntValue, TestFunc->ValueOfTrapInt);
}
bool TestX_IN_Power3_Trap()
{
	const int HighDeegreeOfX = 3;
	double* x = new double[HighDeegreeOfX + 1];
	x[3] = 1.0;
	x[2] = 0;
	x[1] = 0;
	x[0] = 0;
	MathFunction* TestFunc = new MathFunction(x, HighDeegreeOfX, HighRange, LowRange, Divides);
	TestFunc->ValueOfRealInt(LowRange, HighRange);
	TestFunc->TrapInt(LowRange, HighRange, Divides);
	return DoubleIsEqual(TestFunc->RealIntValue, TestFunc->ValueOfTrapInt);
}
bool TestX_IN_Power2_Simps()
{
	const int HighDeegreeOfX = 2;
	double* x = new double[HighDeegreeOfX + 1];
	x[2] = 1.0;
	x[1] = 0;
	x[0] = 0;
	MathFunction* TestFunc = new MathFunction(x, HighDeegreeOfX, HighRange, LowRange, Divides);
	TestFunc->ValueOfRealInt(LowRange, HighRange);
	TestFunc->SimpsInt(LowRange, HighRange);
	return DoubleIsEqual(TestFunc->RealIntValue, TestFunc->ValueOfSimpsInt);
}

bool TestX_IN_Power1_Simps()
{
	const int HighDeegreeOfX = 1;
	double* x = new double[HighDeegreeOfX + 1];
	x[1] = 1.0;
	x[0] = 0;
	MathFunction* TestFunc = new MathFunction(x, HighDeegreeOfX, HighRange, LowRange, Divides);
	TestFunc->ValueOfRealInt(LowRange, HighRange);
	TestFunc->SimpsInt(LowRange, HighRange);
	return DoubleIsEqual(TestFunc->RealIntValue, TestFunc->ValueOfSimpsInt);
}

bool StartTest() {
	bool Result = true;
	typedef bool(*FunctionArr)();
	FunctionArr Functions[] = { TestX_IN_Power1_Simps, TestX_IN_Power2_Simps,TestX_IN_Power3_Trap,TestX_IN_Power4_Trap,TestX_IN_Power5_Trap };
	size_t CountOfFunctions = sizeof(Functions) / sizeof(Functions[0]);
	for (int i = 0; i < CountOfFunctions; i++) {
		if (!Functions[i]()) {
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
