// Interface.cpp
// ������������ ������ �1.
// ������� ������ 494, ����� ����� �������. 2020 ���

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
		cout << "������� ������� ������� X" << endl;
		HighDeegreOfX = GetInt(1, MAX_DEEGRE_OF_X);
	}
	double* x = new double[HighDeegreOfX+1];
	double HighRange, LowRange;
	int Divides;
	MathFunction* MathFunc;
	srand(static_cast<unsigned int>(time(0)));
	switch (UserChoice) {

	case MenuItem::KEYBOARD:
		cout << endl << "������� �� ������������ ������������ ��� �� x^" << HighDeegreOfX << " �� x^0 ��������������" << endl;
		for (int i = HighDeegreOfX; i >= 0; i--)
			x[i] = GetDouble();
		cout << "������� ������� � ������ ������ ��������������, ���������� ������� ��� ������ ��������: " << endl;
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
		cout << "������� ������: " << HighRange << endl << "������ ������: " << LowRange <<
			endl << "���������� ������� (��� ������ ��������): "<<Divides << endl;

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
			cout << "������ ����� �� �����. ���������� �����" << endl;
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
	cout << "�������� ������ ������� �������:" << endl
		<< "1. ���� � ����������" << endl
		<< "2. ��������� �������" << endl
		<< "3. ������� �� �����" << endl << endl << endl
		<< "-----------------------" << endl
		<< "4. ������������ ���������" << endl
		<< "0. ����� �� ���������" << endl << endl
		<< "��� �����:" << endl;
}

void PrintContinueMenu() {
	cout << "��������� ��������� ������ ���������?" << endl
		<< "1. ��, � ����������" << endl
		<< "2. ��, � ���������" << endl
		<< "3. ���, �� ������ ��������� �������" << endl
		<< "-----------------------" << endl
		<< "0. ����� �� ���������" << endl << endl
		<< "��� �����:" << endl;
}

void PrintDataSaveMenu() {
	cout << "��������� �������� ������ ���������?" << endl
		<< "1. ��" << endl
		<< "2. ���" << endl
		<< "-----------------------" << endl
		<< "0. ����� �� ���������" << endl << endl
		<< "��� �����:" << endl;
}



