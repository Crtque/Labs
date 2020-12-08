// MatrixClass.cpp
// Лабораторная работа №2.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include <string>
#include <sstream>
#include "MatrixClass.h"
#include <Windows.h>
using namespace std;
void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((static_cast<WORD>(background) << 4) | static_cast<WORD>(text)));
}
bool isEqual(double x, double y) {
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

	Matrix::Matrix(int width, int height,int ComparingValue){
		_CurrentColumn = 0;
		_CurrentRow = 0;
		_ComparingValue = ComparingValue;
		_Width = width;
		_Height = height;
		_SourceMatrix = new int* [height];
		_ChangedMatrix = new int* [height];
		for (int i = 0; i < height; i++) {
			_SourceMatrix[i] = new int[width];
			_ChangedMatrix[i] = new int[width];
		}
	}

	Matrix::~Matrix() {
		for (int i = 0; i < _Height; i++) {
			delete [] _SourceMatrix[i];
			delete [] _ChangedMatrix[i];
		}
		delete [] _SourceMatrix;
		delete [] _ChangedMatrix;

	}
	bool Matrix::EqualsTo(Matrix* ComparingMatrix, bool isFirstSource,bool isSecondSource) {
		bool Result = true;
		for (int i = 0; i < _Height; i++) {
			for (int j = 0; j < _Width; j++) {
				if (!(this->GetValueOfCell(i, j,isFirstSource) == ComparingMatrix->GetValueOfCell(i, j,isSecondSource))) {
					//cout << " " << i << " " << j << endl;
					Result = false;
				}
			}
		}
		return Result;
	}

	int Matrix::GetWidth() {
		return this->_Width;
	}

	int Matrix::GetHeight() {
		return this->_Height;
	}

	int Matrix::GetReq() {
		return this->_ComparingValue;
	}


	bool Matrix::EqualsToComparing(int value) {
		return value == _ComparingValue;
	}

	int Matrix::Append(int value) {
		_SourceMatrix[_CurrentRow][_CurrentColumn] = _ChangedMatrix[_CurrentRow][_CurrentColumn] = value;
		if ((_CurrentColumn + 1) > (_Width - 1)) {
			_CurrentRow++;
			_CurrentColumn = 0;
		}
		else {
			_CurrentColumn++;
		}
		return value;
	}

	int Matrix::GetValueOfCell(int Row, int Column, bool Source) {
		int** MatrixPtr;
		if (Source) {
			MatrixPtr = _SourceMatrix;
		}
		else {
			MatrixPtr = _ChangedMatrix;
		}
		return MatrixPtr[Row][Column];
	}



	void Matrix::Swap(int OldI, int OldJ) {
		int Buff = GetValueOfCell(OldI,OldJ);
		_ChangedMatrix[OldI][OldJ] = _ChangedMatrix[_ChangingRow][_ChangingColumn];
		_ChangedMatrix[_ChangingRow][_ChangingColumn] = Buff;

		if ((_ChangingColumn + 1) > (_Width - 1)) {
			_ChangingColumn = 0;
			_ChangingRow++;
		}
		else {
			_ChangingColumn++;
		}
	}
	typedef bool (Matrix::*SomeClassFunction) (int);
	int Matrix::CheckEachCell(BoolFunction ComparingFunction,VoidFunction ApplyingToCellFunction) { //возвращает количество найденых элементов
		int Count = 0;
		for (int i = 0; i < _Height; i++) {
			for (int j = 0; j < _Width; j++) {
				if ((this->*ComparingFunction)(this->GetValueOfCell(i, j))) {
					Count++;
					(this->*ApplyingToCellFunction)(i, j);
				}
			}
		}
		return Count;
	}

	string Matrix::GetStringOfMatrix(bool ToPrint,bool Source) {
		stringstream MatrixString;
		string Result = "";
		int** StrPtr;
		if (Source) {
			StrPtr = _SourceMatrix;
		}
		else {
			StrPtr = _ChangedMatrix;
		}
		SetColor(ConsoleColor::Green);
		for (int i = 0; i < _Height; i++) {
			for (int j = 0; j < _Width; j++) {
				if (!ToPrint) {
					MatrixString << StrPtr[i][j] << "\t";
				}
				else {
					if (StrPtr[i][j] == _ComparingValue) {
						SetColor(ConsoleColor::Yellow);
					}
					cout << StrPtr[i][j] << "\t";
					SetColor(ConsoleColor::Green);
				}
			}
			if (!ToPrint) {
				MatrixString << endl;
			}
			else {
				cout << endl;
			}
		}
		SetColor(ConsoleColor::White);
		Result = MatrixString.str();
		MatrixString.clear();
		return Result;
	}

	