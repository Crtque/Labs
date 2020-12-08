// Interface.h
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год
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