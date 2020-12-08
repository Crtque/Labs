// UnitTest.cpp
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include "TextClass.h"
#include <memory>
using namespace std;


bool LaunchTest(Text* ControlText, string TestStr, int ToJoin,bool PrintError) {
	bool	Result		= true;
	Text*	TestText	= new Text();
	TestText->Append(TestStr);
	if (ToJoin == 0) {
		TestText->ToUpperCase();
	}
	else {
		TestText->Join(new Text("Вставка"), ToJoin);
	}
	if (TestText->IsEqual(ControlText,PrintError)) {
		Result = true;
	}
	else {
		Result = false;
	}
	delete TestText;
	return Result;
}

bool Test_TestStr(bool PrintError = false){
	Text*	ControlText = new Text();
	string	Txt			= "Тест ";
	string	TestStr		= "тест";
	ControlText->Append(Txt);
	bool Result = LaunchTest(ControlText, TestStr, 0, PrintError);
	delete ControlText;
	return Result;
}


bool Test_Join(bool PrintError = false)
{
	Text*	ControlText	= new Text();
	string	Txt			= "\tПервый абзац первая строка.\nпервЫй абзац вторая стРока С Ошибками.\n\nВставка\n\tВторой абзац Первая строка.\nВторой абзац вторая Строка.";
	string	TestStr		= "\tПервый абзац первая строка.\nпервЫй абзац вторая стРока С Ошибками.\n\n\tВторой абзац Первая строка.\nВторой абзац вторая Строка.";
	ControlText->Append(Txt);
	bool Result = LaunchTest(ControlText, TestStr, 3, PrintError);
	delete ControlText;
	return Result;
}


bool StartTest() {
    bool	Result = true;
    typedef bool(*FunctionArr)(bool);
    FunctionArr Functions[] = { Test_TestStr, Test_Join};
    size_t CountOfFunctions = sizeof(Functions) / sizeof(Functions[0]);
    for (unsigned int i = 0; i < CountOfFunctions; i++) {
        if (!Functions[i](true)) {
            Result = false;
            std::cout << "Тестирование завершено с ошибкой. Ошибка в тесте: " << i + 1 << endl;
            break;
        }
    }
    if (Result) {
        std::cout << "Тестирование прошло успешно." << endl;
    }
    return Result;
}
