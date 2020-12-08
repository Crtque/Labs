// Input.cpp
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include "Interface.h"
#include <string>
#include <ctime>

using namespace std;


const int HighRangeForRand = 100;
const int LowRangeForRand = 0;
template<typename T>
T GetInput() {
	T UserInput;
	cin >> UserInput;
	if (cin.fail()) {
		while (cin.fail()) {
			cout << "Такое значение не поддерживается программой." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> UserInput;
		}
	}
	cin.ignore(INT_MAX, '\n');
	return UserInput;
}

bool GetBool() {
	return GetInput<bool>();
}

int GetInt(int LowRange = INT_MIN, int HighRange = INT_MAX) {
	int UserInput;
	cin >> UserInput;
	
	if (cin.fail() || (UserInput > HighRange) || (UserInput < LowRange)) {
		while (cin.fail() || (UserInput > HighRange) || (UserInput < LowRange)) {
			cout << "Такое значение не поддерживается программой." << endl;
			if ((UserInput > HighRange) || (UserInput < LowRange)) {
				cout << "Значение должно быть в диапазоне от " << LowRange << " до " << HighRange << endl;
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> UserInput;
		}
	}
	cin.ignore(INT_MAX, '\n');
	return UserInput;
}

double GetDouble() {
	return GetInput<double>();
}

double RandomNeg(double Input) {
	return (rand() % 2 ? Input : Input * -1);
}
int GetRandomInt(int HighRange = HighRangeForRand, int LowRange = LowRangeForRand) {
	
	if (HighRange < LowRange) {
		int Buff = HighRange;
		HighRange = LowRange;
		LowRange = Buff;
	}
	return rand() % (HighRange - LowRange) + LowRange;
}

double GetRandomDouble(int HighRange = HighRangeForRand, int LowRange = LowRangeForRand) {
	if (HighRange < LowRange) {
		int Buff = HighRange;
		HighRange = LowRange;
		LowRange = Buff;
	}
	double a, b;
	a = static_cast<double>(GetRandomInt(LowRange, HighRange));
	do {
		b = static_cast<double>(GetRandomInt(LowRange, HighRange));
	} while (b == 0.0);
	return a / b;
}

MenuItem GetMenuItem(MenuItem Min,MenuItem Max) {
	int UserInput;
	cin >> UserInput;
	if (cin.fail() || UserInput < static_cast<int>(Min) || UserInput > static_cast<int>(Max)){
		while (cin.fail() || UserInput < static_cast<int>(Min) || UserInput > static_cast<int>(Max)) {
			cout << "Такое значение не поддерживается программой." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> UserInput;
		}
	}
	cin.ignore(INT_MAX, '\n');
	return static_cast<MenuItem>(UserInput);
}