// MathFunction.cpp
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include <string>
#include <sstream>
#include "MathFunction.h"
using namespace std;

bool isEqual(double x, double y) {
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

	MathFunction::MathFunction(double *arrx, int HighDeegreeOfXV, double HighRangeV, double LowRangeV,int DividesV){
		RealIntValue = ValueOfSimpsInt = ValueOfTrapInt = 0;
		for (int i = HighDeegreeOfXV; i >= 0; i--) {
			x[i] = arrx[i];
			
		}
		HighRange = HighRangeV;
		HighDeegreeOfX = HighDeegreeOfXV;
		LowRange = LowRangeV;
		Divides = DividesV;		
	}

	string MathFunction::GetStringOfFunction() {
		stringstream Function;
		string Result = "";
		Function << endl << "f(x) = ";
		for (int i = HighDeegreeOfX; i >= 0; i--) {
			if (i == HighDeegreeOfX) {
				Function << (x[i] >= 0 ? "" : "-") << (isEqual(fabs(x[i]), 1.0) ? "x^" : to_string(fabs(x[i])) + "x^") << i << " ";
			}
			else if (i == 0) {
				Function << (x[i] >= 0 ? "+" : "-") << fabs(x[i]) << endl;
			}
			else if (i == 1) {
				Function << (x[i] >= 0 ? "+" : "-") << (isEqual(fabs(x[i]), 1.0) ? "x " : to_string(fabs(x[i])) + "x ");
			}
			else {
				Function << (x[i] >= 0 ? "+" : "-") << (isEqual(fabs(x[i]), 1.0) ? "x^" : to_string(fabs(x[i])) + "x^") << i << " ";
			}
		}
		Result = Function.str();
		Function.clear();
		return Result;
	}

	string MathFunction::GetStringOfResults() {
		stringstream Results;
		string Result;
		Results << "Результат методом трапеции: " << this->ValueOfTrapInt << endl;
		Results << "Результат методом параболы: " << this->ValueOfSimpsInt << endl;
		Result = Results.str();
		Results.clear();
		return Result;
	}

	double* MathFunction::GetArrX() {
		return x;
	}

	int MathFunction::GetHighDeegre() {
		return HighDeegreeOfX;
	}

	double MathFunction::FuncValueAtX(double x) {
		double* Coef = this->GetArrX();
		double Result = 0;
		double Buff;
		for (int i = this->GetHighDeegre(); i >= 0; i--) {
			Buff = Coef[i];
			for (int j = 0; j < i; j++) {
				Buff *= x;
			}
			Result += Buff;
			Buff = 0;
		}
		return Result;
	}


	double MathFunction::TrapInt(double a, double b, int n) {
		double Result = 0;
		double h = (b - a) / n;
		double xi = a + h;

		Result += (this->FuncValueAtX(a) / 2) * (xi - a);
		xi = a + ((static_cast<double>(n) - 1) * h);
		Result += (this->FuncValueAtX(b) / 2) * (b - xi);

		for (int i = 1; i <= (n-1); i++) {
			xi = a + (i * h);
			Result += (this->FuncValueAtX(xi) / 2) * (2 * h);
		}
		this->ValueOfTrapInt = Result;
		return Result;
	}

	double MathFunction::SimpsInt(double a, double b) {
		double Result = 0;
		Result = ((b - a) / 6) * (FuncValueAtX(a) + (4 * FuncValueAtX((a + b) / 2)) + FuncValueAtX(b));
		this->ValueOfSimpsInt = Result;
		return Result;
	}

	double MathFunction::RealIntOfFunc(double x) {
		double* Coef = this->GetArrX();
		double Result = 0;
		double Buff;
		for (int i = this->GetHighDeegre(); i >= 0; i--) {
			Buff = Coef[i];
			for (int j = 0; j < i+1; j++) {
				Buff *= x;
			}
			Buff /= static_cast<double>(i) + 1;
			Result += Buff;
			Buff = 0;
		}
		
		return Result;
	}
	double MathFunction::ValueOfRealInt(double a, double b) {
		double Result = RealIntOfFunc(b) - RealIntOfFunc(a);
		this->RealIntValue = Result;
		return Result;
	}
