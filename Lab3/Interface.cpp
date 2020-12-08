// Interface.cpp
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

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
		cout << "Введите значение ширины и высоты матрицы: " << endl;
		Width =  GetInt(MinValueForSize, MaxValueForSize);
		Height = GetInt(MinValueForSize, MaxValueForSize);
		MatrixObj = new Matrix(Width, Height);
		cout << endl << "Введите значения ячеек матриц:" << endl;
		for (int i = 0; i < (Width * Height); i++) {
			MatrixObj->Append(GetInt());
		}

		cout << endl << "Матрица размерами: " << Width << "x" << Height << endl;
		cout << endl << "Иcходная матрица:" << endl;
		MatrixObj->GetStringOfSourceMatrix(true);
		MatrixObj->Sort();
		for (int i = 0; i < MatrixObj->GetNumberOfSorts(); i++) {
			cout << endl << "Измененная матрица методом " << MatrixObj->GetNameOfSort(i) << ":" << endl;
			MatrixObj->GetStringOfChangedMatrix(true, i);
		}
		MatrixObj->GetSortsTable(true);
		return SaveDialog(*MatrixObj);
		break;

	case InputType::RANDOM:
		cout << "Введите значение ширины и высоты матрицы: " << endl;
		Width = GetInt(MinValueForSize, MaxValueForSize);
		Height = GetInt(MinValueForSize, MaxValueForSize);
		cout << endl << "Матрица размерами: " << Width << "x" << Height << endl;
		MatrixObj = new Matrix(Width, Height);
		cout << endl << "Иcходная матрица:" << endl;
		for (int i = 0; i < (Width * Height); i++) {
			MatrixObj->Append(static_cast<int>(RandomNeg(GetRandomInt(INT_MAX,0))));
		}
		MatrixObj->GetStringOfSourceMatrix(true);
	    MatrixObj->Sort();
		for (int i = 0; i < MatrixObj->GetNumberOfSorts(); i++) {
			cout << endl << "Измененная матрица методом "<<MatrixObj->GetNameOfSort(i)<<":" << endl;
			MatrixObj->GetStringOfChangedMatrix(true, i);
		}
		MatrixObj->GetSortsTable(true);
		return SaveDialog(*MatrixObj);
		break;

	case InputType::MYFILE:
		MatrixObj = InputData();
		if (MatrixObj != nullptr) {
			
			cout << endl << "Матрица размерами: " << MatrixObj->GetWidth() << "x" << MatrixObj->GetHeight() << endl;

			cout << endl << "Иcходная матрица:" << endl;
			MatrixObj->GetStringOfSourceMatrix(true);
			MatrixObj->Sort();
			for (int i = 0; i < MatrixObj->GetNumberOfSorts(); i++) {
				cout << endl << "Измененная матрица методом " << MatrixObj->GetNameOfSort(i) << ":" << endl;
				MatrixObj->GetStringOfChangedMatrix(true, i);
			}
			MatrixObj->GetSortsTable(true);
			return SaveDialog(*MatrixObj,true);
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
	cout << "Выберите способ задания матрицы:" << endl
		<< "1. Ввод с клавиатуры" << endl
		<< "2. Случайная матрица" << endl
		<< "3. Матрица из файла" << endl << endl << endl
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



