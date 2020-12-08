// MatrixClass.h
// Лабораторная работа №2.
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
	int** _ChangedMatrix;
	int _CurrentRow=0, _CurrentColumn=0,_Width,_Height;
	int _ChangingRow=0, _ChangingColumn=0;
	int _ComparingValue = 0;
public:
	Matrix(int width, int height,int ComparingValue);
	~Matrix();
	int GetWidth();
	int GetHeight();
	int GetReq();
	bool EqualsTo(Matrix* ComparingMatrix, bool isFirstSource, bool isSecondSource);
	int Append(int value);
	int GetValueOfCell(int Row, int Column, bool Source = true);
	typedef bool(Matrix::*BoolFunction)(int);
	typedef void(Matrix::*VoidFunction)(int,int);
	int CheckEachCell(BoolFunction ComparingFunction, VoidFunction ApplyingToCellFunction);
	void Swap(int OldI, int OldJ);
	bool EqualsToComparing(int value);
	std::string GetStringOfMatrix(bool ToPrint = false,bool Source = true);
};
