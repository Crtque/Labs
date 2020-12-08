// Interface.cpp
// ������������ ������ �2.
// ������� ������ 494, ����� ����� �������. 2020 ���

#include <iostream>
#include "Input.h"
#include <ctime>
#include "FileWork.h"
#include "MatrixClass.h"
#include "UnitTest.h"
#include <Windows.h>

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
	const int MaxValueForSize = 11;
	const int MinValueForSize = 1;

	int Height, Width,Req;
	Matrix* MatrixObj(nullptr);;
	srand(static_cast<unsigned int>(time(0)));
	switch (UserChoice) {

	case InputType::KEYBOARD:
		cout << "������� �������� ������ � ������ �������: " << endl;
		Width = GetInt(MinValueForSize, MaxValueForSize);
		Height = GetInt(MinValueForSize, MaxValueForSize);
		cout << endl << "������� �������� �������� ����� " << endl;
		Req = GetInt(MinValueForSize, MaxValueForSize);

		MatrixObj = new Matrix(Width, Height, Req);
		for (int i = 0; i < (Width * Height); i++) {
			MatrixObj->Append(GetInt(MinValueForSize,MaxValueForSize));
		}
		cout << endl << "������� ���������: " << Width << "x" << Height << endl;
		cout << "������� �����: " << Req << endl << endl;

		cout << endl << "�c������ �������:" << endl;
		MatrixObj->GetStringOfMatrix(true,true);

		MatrixObj->CheckEachCell(&Matrix::EqualsToComparing, &Matrix::Swap);
		cout << endl << "���������� �������:" << endl;
		MatrixObj->GetStringOfMatrix(true,false);
		return SaveDialog(*MatrixObj);
		break;

	case InputType::RANDOM:
		Width = GetRandomInt(MinValueForSize, MaxValueForSize);
		Height = GetRandomInt(MinValueForSize, MaxValueForSize);
		Req = GetRandomInt(MinValueForSize, MaxValueForSize);

		MatrixObj = new Matrix(Width, Height, Req);
		for (int i = 0; i < (Width * Height); i++) {
			MatrixObj->Append(GetRandomInt(MinValueForSize,MaxValueForSize));
		}
		cout << endl << "������� ���������: " << Width << "x" << Height << endl;
		cout << "������� �����: " << Req << endl << endl;

		cout << endl << "�c������ �������:" << endl;
		MatrixObj->GetStringOfMatrix(true,true);

		MatrixObj->CheckEachCell(&Matrix::EqualsToComparing, &Matrix::Swap);
		cout << endl << "���������� �������:" << endl;
		MatrixObj->GetStringOfMatrix(true,false);


		return SaveDialog(*MatrixObj);
		break;

	case InputType::MYFILE:
		MatrixObj = InputData();
		if (MatrixObj != nullptr) {
			
			cout << endl << "������� ���������: " << MatrixObj->GetWidth() << "x" << MatrixObj->GetHeight() << endl;
			cout << "������� �����: " << MatrixObj->GetReq()<< endl << endl;

			cout << endl << "�c������ �������:" << endl;
			MatrixObj->GetStringOfMatrix(true, true);
			MatrixObj->CheckEachCell(&Matrix::EqualsToComparing, &Matrix::Swap);
			cout << endl << "���������� �������:" << endl;
			MatrixObj->GetStringOfMatrix(true, false);
			return SaveDialog(*MatrixObj,true);
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



