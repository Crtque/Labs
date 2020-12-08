// FileWork.cpp
// Лабораторная работа №2.
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


bool NameIsNormal(string FilePath,string &PathWOFilename) {
	istringstream StringStream(FilePath);
	string Token = "";
	string PathWithoutFilename = FilePath;
	string ReservedNames[] = {"con","com1","com2","com3","com4","com5","com6","com7","com8","com9","prn",
		"aux","nul","ltp1" ,"ltp2" ,"ltp3" ,"ltp4" ,"ltp5" ,"ltp6" ,"ltp7" ,"ltp8" ,"ltp9" };

	char BadNameChars[] = { '\\','/',':','*','?','"','<','>','|','+',' ','%','!','@'};
	int NumberOfReservedNames = 22;
	int NumberOfBadChars = 14;
	bool PathIsOkay = true;
	int NumOfDirectory = 0;
	size_t LastSlashPos = PathWithoutFilename.find_last_of('\\');
	PathWOFilename = PathWithoutFilename.substr(0,LastSlashPos);
	while (getline(StringStream, Token, '\\')) {
		if (NumOfDirectory == 0) {
			if (fs::is_directory(Token)) {
				NumOfDirectory++;
				continue;
			}
			else {
				PathIsOkay = false;
				return PathIsOkay;
				break;
			}
		}
		transform(Token.begin(), Token.end(), Token.begin(),
			[NumberOfBadChars, BadNameChars, &PathIsOkay, &NumOfDirectory](unsigned char c) {
				for (int i = 0; i < NumberOfBadChars; i++) {
					if ((c == BadNameChars[i]) && (NumOfDirectory !=0)) {
						PathIsOkay = false;
						cout << "Обнаружен недопустимый символ: " << c << endl;
						break;
					}
				}
				return std::tolower(c); 
			});
		if (!PathIsOkay) {
			return PathIsOkay;
		}
		for (int i = 0; i < NumberOfReservedNames; i++) {
			if (Token._Equal(ReservedNames[i])) {
				cout << "Запрещенное название папки: " << Token << endl;
				PathIsOkay = false;
				StringStream.clear();
				return PathIsOkay;
			}
		}
		NumOfDirectory++;
	}
	StringStream.clear();
	StringStream.str(Token);
	while (getline(StringStream, Token, '.')) {
		for (int i = 0; i < NumberOfReservedNames; i++) {
			if (Token._Equal(ReservedNames[i])) {
				cout << "Запрещенное имя файла: " << Token << endl;
				PathIsOkay = false;
				return PathIsOkay;
			}
		}
	}
	return PathIsOkay;
}

