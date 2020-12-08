// MatrixClass.cpp
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include <string>
#include <sstream>
#include "MatrixClass.h"
#include "Sorting.h"
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

	Matrix::Matrix(int width, int height){
		_NamesOfSorts = new string[5];
		_NamesOfSorts[0] = "Shell";
		_NamesOfSorts[1] = "Bubble";
		_NamesOfSorts[2] = "Select";
		_NamesOfSorts[3] = "Insert";
		_NamesOfSorts[4] = "Quick";
		_CurrentColumn = 0;
		_CurrentRow = 0;
		_Width = width;
		_Height = height;
		_ChangedMatrix = new int** [NUMBER_SORTS];
		_DiagArr = new int*[NUMBER_SORTS];
		_LowerPartArr = new int* [NUMBER_SORTS];
		_UpperPartArr = new int* [NUMBER_SORTS];
		_SourceMatrix = new int* [_Height];

		_Swaps = new int[NUMBER_SORTS];
		_Compares = new int[NUMBER_SORTS];

		for (int i = 0; i < width; i++) {
			
			if (height == width) {
				_NumOfLower += height - i - 1;
				_NumOfUpper = _NumOfLower;
			}
			else if(height > width){
				int buff = height - i - 1;
				_NumOfLower += buff;
				_NumOfUpper = (width * height) - width - _NumOfLower;
			}
			else if(height < width){
				if (i < (height-1)) {
					int buff = height - i - 1;
					_NumOfLower += buff;
				}
				_NumOfUpper = (width * height) - height - _NumOfLower;
			}
		}
	

		for (int i = 0; i < NUMBER_SORTS; i++) {
			_ChangedMatrix[i] = new int* [_Height];
			_DiagArr[i] = new int[min(_Width, _Height)];
			_Swaps[i] = _Compares[i] = 0;
			if (_NumOfLower > 0) {
				_LowerPartArr[i] = new int[_NumOfLower];
			}
			if (_NumOfUpper > 0) {
				_UpperPartArr[i] = new int[_NumOfUpper];
			}
		}

		for (int i = 0; i < _Height; i++) {
			_SourceMatrix[i] = new int[_Width];
			for (int j = 0; j < NUMBER_SORTS; j++) {
				_ChangedMatrix[j][i] = new int[_Width];
			}
		}
	}

	Matrix::~Matrix() {
		for (int i = 0; i < _Height; i++) {
			delete [] _SourceMatrix[i];
			for (int j = 0; j < NUMBER_SORTS; j++) {
				delete[] _ChangedMatrix[j][i];

			}
		}

		for (int j = 0; j < NUMBER_SORTS; j++) {
			delete[] _ChangedMatrix[j];
			delete[] _DiagArr[j];
			if (_NumOfLower > 0){
				delete[] _LowerPartArr[j];
			}
			if (_NumOfUpper > 0) {
				delete[] _UpperPartArr[j];
			}
		}
		
		delete[] _SourceMatrix;
		delete[] _ChangedMatrix;

		delete[] _DiagArr;
		delete[] _LowerPartArr;
		delete[] _UpperPartArr;

		delete[] _NamesOfSorts;
		delete[] _Swaps;
		delete[] _Compares;
	}
	
	int Matrix::GetNumberOfSorts() {
		return NUMBER_SORTS;
	}
	string Matrix::GetNameOfSort(int Num) {
		return _NamesOfSorts[Num];
	}

	int Matrix::GetNumberOfSwaps(int Num) {
		return _Swaps[Num];
	}

	int Matrix::GetNumberOfCompares(int Num) {
		return _Compares[Num];
	}

	int Matrix::GetWidth() {
		return this->_Width;
	}

	int Matrix::GetHeight() {
		return this->_Height;
	}

	void Matrix::Sort() {
		typedef void(*FunctionArr)(int*&,int,int&,int&);
		FunctionArr Functions[] = { Shell,Bubble,SelectionSort,Insertion};
		size_t CountOfFunctions = sizeof(Functions) / sizeof(Functions[0]);
		int DiagCounter = 0, UpperCounter = _NumOfUpper - 1, LowerCounter = 0;
		
		for (unsigned int i = 0; i < CountOfFunctions; i++) {
			DiagCounter = 0, UpperCounter = _NumOfUpper - 1, LowerCounter = 0;
			Functions[i](_DiagArr[i], min(_Width, _Height),_Swaps[i],_Compares[i]);
			Functions[i](_UpperPartArr[i], _NumOfUpper, _Swaps[i], _Compares[i]);
			Functions[i](_LowerPartArr[i], _NumOfLower, _Swaps[i], _Compares[i]);
			for (int j = 0; j < _Height; j++) {
				for (int k = 0; k < _Width; k++) {
					if (j == k) {
						_ChangedMatrix[i][j][k] = _DiagArr[i][DiagCounter++];
					}
					else if(k > j){
						_ChangedMatrix[i][j][k] = _UpperPartArr[i][UpperCounter--];
					}
					else {
						_ChangedMatrix[i][j][k] = _LowerPartArr[i][LowerCounter++];
					}
				}
			}
		}
		DiagCounter = 0, UpperCounter = _NumOfUpper - 1, LowerCounter = 0;
		if ((min(_Width, _Height) - 1 > 0)) {
			QuickSort(_DiagArr[4], 0, min(_Width, _Height) - 1, _Swaps[4], _Compares[4]);
		}
		if (_NumOfUpper > 0) {
			QuickSort(_UpperPartArr[4], 0, _NumOfUpper - 1, _Swaps[4], _Compares[4]); 
		}
		if (_NumOfLower > 0) {
			QuickSort(_LowerPartArr[4], 0, _NumOfLower - 1, _Swaps[4], _Compares[4]);
		}
		for (int j = 0; j < _Height; j++) {
			for (int k = 0; k < _Width; k++) {
				if (j == k) {
					_ChangedMatrix[4][j][k] = _DiagArr[4][DiagCounter++];
				}
				else if (k > j) {
					_ChangedMatrix[4][j][k] = _UpperPartArr[4][UpperCounter--];
				}
				else {
					_ChangedMatrix[4][j][k] = _LowerPartArr[4][LowerCounter++];
				}
			}
		}

	}
	
	int Matrix::Append(int value) {
		_SourceMatrix[_CurrentRow][_CurrentColumn] = value;
		if (_CurrentRow == _CurrentColumn) {
			for (int i = 0; i < NUMBER_SORTS; i++) {
				_DiagArr[i][_CurrentDiag] = value;
			}
			_CurrentDiag++;
		}
		else if (_CurrentColumn > _CurrentRow) {
			for (int i = 0; i < NUMBER_SORTS; i++) {
			_UpperPartArr[i][_CurrentUpper] = value;
			}
			_CurrentUpper++;
		}
		else if (_CurrentRow > _CurrentColumn) {
			for (int i = 0; i < NUMBER_SORTS; i++) {
			_LowerPartArr[i][_CurrentLower] = value;
			}
			_CurrentLower++;
		}

		if (abs(value) >= _MaxAbs) {
			_MaxAbs = abs(value);
			_MaxAbsC = _CurrentColumn;
			_MaxAbsR = _CurrentRow;
		}

		if ((_CurrentColumn + 1) > (_Width - 1)) {
			_CurrentRow++;
			_CurrentColumn = 0;
		}
		else {
			_CurrentColumn++;
		}
		return value;
	}

	int Matrix::GetValueOfCell(int Row, int Column, int Number) {
		int** MatrixPtr;
		if (Number == -1) {
			MatrixPtr = _SourceMatrix;
		}
		else {
			MatrixPtr = _ChangedMatrix[Number];
		}
		return MatrixPtr[Row][Column];
	}



	string Matrix::GetStringOfSourceMatrix(bool ToPrint) {
		stringstream MatrixString;
		string Result = "";
		int** StrPtr;
		StrPtr = _SourceMatrix;
		SetColor(ConsoleColor::Green);
		for (int i = 0; i < _Height; i++) {
			for (int j = 0; j < _Width; j++) {
				if (!ToPrint) {
					MatrixString << StrPtr[i][j] << "\t";
				}
				else
				{
					if ((i == j)) {
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
	string Matrix::GetSortsTable(bool ToPrint) {
		stringstream TableSS;
		string Result = "";
			TableSS << endl << "\t";
			for (int i = 0; i < this->GetNumberOfSorts(); i++) {
				TableSS << "\t" << this->_NamesOfSorts[i];
			}
			TableSS << endl << "Обмены:\t";
			for (int i = 0; i < this->GetNumberOfSorts(); i++) {
				TableSS << "\t" << this->GetNumberOfSwaps(i);
			}
			TableSS << endl << "Сравнения:";
			for (int i = 0; i < this->GetNumberOfSorts(); i++) {
				TableSS << "\t" << this->GetNumberOfCompares(i);
			}
			TableSS << endl;

		if(ToPrint) {
			cout << endl << "\t";
			for (int i = 0; i < this->GetNumberOfSorts(); i++) {
				cout << "\t" << this->_NamesOfSorts[i];
			}
			cout << endl << "Обмены:\t";
			for (int i = 0; i < this->GetNumberOfSorts(); i++) {
				cout << "\t" << this->GetNumberOfSwaps(i);
			}
			cout << endl << "Сравнения:";
			for (int i = 0; i < this->GetNumberOfSorts(); i++) {
				cout << "\t" << this->GetNumberOfCompares(i);
			}
			cout << endl;
		}
		Result = TableSS.str();
		TableSS.clear();
		return Result;
	
	}
	string Matrix::GetStringOfChangedMatrix(bool ToPrint,int Num) {
		stringstream MatrixString;
		string Result = "";
		int*** StrPtr;
		StrPtr = _ChangedMatrix;
		SetColor(ConsoleColor::Green);
		for (int i = 0; i < _Height; i++) {
			for (int j = 0; j < _Width; j++) {
				
					MatrixString << StrPtr[Num][i][j] << "\t";
				
				if(ToPrint)
				{
					if ((i == j)) {
						SetColor(ConsoleColor::Yellow);
					}


					cout << StrPtr[Num][i][j] << "\t";
					SetColor(ConsoleColor::Green);
				}
			}
			
				MatrixString << endl;
			
			if(ToPrint){
				cout << endl;
			}
		}
		SetColor(ConsoleColor::White);
		Result = MatrixString.str();
		MatrixString.clear();
		return Result;
	}

	bool Matrix::EqualsTo(Matrix* ComparingMatrix, int isFirstSource, int isSecondSource,bool PrintError) {
		bool Result = true;
		for (int i = 0; i < _Height; i++) {
			for (int j = 0; j < _Width; j++) {
				if (!(this->GetValueOfCell(i, j, isFirstSource) == ComparingMatrix->GetValueOfCell(i, j, isSecondSource))) {
					Result = false;
					if (PrintError) {
						cout << endl << "Несоотвествие значения " << this->GetValueOfCell(i, j, isSecondSource) << " ячейки строки: "
							<< i + 1 << " столбца: " << j + 1 << " со значением " << ComparingMatrix->GetValueOfCell(i, j, isSecondSource) << endl;
					}
				}
			}
		}
		return Result;
	}

