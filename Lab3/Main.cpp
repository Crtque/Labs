// [--- Начало программы ---]
// Main.cpp
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include "Interface.h"

using namespace std;

int main()
{
   InputType UserChoice = InputType::CNT;
	setlocale(LC_ALL, "Russian");
	SetColor(ConsoleColor::White, ConsoleColor::Black);
	cout << "Лабораторная работа  №3" << endl
		<< "Студента 494 группы Тагина Игоря" << endl
		<< "Вариант №27" << endl
		<< "Методы сортировки" << endl << endl
		<< "Задание:" << endl
		<< "Упорядочить главную диагональ матрицы по возрастанию, данные сверху от" << endl
		<< "главной диагонали упорядочить по убыванию, снизу от главной диагонали по" << endl
		<< "возрастанию." << endl << endl
		<< "\nПрограмма позволяет пользователю задать матрицу тремя способами:" << endl
		<< "1. Ввести значения с клавиатуры" << endl
		<< "2. Позволить программе использовать случайные значения" << endl
		<< "3. Ввести значения из файла" << endl
		<< "\nПрограмма производит преобразования матрицы," << endl
		<< "после чего выводит результат работы программы на экран" << endl << endl;
	system("pause");
	system("cls");
	
	do { UserChoice = Selection(); } while (UserChoice != InputType::QUIT);
	return 0;
	
}