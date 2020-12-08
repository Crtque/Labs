// FileWork.cpp
// ������������ ������ �1.
// ������� ������ 494, ����� ����� �������. 2020 ���
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "Input.h"
#include "MathFunction.h"
#include <direct.h>
#include <sstream>
#include <cctype>

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
						cout << "��������� ������������ ������: " << c << endl;
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
				cout << "����������� �������� �����: " << Token << endl;
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
				cout << "����������� ��� �����: " << Token << endl;
				PathIsOkay = false;
				return PathIsOkay;
			}
		}
	}
	return PathIsOkay;
}

void OutputResultData(MathFunction& MathFunc) {


	bool IsDataSaved = false;
	bool IsCurrentDir = false;
	bool IsNewFile = false;

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
		cout << "��������� ������ � ( ������� ���� � ����� ):" << endl;
		getline(cin, FilePath);
		if (!NameIsNormal(FilePath, AbsolutePathWOFilename)) {
			if (!NameIsNormal(StrOfCurrentDir + "\\" + FilePath, RelativePathWOFilename)) {
				cout << "��������� ���� �����������" << endl;
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
				cout << "���� �� ����������." << endl << endl
					<< "�������� ��������:" << endl
					<< "0. ������� ����� ����." << endl
					<< "1. ��������� ����." << endl;
				bool Repeat = GetBool();
				if (Repeat) {
					continue;
				}
				else {
					if (PathType == RELATIVE) {
						fs::create_directories(RelativePathWOFilename);
						FilePath = StrOfCurrentDir + '\\' + FilePath;

					}
					else if (PathType == ABSOLUTE) {
						fs::create_directories(AbsolutePathWOFilename);
					}
				}
			}
			else {
				FilePath = StrOfCurrentDir + '\\' + FilePath;
			}
		}

		if (ifstream(FilePath)) {
			cout << "���� ��� ����������." << endl << endl
				<< "�������� ��������:" << endl
				<< "0. ������������ ������������ ����." << endl
				<< "1. ��������� ����." << endl;
			bool IsAnother = GetBool();
			if (IsAnother) {
				continue;
			}
		}

		ofstream MyFile(FilePath, ofstream::app);


		if (!MyFile) {
			cout << "������ ���������. ��������� ����." << endl;
			MyFile.close();
			continue;
		}

		MyFile.close();
		MyFile.open(FilePath, ofstream::trunc);
		MyFile << MathFunc.GetStringOfResults();
		MyFile << "��� �������� ������:" << endl << MathFunc.GetStringOfFunction();
		MyFile << "������� ������: " << MathFunc.HighRange << endl << "������ ������: " << MathFunc.LowRange << endl;
		MyFile << "���������� ������� (��� ������ ��������): " << MathFunc.Divides << endl;
		MyFile.close();
		cout << "������ ������ ���������." << endl;
		IsDataSaved = true;
	} while (!IsDataSaved);
}

void OutputSourceData(MathFunction& MathFunc) {


	bool IsDataSaved = false;
	bool IsCurrentDir = false;
	bool IsNewFile = false;

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
		cout << "��������� ������ � ( ������� ���� � ����� ):" << endl;
		getline(cin, FilePath);
		if (!NameIsNormal(FilePath, AbsolutePathWOFilename)) {
			if (!NameIsNormal(StrOfCurrentDir + "\\" + FilePath, RelativePathWOFilename)) {
				cout << "��������� ���� �����������" << endl;
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
				cout << "���� �� ����������." << endl << endl
					<< "�������� ��������:" << endl
					<< "0. ������� ����� ����." << endl
					<< "1. ��������� ����." << endl;
				bool Repeat = GetBool();
				if (Repeat) {
					continue;
				}
				else {
					if (PathType == RELATIVE) {
						fs::create_directories(RelativePathWOFilename);
						FilePath = StrOfCurrentDir + '\\' + FilePath;

					}
					else if (PathType == ABSOLUTE) {
						fs::create_directories(AbsolutePathWOFilename);
					}
				}
			}
			else {
				FilePath = StrOfCurrentDir + '\\' + FilePath;
			}
		}

		if (ifstream(FilePath)) {
			cout << "���� ��� ����������." << endl << endl
				<< "�������� ��������:" << endl
				<< "0. ������������ ������������ ����." << endl
				<< "1. ��������� ����." << endl;
			bool IsAnother = GetBool();
			if (IsAnother) {
				continue;
			}
		}

		ofstream MyFile(FilePath, ofstream::app);


		if (!MyFile) {
			cout << "������ ���������. ��������� ����." << endl;
			MyFile.close();
			continue;
		}

		MyFile.close();
		MyFile.open(FilePath, ofstream::trunc);
		MyFile << MathFunc.HighDeegreeOfX << " ";
		double* x = MathFunc.GetArrX();
		for (int i = MathFunc.HighDeegreeOfX; i >= 0; i--)
			MyFile << x[i] << " ";
		MyFile << MathFunc.HighRange << " ";
		MyFile << MathFunc.LowRange << " ";
		MyFile << MathFunc.Divides << " " << endl;
		MyFile.close();
		cout << "������ ������ ���������." << endl;
		IsDataSaved = true;
	} while (!IsDataSaved);
}

MathFunction* InputData() {
	string FilePath;
	bool IsDataLoaded = false;
	char* CurrentDir;
	const int MinDivides = 1000;
	const int MaxDivides = 10000;
	MathFunction* MathFunc = nullptr;
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
		int MaxDeegre;
		double HighRange, LowRange;
		int Divides;
		double* Arr;
		

		if (!(MyFile >> MaxDeegre) || MaxDeegre <= 0 || MaxDeegre > MAX_DEEGRE_OF_X) {
			
			cout << "������������ ������ ������� X." << endl;
			MyFile.close();
			continue;
		}

		Arr = new double[MaxDeegre+1];
		for (int i = MaxDeegre; i >= 0; i--) {
			if (!(MyFile >> Arr[i])) {
				cout << "������������ ������. ������ � ������������ ��� x^" << i << endl;
				MyFile.close();
				continue;
			}
		}

		if (!(MyFile >> HighRange)){
			cout << "������������ ������ ��� �������� ������� ��������������." << endl;
			MyFile.close();
			continue;
		}
		if (!(MyFile >> LowRange)) {
			cout << "������������ ������ ��� ������� ������� ��������������." << endl;
			MyFile.close();
			continue;
		}

		if (!(MyFile >> Divides) || Divides < MinDivides || Divides > MaxDivides) {
			cout << "������������ ������. ���������� ������� �� ����� ���� ������ " << MinDivides <<" ��� ������ "<< MaxDivides << endl;
			MyFile.close();
			continue;
		}
		MathFunc = new MathFunction(Arr, MaxDeegre, HighRange, LowRange, Divides);
		cout << "�������� ������ ���������." << endl;
		IsDataLoaded = true;

		MyFile.close();
	} while (!IsDataLoaded);
	return MathFunc;
}