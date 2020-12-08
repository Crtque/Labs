// Input.h
// ������������ ������ �1.
// ������� ������ 494, ����� ����� �������. 2020 ���

#pragma once
#include "Interface.h"
const int HighRangeForRand = 100;
const int LowRangeForRand = 1;
template<typename T>
T GetInput();
int GetInt(int = INT_MIN, int = INT_MAX);
double GetDouble();
bool GetBool();
double RandomNeg(double);
int GetRandomInt(int = HighRangeForRand, int = LowRangeForRand);
double GetRandomDouble(int = HighRangeForRand, int = LowRangeForRand);
MenuItem GetMenuItem(MenuItem,MenuItem);