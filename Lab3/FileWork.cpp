// FileWork.cpp
// ������������ ������ �3.
// ������� ������ 494, ����� ����� �������. 2020 ���

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
		cout << "��������� �:" << endl;
		cin >> filePath;
		if (ifstream(filePath)) {
			cout << "���� ��� ����������." << endl << endl
				<< "�������� ��������:" << endl
				<< "0. ������������ ������������ ����." << endl
				<< "1. ��������� ����." << endl;
			bool IsAnother = GetBool();
			if (IsAnother) {
				continue;
			}
			else {
				WIN32_FIND_DATAA findData;
				HANDLE hFile = FindFirstFileA(filePath.c_str(), &findData);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					cout << "������ ���������. ��������� ����." << endl;
					continue;

				}
				else
				{
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
					{
						cout << "������ ���� �������� ������ ��� ������. �������� �������� ����� � ��������� ����." << endl
							<< "���� �������� ������ ����." << endl;
						continue;
					}
				}
			}
		}
		ofstream myFile(filePath, ofstream::app);
		if (!fs::is_regular_file(fs::path(filePath))) {
			cout << "������ ���������. ��������� ����." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		myFile << "������� ���������: " << MatrixObj.GetWidth() << "x" << MatrixObj.GetHeight() << endl;
		myFile << endl << "�c������ �������:" << endl;
		myFile << MatrixObj.GetStringOfSourceMatrix(false);
		for (int i = 0; i < MatrixObj.GetNumberOfSorts(); i++) {
			myFile << endl << "���������� ������� ������� " << MatrixObj.GetNameOfSort(i) << ":" << endl;
			myFile << MatrixObj.GetStringOfChangedMatrix(false, i);
		}
		myFile << MatrixObj.GetSortsTable(true);
		myFile.close();
		cout << "������ ������ ���������." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}

void OutputSourceData(Matrix& MatrixObj) {
	string filePath;
	bool isDataSaved = false;
	do {
		cout << "��������� �:" << endl;
		cin >> filePath;
		if (ifstream(filePath)) {
			cout << "���� ��� ����������." << endl << endl
				<< "�������� ��������:" << endl
				<< "0. ������������ ������������ ����." << endl
				<< "1. ��������� ����." << endl;
			bool IsAnother = GetBool();
			if (IsAnother) {
				continue;
			}
			else {
				WIN32_FIND_DATAA findData;
				HANDLE hFile = FindFirstFileA(filePath.c_str(), &findData);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					cout << "������ ���������. ��������� ����." << endl;
					continue;

				}
				else
				{
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
					{
						cout << "������ ���� �������� ������ ��� ������. �������� �������� ����� � ��������� ����." << endl
							<< "���� �������� ������ ����." << endl;
						continue;
					}
				}
			}
		}
		ofstream myFile(filePath, ofstream::app);
		if (!fs::is_regular_file(fs::path(filePath))) {
			cout << "������ ���������. ��������� ����." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		myFile << MatrixObj.GetHeight() << " " << MatrixObj.GetWidth() << endl;
		myFile << MatrixObj.GetStringOfSourceMatrix(false);
		myFile.close();
		cout << "������ ������ ���������." << endl;
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
		cout << "��������� ������ �� ( ������� ���� � ����� ):" << endl;
		cin >> FilePath;

		if (!ifstream(FilePath)) {
			cout << "���� �� ����������. ��������� ����." << endl;
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		if (!fs::is_regular_file(FilePath)) {
			cout << "����� �������� ������������ ��������. ��������� ����." << endl;
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		ifstream MyFile(FilePath);

		if (!MyFile) {
			cout << "�������� ���������. ��������� ����." << endl;
			MyFile.close();
			continue;
		}
		int Width, Height;
		

		if (!(MyFile >> Height) || Height < MinValueForSize || Height >= MaxValueForSize) {
			
			cout << "����������� ������/������ �������. ������/������ ������� ������ ���� �� " << MinValueForSize << " �� " << MaxValueForSize-1 << endl;
			MyFile.close();
			continue;
		}
		if (!(MyFile >> Width) || Width < MinValueForSize || Width >= MaxValueForSize) {

			cout << "����������� ������/������ �������. ������/������ ������� ������ ���� �� " << MinValueForSize << " �� " << MaxValueForSize - 1 << endl;
			MyFile.close();
			continue;
		}

		MatrixObj = new Matrix(Width, Height);
		int Buff;
		bool AllIsFine = true;
		for (int i = 0; i < (Width * Height); i++) {
			if (!(MyFile >> Buff) || Buff < MinValueForCell || Buff >= MaxValueForCell) {

				cout << "������������ �������� ��� ������ �������. ������ ������� ����� ����� �������� �� " << MinValueForSize << " �� " << MaxValueForCell - 1 << endl;
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
		cout << "�������� ������ ���������." << endl;
		IsDataLoaded = true;

		MyFile.close();
	} while (!IsDataLoaded);
	return MatrixObj;
}