void OutputResultData(Matrix& MatrixObj) {


	bool IsDataSaved = false;

	char* CurrentDir;
	string StrOfCurrentDir;

	if ((CurrentDir = _getcwd(NULL, 0)) == NULL) {
		perror("_getcwd error");
	}
	else {
		StrOfCurrentDir = static_cast<string>(CurrentDir);
	}

	do {
		string FilePath = "";
		string AbsolutePathWOFilename = "";
		string RelativePathWOFilename = "";
		int PathType = NOTDEFFINED;
		cout << "Сохранить данные в ( введите путь к файлу ):" << endl;
		getline(cin, FilePath);
		if (!NameIsNormal(FilePath, AbsolutePathWOFilename)) {
			if (!NameIsNormal(StrOfCurrentDir + "\\" + FilePath, RelativePathWOFilename)) {
				cout << "Введенный путь некорректен" << endl;
				continue;
			}
			else {
				PathType = RELATIVE;
			}
		}
		else {
			PathType = ABSOLUTE;
		}

		if (!fs::exists(FilePath)) {
			if (!fs::exists(StrOfCurrentDir + '\\' + FilePath)) {
				
					if (PathType == RELATIVE) {
						fs::create_directories(RelativePathWOFilename);
						FilePath = StrOfCurrentDir + '\\' + FilePath;

					}
					else if (PathType == ABSOLUTE) {
						fs::create_directories(AbsolutePathWOFilename);
					}
				
			}
			else {
				FilePath = StrOfCurrentDir + '\\' + FilePath;
			}
		}

		if (ifstream(FilePath)) {
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
				HANDLE hFile = FindFirstFileA(FilePath.c_str(), &findData);
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

		ofstream MyFile(FilePath, ofstream::app);


		if (!MyFile) {
			cout << "Запись запрещена. Повторите ввод." << endl;
			MyFile.close();
			continue;
		}

		MyFile.close();
		MyFile.open(FilePath, ofstream::trunc);
		MyFile << "Матрица размерами: " << MatrixObj.GetWidth() << "x" << MatrixObj.GetHeight() << endl;
		MyFile << "Искомое число: " << MatrixObj.GetReq() << endl;
		MyFile << endl << "Иcходная матрица:" << endl;
		MyFile << MatrixObj.GetStringOfMatrix(false, true);
		MyFile << endl << "Измененная матрица:" << endl;
		MyFile << MatrixObj.GetStringOfMatrix(false, false);

		MyFile.close();
		cout << "Запись данных завершена." << endl;
		IsDataSaved = true;
	} while (!IsDataSaved);
}

void OutputSourceData(Matrix& MatrixObj) {


	bool IsDataSaved = false;

	char* CurrentDir;
	string StrOfCurrentDir;

	if ((CurrentDir = _getcwd(NULL, 0)) == NULL) {
		perror("_getcwd error");
	}
	else {
		StrOfCurrentDir = static_cast<string>(CurrentDir);
	}

	do {
		string FilePath = "";
		string AbsolutePathWOFilename = "";
		string RelativePathWOFilename = "";
		int PathType = NOTDEFFINED;
		cout << "Сохранить данные в ( введите путь к файлу ):" << endl;
		getline(cin, FilePath);
		if (!NameIsNormal(FilePath, AbsolutePathWOFilename)) {
			if (!NameIsNormal(StrOfCurrentDir + "\\" + FilePath, RelativePathWOFilename)) {
				cout << "Введенный путь некорректен" << endl;
				continue;
			}
			else {
				PathType = RELATIVE;
			}
		}
		else {
			PathType = ABSOLUTE;
		}

		if (!fs::exists(FilePath)) {
			if (!fs::exists(StrOfCurrentDir + '\\' + FilePath)) {
				
					if (PathType == RELATIVE) {
						fs::create_directories(RelativePathWOFilename);
						FilePath = StrOfCurrentDir + '\\' + FilePath;

					}
					else if (PathType == ABSOLUTE) {
						fs::create_directories(AbsolutePathWOFilename);
					}
				
			}
			else {
				FilePath = StrOfCurrentDir + '\\' + FilePath;
			}
		}

		if (ifstream(FilePath)) {
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
				HANDLE hFile = FindFirstFileA(FilePath.c_str(), &findData);
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

		ofstream MyFile(FilePath, ofstream::app);


		if (!MyFile) {
			cout << "Запись запрещена. Повторите ввод." << endl;
			MyFile.close();
			continue;
		}

		MyFile.close();
		MyFile.open(FilePath, ofstream::trunc);
		MyFile << MatrixObj.GetHeight() << " " << MatrixObj.GetWidth() <<" " << MatrixObj.GetReq() << endl;
		MyFile << MatrixObj.GetStringOfMatrix();
		MyFile.close();
		cout << "Запись данных завершена." << endl;
		IsDataSaved = true;
	} while (!IsDataSaved);
}

Matrix* InputData() {
	string FilePath;
	bool IsDataLoaded = false;
	char* CurrentDir;
	const int MaxValueForSize = 11;
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
		int Width, Height, Req;
		

		if (!(MyFile >> Height) || Height < MinValueForSize || Height >= MaxValueForSize) {
			
			cout << "Некорректая высота матрицы. Высота матрицы должна быть от " << MinValueForSize << " до " << MaxValueForSize-1 << endl;
			MyFile.close();
			continue;
		}


		if (!(MyFile >> Width) || Width < MinValueForSize || Width >= MaxValueForSize) {

			cout << "Некорректная ширина матрицы. Ширина матрицы должна быть от " << MinValueForSize << " до " << MaxValueForSize - 1 << endl;
			MyFile.close();
			continue;
		}
		if (!(MyFile >> Req) || Req < MinValueForSize || Req >= MaxValueForSize) {

			cout << "Некорректное значение искомого числа. Искомое число может иметь значение от " << MinValueForSize << " до " << MaxValueForSize - 1 << endl;
			MyFile.close();
			continue;
		}

		MatrixObj = new Matrix(Width, Height, Req);
		int Buff;
		for (int i = 0; i < (Width * Height); i++) {
			if (!(MyFile >> Buff) || Buff < MinValueForSize || Buff >= MaxValueForSize) {

				cout << "Некорректное значение для ячейки матрицы. Ячейка матрицы может иметь значение от " << MinValueForSize << " до " << MaxValueForSize - 1 << endl;
				MyFile.close();
				continue;
			}
		MatrixObj->Append(Buff);
		}

		cout << "Загрузка данных завершена." << endl;
		IsDataLoaded = true;

		MyFile.close();
	} while (!IsDataLoaded);
	return MatrixObj;
}