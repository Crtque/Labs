// Interface.cpp
// ������������ ������ �3.
// ������� ������ 494, ����� ����� �������. 2020 ���

#include <iostream>
#include "Input.h"
#include <ctime>
#include "FileWork.h"
#include "UnitTest.h"
#include "MatrixClass.h"
#include <Windows.h>
#include <math.h>
#include "Sorting.h"

using namespace std;

InputType SaveDialog(Matrix& MatrixObj,bool FromFile) {
	BoolType UserChoice;
	if (!FromFile) {
		PrintDataSaveMenu();
		UserChoice = GetMenuItem(BoolType::QUIT, BoolType::NO);
		switch (UserChoice) {
		case BoolType::YES:
			OutputSourceData(MatrixObj);
			break;
		case BoolType::NO:
			break;
		case BoolType::QUIT:
			delete& MatrixObj;
			return InputType::QUIT;
			break;

		default:
			return InputType::CNT;
			break;
		}
	}
	PrintContinueMenu();
	SaveType SecondChoice = GetMenuItem(SaveType::QUIT, SaveType::CNT);
	
	switch (SecondChoice) {
	case SaveType::SAVECNT:
		OutputResultData(MatrixObj);
		system("cls");
		delete& MatrixObj;
		return InputType::CNT;
		break;
	case SaveType::SAVEEXT:
		OutputResultData(MatrixObj);
		delete& MatrixObj;
		return InputType::QUIT;
		break;
	case SaveType::CNT:
		system("cls");
		delete& MatrixObj;
		return InputType::CNT;
		break;
	case SaveType::QUIT:
		delete& MatrixObj;
		return InputType::QUIT;
		break;

	default:
		return InputType::CNT;
		break;
	}

}

InputType Selection() {
	PrintStartMenu();
	InputType UserChoice = GetMenuItem(InputType::QUIT,InputType::TEST);
	const int MaxValueForCell = 1000;
	const int MaxValueForSize = 100;
	const int MinValueForSize = 1;
	int Height, Width;
	Matrix* MatrixObj(nullptr);;
	srand(static_cast<unsigned int>(time(0)));
	switch (UserChoice) {

	case InputType::KEYBOARD:
		cout << "������� �������� ������ � ������ �������: " << endl;
		Width =  GetInt(MinValueForSize, MaxValueForSize);
		Height = GetInt(MinValueForSize, MaxValueForSize);
		MatrixObj = new Matrix(Width, Height);
		cout << endl << "������� �������� ����� ������:" << endl;
		for (int i = 0; i < (Width * Height); i++) {
			MatrixObj->Append(GetInt());
		}

		cout << endl << "������� ���������: " << Width << "x" << Height << endl;
		cout << endl << "�c������ �������:" << endl;
		MatrixObj->GetStringOfSourceMatrix(true);
		MatrixObj->Sort();
		for (int i = 0; i < MatrixObj->GetNumberOfSorts(); i++) {
			cout << endl << "���������� ������� ������� " << MatrixObj->GetNameOfSort(i) << ":" << endl;
			MatrixObj->GetStringOfChangedMatrix(true, i);
		}
		MatrixObj->GetSortsTable(true);
		return SaveDialog(*MatrixObj);
		break;

	case InputType::RANDOM:
		cout << "������� �������� ������ � ������ �������: " << endl;
		Width = GetInt(MinValueForSize, MaxValueForSize);
		Height = GetInt(MinValueForSize, MaxValueForSize);
		cout << endl << "������� ���������: " << Width << "x" << Height << endl;
		MatrixObj = new Matrix(Width, Height);
		cout << endl << "�c������ �������:" << endl;
		for (int i = 0; i < (Width * Height); i++) {
			MatrixObj->Append(static_cast<int>(RandomNeg(GetRandomInt(INT_MAX,0))));
		}
		MatrixObj->GetStringOfSourceMatrix(true);
	    MatrixObj->Sort();
		for (int i = 0; i < MatrixObj->GetNumberOfSorts(); i++) {
			cout << endl << "���������� ������� ������� "<<MatrixObj->GetNameOfSort(i)<<":" << endl;
			MatrixObj->GetStringOfChangedMatrix(true, i);
		}
		MatrixObj->GetSortsTable(true);
		return SaveDialog(*MatrixObj);
		break;

	case InputType::MYFILE:
		MatrixObj = InputData();
		if (MatrixObj != nullptr) {
			
			cout << endl << "������� ���������: " << MatrixObj->GetWidth() << "x" << MatrixObj->GetHeight() << endl;

			cout << endl << "�c������ �������:" << endl;
			MatrixObj->GetStringOfSourceMatrix(true);
			MatrixObj->Sort();
			for (int i = 0; i < MatrixObj->GetNumberOfSorts(); i++) {
				cout << endl << "���������� ������� ������� " << MatrixObj->GetNameOfSort(i) << ":" << endl;
				MatrixObj->GetStringOfChangedMatrix(true, i);
			}
			MatrixObj->GetSortsTable(true);
			return SaveDialog(*MatrixObj,true);
			break;
		}
		else {
			cout << "������ ����� �� �����. ���������� �����" << endl;
			return InputType::CNT;
		}
		break;
	case InputType::TEST:
		StartTest();
		return InputType::CNT;
		break;
	case InputType::QUIT:
		return InputType::QUIT;
		break;

	default:
		return InputType::CNT;
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



