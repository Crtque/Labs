// FileWork.h
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#pragma once
#include "MathFunction.h"
#include <string>
void OutputResultData(MathFunction&);
void OutputSourceData(MathFunction&);
bool NameIsNormal(std::string);
MathFunction* InputData();