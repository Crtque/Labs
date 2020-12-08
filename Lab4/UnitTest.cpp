// UnitTest.cpp
// ������������ ������ �4.
// ������� ������ 494, ����� ����� �������. 2020 ���

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
		TestText->Join(new Text("�������"), ToJoin);
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
	string	Txt			= "���� ";
	string	TestStr		= "����";
	ControlText->Append(Txt);
	bool Result = LaunchTest(ControlText, TestStr, 0, PrintError);
	delete ControlText;
	return Result;
}


bool Test_Join(bool PrintError = false)
{
	Text*	ControlText	= new Text();
	string	Txt			= "\t������ ����� ������ ������.\n������ ����� ������ ������ � ��������.\n\n�������\n\t������ ����� ������ ������.\n������ ����� ������ ������.";
	string	TestStr		= "\t������ ����� ������ ������.\n������ ����� ������ ������ � ��������.\n\n\t������ ����� ������ ������.\n������ ����� ������ ������.";
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
            std::cout << "������������ ��������� � �������. ������ � �����: " << i + 1 << endl;
            break;
        }
    }
    if (Result) {
        std::cout << "������������ ������ �������." << endl;
    }
    return Result;
}
