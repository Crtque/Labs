// Interface.h
// ������������ ������ �3.
// ������� ������ 494, ����� ����� �������. 2020 ���

#pragma once
#include "MatrixClass.h"

enum class InputType :int {
	QUIT=0,KEYBOARD, RANDOM, MYFILE, TEST,
	CNT=3
};

enum class SaveType:int{
	QUIT = 0, SAVECNT, SAVEEXT, CNT
};

enum class BoolType:int {
	QUIT=0,YES,NO
};


InputType SaveDialog(Matrix&,bool FromFile=false);
InputType Selection();
void PrintStartMenu();
void PrintContinueMenu();
void PrintDataSaveMenu();
enum PathType:int{
	NOTDEFFINED=-1,RELATIVE,ABSOLUTE
};