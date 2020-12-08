// [--- Начало программы ---]
// Main.cpp
// Лабораторная работа №4.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

#include <iostream>
#include "Interface.h"
#include "TextClass.h"
#include <locale.h>
#include <windows.h>

using namespace std;

int main()
{
   InputType UserChoice = InputType::CNT;
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);
   setlocale(LC_ALL, "");
	SetColor(ConsoleColor::White, ConsoleColor::Black);
	cout << "Лабораторная работа  №4" << endl
		<< "Студента 494 группы Тагина Игоря" << endl
		<< "Вариант №27" << endl
		<< "Символьные строки" << endl << endl
		<< "Задание:" << endl
		<< "Необходимо разработать текстовый редактор с параметрами, определенными" << endl
		<< "номером варианта." << endl
		<< "1. Замена всех первых строчных букв слов прописными." << endl
		<< "2. Подсчет количества символов, строк, слов и абзацев." << endl 
		<< "3. Вставка текста из файла." << endl << endl
		<< "\nПрограмма позволяет пользователю ввести текст двумя способами:" << endl
		<< "1. Ввести текст с клавиатуры, прервав ввод командой '--END--'" << endl
		<< "2. Получить текст из файла" << endl
		<< "\nПрограмма производит преобразования текста," << endl
		<< "после чего выводит результат работы программы на экран" << endl << endl;
	system("pause");
	system("cls");
	
	do { UserChoice = Selection(); } while (UserChoice != InputType::QUIT);
	return 0;
	
}