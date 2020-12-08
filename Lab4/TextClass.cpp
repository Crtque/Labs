// TextClass.cpp
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include <string>
#include <algorithm>
#include "Input.h"
#include <sstream>
#include "TextClass.h"
#include <Windows.h>

using namespace std;
Text::Text(string Text) {
	this->Append(Text);
}

void Text::Add() {
	string Text = "";
	cout << "Вводите текст. Для прекращения ввода отправьте \"--END--\""<< endl; 
       do
       {
            getline(cin, Text);
            if (Text != "--END--") {
                Append(Text + "\n");
            }
       } while (Text != "--END--");
    
	
}

string Text::Append(string Text) {
	_Text = _Text + Text;
	_ChangedText = _Text;
	return _Text;
}

string Text::GetText() {
	return _Text + "\n";
}
string Text::GetChangedText() {
	return _ChangedText;
}

string Text::GetStringOfNums() {
	stringstream SS("");
	CountAll();
	SS << "Количество строк: " << _NumOfRows << '\n';
	SS << "Количество символов: " << _NumOfSymbs << '\n';
	SS << "Количество слов: " << _NumOfWords << '\n';
	SS << "Количество абзацев: " << _NumOfParas << '\n';
	return SS.str();
}


string Text::ToUpperCase() {
	stringstream StringStream(_ChangedText);
	int Num = 1;
	_ChangedText = "";
	string Token = "";
	char NormalLetters[] = { 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m','й','ц','у','к','е','н','г','ш','щ','з','х','ъ','ф','ы','в','а',
		'п','р','о','л','д','ж','э','я','ч','с','м','и','т','ь','б','ю'};
	int NumOfNormalLetters = 60;
	string Row = "";
	while (getline(StringStream, Row, '\n')) {
		stringstream RowStream(Row);
		while (getline(RowStream, Token, ' ')) {
			if (Token != "") {
				bool Done = false;
				transform(Token.begin(), Token.end(), Token.begin(),
					[&Done, NumOfNormalLetters,&NormalLetters](unsigned char c) {
						bool isOk = false;
						for (int i = 0; i < NumOfNormalLetters; i++) {
							if (static_cast<char>(std::tolower(c)) == static_cast<char>(NormalLetters[i])) {
								isOk = true;
								break;
							}
						}

						if (isOk) {
							if (!Done) {
								Done = true;
								return std::toupper(c);
							}
							else {
								return static_cast<int>(c);
							}
						}
						else {
							return static_cast<int>(c);
						}
					});
				
			}
			_ChangedText += Token + " ";
		}
		RowStream.clear();
		Num++;
		_ChangedText += "\n";
	}
	StringStream.clear();
    return _ChangedText;
}

void Text::CountAll() {

	stringstream StringStream(_ChangedText);

	int		NumOfRows	= 0;
	int		NumOfSymbs	= 0;
	int		NumOfParas	= 0;
	int		NumOfWords	= 0;
	string	Token		= "";
	string	Row			= "";

	while (getline(StringStream, Row, '\n')) {
		NumOfRows++;
		stringstream RowStream(Row);
		while (getline(RowStream, Token, ' ')) {
			if (Token != "") {
				NumOfWords++;
				transform(Token.begin(), Token.end(), Token.begin(),
					[&NumOfSymbs,&NumOfParas](unsigned char c) {
						NumOfSymbs++;
						if (c == '\t') {
							NumOfParas++;
						}
						return c;
					});

			}
		}
		RowStream.clear();
		
	}
	StringStream.clear();
	_NumOfRows	= NumOfRows	;
	_NumOfSymbs = NumOfSymbs;
	_NumOfParas = NumOfParas;
	_NumOfWords = NumOfWords;
}

bool Text::Join(Text* TextObjToJoin, int Pos) {
	stringstream StringStr("");
	if (Pos == -1) {
		StringStr << _ChangedText;
		StringStr << TextObjToJoin->GetText();
	}
	else if(Pos==0){
		StringStr << TextObjToJoin->GetText();
		StringStr << _ChangedText;
	}
	else {
		stringstream StringStream(_ChangedText);

		int		NumOfRows	= 0;
		string	Token		= "";
		string	Row			= "";

		while (getline(StringStream, Row, '\n')) {
			NumOfRows++;
			StringStr << Row << '\n';
			if (NumOfRows == Pos) {
				StringStr << TextObjToJoin->GetText();
			}
		

		}
		StringStream.clear();
		if (NumOfRows < Pos) { return false; }
	
	}
	this->_ChangedText = StringStr.str();
	StringStr.clear();
	return true;
}

bool Text::IsEqual(Text* SecondText,bool PrintError) {
	if (this->_ChangedText == SecondText->GetText()) {
		return true;
	}
	else {
		if (PrintError) {
			cout << "Ожидалось: " << endl << SecondText->GetText() << endl << endl << "Получено: " << endl << _ChangedText << endl;
		}
		return false;
	}
}

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((static_cast<WORD>(background) << 4) | static_cast<WORD>(text)));
}