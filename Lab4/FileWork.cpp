// FileWork.cpp
// ������������ ������ �4.
// ������� ������ 494, ����� ����� �������. 2020 ���

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
		string buff = TextObj.GetStringOfNums();
		myFile << TextObj.GetChangedText();
		myFile << buff << endl;
		myFile.close();
		cout << "������ ������ ���������." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}

void OutputSourceData(Text& TextObj) {
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
		myFile << TextObj.GetText();
		myFile.close();
		cout << "������ ������ ���������." << endl;
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
		string TextRow,SourceText;
		SourceText = "";
		while (!MyFile.eof()) {
			getline(MyFile, TextRow);
			SourceText += TextRow+"\n";
		}

		TextObj = new Text();
		TextObj->Append(SourceText);
		
		cout << "�������� ������ ���������." << endl;
		IsDataLoaded = true;

		MyFile.close();
	} while (!IsDataLoaded);
	return TextObj;
}