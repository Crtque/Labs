// MathFunction.h
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#pragma once
#define MAX_DEEGRE_OF_X 5
#include <string>
bool isEqual(double,double);
class MathFunction
{
private:
	double* x = new double[MAX_DEEGRE_OF_X+1];
public:
	double ValueOfTrapInt, ValueOfSimpsInt, RealIntValue;
	double HighRange, LowRange;
	int Divides;
	int HighDeegreeOfX;
	MathFunction(double *,int,double,double,int);
	std::string GetStringOfFunction();
	std::string GetStringOfResults();
	double* GetArrX();
	int GetHighDeegre();
	double FuncValueAtX(double);
	double TrapInt(double, double, int);
	double SimpsInt(double, double);
	double RealIntOfFunc(double);
	double ValueOfRealInt(double, double);
};