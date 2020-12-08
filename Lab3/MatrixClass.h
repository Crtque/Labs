// MatrixClass.h
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#pragma once
#include <string>

enum class ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

bool isEqual(double,double);
void SetColor(ConsoleColor, ConsoleColor background = ConsoleColor::Black);
class Matrix
{
private:
	int** _SourceMatrix;
	int***_ChangedMatrix;
	int** _DiagArr;
	int** _LowerPartArr;
	int** _UpperPartArr;
	int _NumOfUpper = 0;
	int _NumOfLower = 0;
	int* _Swaps,*_Compares;
	const int NUMBER_SORTS = 5;
	int _CurrentRow=0, _CurrentColumn=0,_Width,_Height;
	int _CurrentLower = 0, _CurrentUpper = 0,_CurrentDiag=0;
	int _ChangingRow=0, _ChangingColumn=0;
	int _MaxAbs=0, _MaxAbsR=0, _MaxAbsC=0;
	int _ComparingValue = 0;
	std::string* _NamesOfSorts;
public:
	Matrix(int width, int height);
	~Matrix();
	int GetWidth();
	int GetHeight();
	int GetNumberOfSwaps(int Num=0);
	int GetNumberOfCompares(int Num=0);
	int Append(int value);
	void Sort();
	int GetNumberOfSorts();
	std::string GetNameOfSort(int Num);
	int GetValueOfCell(int Row, int Column,int Number);
	bool EqualsTo(Matrix* ComparingMatrix, int isFirstSource, int isSecondSource,bool PrintError=false);
	std::string GetStringOfSourceMatrix(bool ToPrint = false);
	std::string GetStringOfChangedMatrix(bool ToPrint,int Num);
	std::string GetSortsTable(bool ToPrint = false);
};
