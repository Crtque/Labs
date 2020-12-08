﻿// [--- Начало программы ---]
// Main.cpp
// Лабораторная работа №1.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include "Interface.h"

using namespace std;

int main()
{
	MenuItem UserChoice = MenuItem::CNT;
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа  №1" << endl
		<< "Студента 494 группы Тагина Игоря" << endl
		<< "Вариант №13" << endl
		<< "Использование языка	программирования С++ для математических расчётов" << endl << endl
		<< "Задание:" << endl
		<< "Вычислить интеграл заданной функции методом трапеций и методом парабол."  << endl << endl
		<< "\nПрограмма позволяет пользователю задать массив тремя способами:" << endl
		<< "1. Ввести функцию с клавиатуры" << endl
		<< "2. Позволить программе использовать случайную функцию" << endl
		<< "3. Ввести функцию из файла" << endl
		<< "\nПрограмма находит численное значение интеграла функции,"
		<< "после чего выводит результат работы программы на экран" << endl << endl;
	system("pause");
	system("cls");
	
	do { UserChoice = Selection(); } while (UserChoice != MenuItem::QUIT);
	return 0;
	
}