// UnitTest.h
// Лабораторная работа №2.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год
#pragma once
bool LaunchTest(int Width, int Height, int Req, int SwapIndexV, int SwapIndexH, bool PrintError = false);
bool Test_Matrix_3x3(bool ToPrint = false);
bool Test_Matrix_5x5(bool ToPrint = false);
bool Test_Matrix_9x9(bool ToPrint = false);
bool Test_Matrix_5x2(bool PrintError = false);
bool Test_Matrix_1x5(bool PrintError = false);
bool StartTest();
