// EnglishProgramm.cpp: ���������� ����� ����� ��� ����������� ����������.
// ��������� ��� ������������ ����������� ������ �� ������������ �����.

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "programm.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);			// ����� �� ������� ������� ����.
	SetConsoleOutputCP(1251);	// ���� � ������� ������� ����.
	Programm app;
	app.StartProgramm();
	_gettch();
	return 0;
}

