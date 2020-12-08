// FileWork.cpp
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "Input.h"
#include "TextClass.h"
#include <direct.h>
#include <sstream>
#include <cctype>
#include <Windows.h>

using namespace std;
namespace fs = std::experimental::filesystem;


void OutputResultData(Text& TextObj) {
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
		string buff = TextObj.GetStringOfNums();
		myFile << TextObj.GetChangedText();
		myFile << buff << endl;
		myFile.close();
		cout << "Запись данных завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}

void OutputSourceData(Text& TextObj) {
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
		myFile << TextObj.GetText();
		myFile.close();
		cout << "Запись данных завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}

Text* InputData() {
	string FilePath;
	bool IsDataLoaded = false;
	char* CurrentDir;

	Text* TextObj = nullptr;
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
		string TextRow,SourceText;
		SourceText = "";
		while (!MyFile.eof()) {
			getline(MyFile, TextRow);
			SourceText += TextRow+"\n";
		}

		TextObj = new Text();
		TextObj->Append(SourceText);
		
		cout << "Загрузка данных завершена." << endl;
		IsDataLoaded = true;

		MyFile.close();
	} while (!IsDataLoaded);
	return TextObj;
}