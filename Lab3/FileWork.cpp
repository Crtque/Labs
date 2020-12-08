// FileWork.cpp
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "Input.h"
#include "MatrixClass.h"
#include <direct.h>
#include <sstream>
#include <cctype>
#include <Windows.h>

using namespace std;
namespace fs = std::experimental::filesystem;

void OutputResultData(Matrix& MatrixObj) {
	string filePath;
	bool isDataSaved = false;
	do {
		cout << "Сохранить в:" << endl;
		cin >> filePath;
		if (ifstream(filePath)) {
			cout << "Файл уже существует." << endl << endl
				<< "Выберите действие:" << endl
				<< "0. Перезаписать существующий файл." << endl
				<< "1. Повторить ввод." << endl;
			bool IsAnother = GetBool();
			if (IsAnother) {
				continue;
			}
			else {
				WIN32_FIND_DATAA findData;
				HANDLE hFile = FindFirstFileA(filePath.c_str(), &findData);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					cout << "Запись запрещена. Повторите ввод." << endl;
					continue;

				}
				else
				{
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
					{
						cout << "Данный файл доступен только для чтения. Измените атрибуты файла и повторите ввод." << endl
							<< "Либо выберите другой файл." << endl;
						continue;
					}
				}
			}
		}
		ofstream myFile(filePath, ofstream::app);
		if (!fs::is_regular_file(fs::path(filePath))) {
			cout << "Запись запрещена. Повторите ввод." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		myFile << "Матрица размерами: " << MatrixObj.GetWidth() << "x" << MatrixObj.GetHeight() << endl;
		myFile << endl << "Иcходная матрица:" << endl;
		myFile << MatrixObj.GetStringOfSourceMatrix(false);
		for (int i = 0; i < MatrixObj.GetNumberOfSorts(); i++) {
			myFile << endl << "Измененная матрица методом " << MatrixObj.GetNameOfSort(i) << ":" << endl;
			myFile << MatrixObj.GetStringOfChangedMatrix(false, i);
		}
		myFile << MatrixObj.GetSortsTable(true);
		myFile.close();
		cout << "Запись данных завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}

void OutputSourceData(Matrix& MatrixObj) {
	string filePath;
	bool isDataSaved = false;
	do {
		cout << "Сохранить в:" << endl;
		cin >> filePath;
		if (ifstream(filePath)) {
			cout << "Файл уже существует." << endl << endl
				<< "Выберите действие:" << endl
				<< "0. Перезаписать существующий файл." << endl
				<< "1. Повторить ввод." << endl;
			bool IsAnother = GetBool();
			if (IsAnother) {
				continue;
			}
			else {
				WIN32_FIND_DATAA findData;
				HANDLE hFile = FindFirstFileA(filePath.c_str(), &findData);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					cout << "Запись запрещена. Повторите ввод." << endl;
					continue;

				}
				else
				{
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
					{
						cout << "Данный файл доступен только для чтения. Измените атрибуты файла и повторите ввод." << endl
							<< "Либо выберите другой файл." << endl;
						continue;
					}
				}
			}
		}
		ofstream myFile(filePath, ofstream::app);
		if (!fs::is_regular_file(fs::path(filePath))) {
			cout << "Запись запрещена. Повторите ввод." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		myFile << MatrixObj.GetHeight() << " " << MatrixObj.GetWidth() << endl;
		myFile << MatrixObj.GetStringOfSourceMatrix(false);
		myFile.close();
		cout << "Запись данных завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}

Matrix* InputData() {
	string FilePath;
	bool IsDataLoaded = false;
	char* CurrentDir;
	const int MaxValueForCell = INT_MAX;
	const int MinValueForCell = INT_MIN;
	const int MaxValueForSize = 100;
	const int MinValueForSize = 1;

	Matrix* MatrixObj = nullptr;
	if ((CurrentDir = _getcwd(NULL, 0)) == NULL) {
		perror("_getcwd error");
	}

	do {
		cout << "Загрузить данные из ( введите путь к файлу ):" << endl;
		cin >> FilePath;

		if (!ifstream(FilePath)) {
			cout << "Файл не существует. Повторите ввод." << endl;
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		if (!fs::is_regular_file(FilePath)) {
			cout << "Адрес содержит недопустимые значения. Повторите ввод." << endl;
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		ifstream MyFile(FilePath);

		if (!MyFile) {
			cout << "Загрузка запрещена. Повторите ввод." << endl;
			MyFile.close();
			continue;
		}
		int Width, Height;
		

		if (!(MyFile >> Height) || Height < MinValueForSize || Height >= MaxValueForSize) {
			
			cout << "Некорректая высота/ширина матрицы. Высота/ширина матрицы должна быть от " << MinValueForSize << " до " << MaxValueForSize-1 << endl;
			MyFile.close();
			continue;
		}
		if (!(MyFile >> Width) || Width < MinValueForSize || Width >= MaxValueForSize) {

			cout << "Некорректая высота/ширина матрицы. Высота/ширина матрицы должна быть от " << MinValueForSize << " до " << MaxValueForSize - 1 << endl;
			MyFile.close();
			continue;
		}

		MatrixObj = new Matrix(Width, Height);
		int Buff;
		bool AllIsFine = true;
		for (int i = 0; i < (Width * Height); i++) {
			if (!(MyFile >> Buff) || Buff < MinValueForCell || Buff >= MaxValueForCell) {

				cout << "Некорректное значение для ячейки матрицы. Ячейка матрицы может иметь значение от " << MinValueForSize << " до " << MaxValueForCell - 1 << endl;
				MyFile.close();
				AllIsFine = false;
				break;
			}
			else {
				MatrixObj->Append(Buff);
			}
		}
		if (!AllIsFine) {
			continue;
		}
		cout << "Загрузка данных завершена." << endl;
		IsDataLoaded = true;

		MyFile.close();
	} while (!IsDataLoaded);
	return MatrixObj;
}