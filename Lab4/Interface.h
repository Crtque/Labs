// Interface.h
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#pragma once
#include "TextClass.h"

enum class InputType :int {
	QUIT=0,KEYBOARD, MYFILE, TEST,
	CNT=3
};

enum class SaveType:int{
	QUIT = 0, SAVECNT, SAVEEXT, CNT
};

enum class BoolType:int {
	QUIT=0,YES,NO
};

enum class SecondMenuType :int {
	QUIT=0,COUNT,JOIN,UPPER
};


InputType	SaveDialog			(Text&,bool FromFile=false);
void		SecondDialog		(Text&);
InputType	Selection			();
void		PrintStartMenu		();
void		PrintContinueMenu	();
void		PrintSecondMenu		();
void		PrintDataSaveMenu	();

enum		PathType			:int{
	NOTDEFFINED=-1,RELATIVE,ABSOLUTE
};