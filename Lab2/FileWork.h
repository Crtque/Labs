// FileWork.h
// Лабораторная работа №2.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#pragma once
#include "MatrixClass.h"
#include <string>
void OutputResultData(Matrix&);
void OutputSourceData(Matrix&);
bool NameIsNormal(std::string);
Matrix* InputData();