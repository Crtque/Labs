// Interface.cpp
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include "Input.h"
#include <ctime>
#include "FileWork.h"
#include "MathFunction.h"
#include "UnitTest.h"

using namespace std;
MenuItem SaveDialog(MathFunction& MathFunc) {
	PrintDataSaveMenu();
	MenuItem UserChoice = GetMenuItem(MenuItem::QUIT,MenuItem::NO);
	switch (UserChoice) {
	case MenuItem::YES:
		OutputSourceData(MathFunc);
		break;
	case MenuItem::NO:
		break;
	case MenuItem::QUIT:
		delete& MathFunc;
		return MenuItem::QUIT;
		break;

	default:
		return MenuItem::CNT;
		break;
	}

	PrintContinueMenu();
	UserChoice = GetMenuItem(MenuItem::QUIT, MenuItem::CNT);
	switch (UserChoice) {
	case MenuItem::SAVECNT:
		OutputResultData(MathFunc);
		system("cls");
		delete& MathFunc;
		return MenuItem::CNT;
		break;
	case MenuItem::SAVEEXT:
		OutputResultData(MathFunc);
		delete& MathFunc;
		return MenuItem::QUIT;
		break;
	case MenuItem::CNT:
		system("cls");
		delete& MathFunc;
		return MenuItem::CNT;
		break;
	case MenuItem::QUIT:
		delete& MathFunc;
		return MenuItem::QUIT;
		break;

	default:
		return MenuItem::CNT;
		break;
	}
}

MenuItem Selection() {
	PrintStartMenu();
	MenuItem UserChoice = GetMenuItem(MenuItem::QUIT,MenuItem::TEST);
	const int MinAmountOfDivides = 1000;
	const int MaxAmountOfDivides = 10000;
	const int MaxValueForRand = 11;
	const int MinValueForRand = 1;
	int HighDeegreOfX = MAX_DEEGRE_OF_X;
	if ((UserChoice != MenuItem::MYFILE) && (UserChoice !=MenuItem::TEST) && (UserChoice !=MenuItem::QUIT)) {
		cout << "Введите старшую степень X" << endl;
		HighDeegreOfX = GetInt(1, MAX_DEEGRE_OF_X);
	}
	double* x = new double[HighDeegreOfX+1];
	double HighRange, LowRange;
	int Divides;
	MathFunction* MathFunc;
	srand(static_cast<unsigned int>(time(0)));
	switch (UserChoice) {

	case MenuItem::KEYBOARD:
		cout << endl << "Ожидаем от пользователя коэффициенты для от x^" << HighDeegreOfX << " до x^0 соответственно" << endl;
		for (int i = HighDeegreOfX; i >= 0; i--)
			x[i] = GetDouble();
		cout << "Введите верхний и нижний предел интегрирования, количество делений для метода трапеций: " << endl;
		HighRange = GetInt();
		LowRange = GetInt();

		Divides = GetInt(MinAmountOfDivides,MaxAmountOfDivides);
		MathFunc = new MathFunction(x, HighDeegreOfX, HighRange, LowRange, Divides);
		MathFunc->SimpsInt(LowRange, HighRange);
		MathFunc->TrapInt(LowRange, HighRange, Divides);
		cout << MathFunc->GetStringOfFunction();
		cout << MathFunc->GetStringOfResults();
		cout << endl;
		return SaveDialog(*MathFunc);
		break;

	case MenuItem::RANDOM:
		
		HighRange = GetRandomInt();
		do { 
			LowRange = GetRandomInt();
		} while (LowRange >= HighRange);

		Divides = GetRandomInt(MinAmountOfDivides, MaxAmountOfDivides);
		cout << "Верхний предел: " << HighRange << endl << "Нижний предел: " << LowRange <<
			endl << "Количество делений (для метода трапеций): "<<Divides << endl;

		for (int i = HighDeegreOfX; i >= 0; i--)
			x[i] = RandomNeg(GetRandomDouble(MinValueForRand,MaxValueForRand));
		MathFunc = new MathFunction(x, HighDeegreOfX, HighRange,LowRange,Divides);
		MathFunc->SimpsInt(LowRange, HighRange); 
		MathFunc->TrapInt(LowRange, HighRange, Divides); 
		cout << MathFunc->GetStringOfFunction();
		cout << MathFunc->GetStringOfResults();
		cout << endl;
		return SaveDialog(*MathFunc);
		break;

	case MenuItem::MYFILE:
		MathFunc = InputData();
		if (MathFunc != nullptr) {
			MathFunc->SimpsInt(MathFunc->LowRange, MathFunc->HighRange);
			MathFunc->TrapInt(MathFunc->LowRange, MathFunc->HighRange, MathFunc->Divides);
			cout << MathFunc->GetStringOfFunction();
			cout << MathFunc->GetStringOfResults();
			cout << endl;
			return SaveDialog(*MathFunc);
		}
		else {
			cout << "Ошибка ввода из файла. Попробуйте снова" << endl;
			return MenuItem::CNT;
		}
		break;
	case MenuItem::TEST:
		StartTest();
		return MenuItem::CNT;
		break;
	case MenuItem::QUIT:
		return MenuItem::QUIT;
		break;

	default:
		return MenuItem::CNT;
		break;
	}

}

void PrintStartMenu() {
	cout << "Выберите способ задания функции:" << endl
		<< "1. Ввод с клавиатуры" << endl
		<< "2. Случайная функция" << endl
		<< "3. Функция из файла" << endl << endl << endl
		<< "-----------------------" << endl
		<< "4. Тестирование программы" << endl
		<< "0. Выход из программы" << endl << endl
		<< "Ваш выбор:" << endl;
}

void PrintContinueMenu() {
	cout << "Сохранить результат работы программы?" << endl
		<< "1. Да, и продолжить" << endl
		<< "2. Да, и закончить" << endl
		<< "3. Нет, но начать программу сначала" << endl
		<< "-----------------------" << endl
		<< "0. Выход из программы" << endl << endl
		<< "Ваш выбор:" << endl;
}

void PrintDataSaveMenu() {
	cout << "Сохранить исходные данные программы?" << endl
		<< "1. Да" << endl
		<< "2. Нет" << endl
		<< "-----------------------" << endl
		<< "0. Выход из программы" << endl << endl
		<< "Ваш выбор:" << endl;
}



