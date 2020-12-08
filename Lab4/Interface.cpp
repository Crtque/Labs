// Interface.cpp
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

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
			cout << "Введите номер строки, после которой вы хотите вставить текст" << endl
				<< "0. Начало" << endl
				<< "-1. Конец" << endl << endl
				<< "Ваш выбор:" << endl;

			if (TextObj.Join(TextToPaste, GetInt(-1))) {
				cout << "Текст после объединения: " << endl << TextObj.GetChangedText() << endl;
			}
			else {
				cout << "Данная строка не существует. Укажите другой номер строки" << endl;
			}
			break;
		case SecondMenuType::COUNT:
			TextObj.CountAll();
			cout << TextObj.GetStringOfNums() << endl;
			break;
		case SecondMenuType::UPPER:
			TextObj.ToUpperCase();
			cout << "Измененный текст: " << endl << TextObj.GetChangedText() << endl;
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
			cout << "Ошибка ввода из файла. Попробуйте снова" << endl;
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
	cout << "Выберите способ задания текста:" << endl
		<< "1. Ввод с клавиатуры" << endl
		<< "2. Текст из файла" << endl
		<< "3. Тестирование" << endl << endl
		<< "-----------------------" << endl
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

void PrintSecondMenu() {
	cout << "Что вы хотите сделать с текстом?" << endl
		<< "1. Подсчет строк, символов, абзацев и слов" << endl
		<< "2. Вставить текст из файла" << endl
		<< "3. Заменить каждую первую строчную букву слова на прописную" << endl
		<< "-----------------------" << endl
		<< "0. Продолжить работу" << endl << endl
		<< "Ваш выбор:" << endl;
}




