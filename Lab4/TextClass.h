// TextClass.h
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#pragma once
#include <string>
using namespace std;

class Text
{
private:
	string	_Text			= "";
	string	_ChangedText	= "";
	int		_NumOfParas		= 0;
	int		_NumOfWords		= 0;
	int		_NumOfRows		= 0;
	int		_NumOfSymbs		= 0;

public:
			Text			(string Text="");
	void	Add				();
	string	Append			(string Text);
	void	CountAll		();
	string	GetText			();
	string	GetStringOfNums	();
	string	GetChangedText	();
	string	ToUpperCase		();
	bool	Join			(Text*,int);
	bool	IsEqual			(Text* SecondText,bool PrintError);
};


enum class ConsoleColor {
	Black		= 0,
	Blue		= 1,
	Green		= 2,
	Cyan		= 3,
	Red			= 4,
	Magenta		= 5,
	Brown		= 6,
	LightGray	= 7,
	DarkGray	= 8,
	LightBlue	= 9,
	LightGreen	= 10,
	LightCyan	= 11,
	LightRed	= 12,
	LightMagenta = 13,
	Yellow		= 14,
	White		= 15
};

void SetColor(ConsoleColor, ConsoleColor background = ConsoleColor::Black);