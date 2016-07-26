// EnglishProgramm.cpp: определяет точку входа для консольного приложения.
// Программа для тестирования слованрного запаса по английсского языка.

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "programm.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);			// Вывод из консоли русских букв.
	SetConsoleOutputCP(1251);	// Ввод в консоль русских букв.
	Programm app;
	app.StartProgramm();
	_gettch();
	return 0;
}

