// Interface.cpp
// ������������ ������ �4.
// ������� ������ 494, ����� ����� �������. 2020 ���

#include <iostream>
#include "Input.h"
#include <ctime>
#include "FileWork.h"
#include "UnitTest.h"
#include <Windows.h>
#include <math.h>
#include "TextClass.h"

using namespace std;

InputType SaveDialog(Text& TextObj, bool FromFile) {
	BoolType UserChoice;
	if (!FromFile) {
		PrintDataSaveMenu();
		UserChoice = GetMenuItem(BoolType::QUIT, BoolType::NO);
		switch (UserChoice) {
		case BoolType::YES:
			OutputSourceData(TextObj);
			break;
		case BoolType::NO:
			break;
		case BoolType::QUIT:
			delete& TextObj;
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
		OutputResultData(TextObj);
		system	("cls");
		delete& TextObj;
		return	InputType::CNT;
		break;
	case SaveType::SAVEEXT:
		OutputResultData(TextObj);
		delete& TextObj;
		return	InputType::QUIT;
		break;
	case SaveType::CNT:
		system	("cls");
		delete& TextObj;
		return	InputType::CNT;
		break;
	case SaveType::QUIT:
		delete& TextObj;
		return	InputType::QUIT;
		break;

	default:
		return	InputType::CNT;
		break;
	}

}
void SecondDialog(Text& TextObj) {
	SecondMenuType UserChoice;
	
	PrintSecondMenu();
	do {
		UserChoice = GetMenuItem(SecondMenuType::QUIT, SecondMenuType::UPPER);
		Text* TextToPaste = nullptr;
		switch (UserChoice) {

		case SecondMenuType::JOIN:
			TextToPaste = InputData();
			cout << "������� ����� ������, ����� ������� �� ������ �������� �����" << endl
				<< "0. ������" << endl
				<< "-1. �����" << endl << endl
				<< "��� �����:" << endl;

			if (TextObj.Join(TextToPaste, GetInt(-1))) {
				cout << "����� ����� �����������: " << endl << TextObj.GetChangedText() << endl;
			}
			else {
				cout << "������ ������ �� ����������. ������� ������ ����� ������" << endl;
			}
			break;
		case SecondMenuType::COUNT:
			TextObj.CountAll();
			cout << TextObj.GetStringOfNums() << endl;
			break;
		case SecondMenuType::UPPER:
			TextObj.ToUpperCase();
			cout << "���������� �����: " << endl << TextObj.GetChangedText() << endl;
			break;
		case SecondMenuType::QUIT:
			break;
		}
		PrintSecondMenu();
	} while (UserChoice != SecondMenuType::QUIT);
	}
	

InputType Selection() {
	PrintStartMenu();
	InputType UserChoice = GetMenuItem(InputType::QUIT,InputType::TEST);
	Text* TextObj = new Text();
	srand(static_cast<unsigned int>(time(0)));
	switch (UserChoice) {

	case InputType::KEYBOARD:
		TextObj->Add();
		SecondDialog(*TextObj);
		return SaveDialog(*TextObj);
		break;

	case InputType::MYFILE:
		TextObj = InputData();
		if (TextObj != nullptr) {
			SetColor(ConsoleColor::Green);
			cout << TextObj->GetText() << endl;
			SetColor(ConsoleColor::White);
			SecondDialog(*TextObj);
			return SaveDialog(*TextObj,true);
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
	cout << "�������� ������ ������� ������:" << endl
		<< "1. ���� � ����������" << endl
		<< "2. ����� �� �����" << endl
		<< "3. ������������" << endl << endl
		<< "-----------------------" << endl
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

void PrintSecondMenu() {
	cout << "��� �� ������ ������� � �������?" << endl
		<< "1. ������� �����, ��������, ������� � ����" << endl
		<< "2. �������� ����� �� �����" << endl
		<< "3. �������� ������ ������ �������� ����� ����� �� ���������" << endl
		<< "-----------------------" << endl
		<< "0. ���������� ������" << endl << endl
		<< "��� �����:" << endl;
}




