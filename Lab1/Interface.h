// Interface.h
// ������������ ������ �1.
// ������� ������ 494, ����� ����� �������. 2020 ���
#pragma once
#include "MathFunction.h"

enum class MenuItem {
	KEYBOARD = 1, RANDOM, MYFILE, TEST,
	QUIT = 0, SAVECNT, SAVEEXT, CNT,
	LOAD = 1, EXIT,
	YES=1,NO
};
MenuItem SaveDialog(MathFunction&);
MenuItem Selection();
void PrintStartMenu();
void PrintContinueMenu();
void PrintDataSaveMenu();
enum PathType{
	NOTDEFFINED=-1,RELATIVE,ABSOLUTE
};