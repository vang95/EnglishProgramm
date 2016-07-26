#pragma once

 // ��������� ��� ��������� ���������� ����
 // ����������: 
 // 1. ����� ����� ���� ������, � �� ���������
 // 2. ���� ������ �����(����� � ����)
 // 3. ����� ���������� ���� ��� ������������: ���� ��������, ��� �����
 // 4. ����� ������ ������������: ��������� - �������, ������� - ����������, �����
 // 5. ����� ���� ����: ����������, �������, ������� - ����������

#include "Word.h"
#include "excepted.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

typedef std::vector<Word> tBase;

class Programm
{
public:
	enum ModeFile{ In, Out };								// ����������� �����.
public:
	Programm();
	//~Programm();
public:
	void StartProgramm();									// ������ ������ ���������.
	void ExitPogramm();										// ���������� ������ ���������.								
public:															
	 /* ���������������� ���������: */
	void setNameFileBase();									// ��������� �������� ����� ���� ������.
	void Menu();											// ������� ����.
	void addWord();											// ���������� ����� � ���� ������.
	void showBaseWords();									// �������� ���� ���� ���� ������.
	void testing();											// ������� ������������ ������������.
private:
	/* �������, ��������� � ������� ���� ������: */
	void _showFullBase();									// ����� ���� ���� ����.
	void _showBaseEnglWords(std::size_t size);				// ����� ���� ������, ���������� �������: ������������� ���������� ����.
	void _showBaseRusWords(std::size_t size);				// ����� ���� ������, ������� �������: ������������� ���������� ����.
	void _randomlyWords();									// ������������ ���� � ���� ������.
private:
	/* �������, ����������� ������������ */
	void _testingWordAnswer();								// ������������: �� ����� ���������� ��� ������� ������ �����, ��������� �������� ���������������
	void __testingWordEnter();								// ������������: �� ����� ���������� ��� ������� ������ �����, ��������� ������ ���������������
private:
	/* �������, ���������� � ��������� ����� ������: */
	void _findWordBase();									// ����� ����� � ���� ������.
	void _findWordInBase(const std::string & query) const;	// ������ �� ����� ����� � ���� ������.
	bool _findPartInWord(const Word & word, const std::string & part) const;	// ����� �������� � �����
	bool _findPartInWord(const std::string & inWord, const std::string & part) const; // �������� ��������
	void _sortedWordsBase();								// ���������� ���� � ���� ������.
	void _sortedWordsBaseEngl();							
	void _sortedWordsBaseRus();								
	void _sortedWordsBaseType();														
	void _deleteWord() const;								// �������� ����� �� ���� ������.	
private:
	 /* �������������� ��������� � ������ ���� ������: */
	void _setNameFileBase(const std::string & nameFile);	// ��������� ������� ����� ���� ������.
	bool _loadFileBase();									// �������� ���� �� ���� ���� ������.
	bool _saveLocalBaseInFile();							// ���������� ������ � ����.
	bool _deleteWordInFileBase();							// �������� ����� �� ���� ���� ������.	
	bool _openFileBase(ModeFile mode);						// �������� ����� ���� ������.
	void _closeFileBase();									// �������� ����� ���� ������.
	bool _addWordinFile(Word & word);						// ���������� ����� � ���� ������ �����.
private:
	std::string		m_nameFile;								// ������� ���� ���� ������.
	std::fstream	m_filebase;								// ����� �������������� � ������ ���� ������.
	tBase			m_base;									// ���� ����.
};

