// FileWork.h
// ������������ ������ �1.
// ������� ������ 494, ����� ����� �������. 2020 ���

#pragma once
#include "MathFunction.h"
#include <string>
void OutputResultData(MathFunction&);
void OutputSourceData(MathFunction&);
bool NameIsNormal(std::string);
MathFunction* InputData();