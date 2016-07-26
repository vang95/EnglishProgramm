#pragma once

 // программа для генерации английских слов
 // функционал: 
 // 1. выбор файла базы данных, с ее загрузкой
 // 2. ввод нового слова(сразу в файл)
 // 3. выбор количества слов для тестирования: ввод значения, все слова
 // 4. выбор режима тестирования: аглийский - русский, русский - английский, любой
 // 5. вывод всех слов: английских, русских, русских - анлгийских

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
	enum ModeFile{ In, Out };								// Модификатор файла.
public:
	Programm();
	//~Programm();
public:
	void StartProgramm();									// Начало работы программы.
	void ExitPogramm();										// Завершение работы программы.								
public:															
	 /* пользовательский интерфейс: */
	void setNameFileBase();									// Установка название файла базы данных.
	void Menu();											// Главное меню.
	void addWord();											// Добавление слова в базу данных.
	void showBaseWords();									// Просмотр всех слов базы данных.
	void testing();											// Функция тестирования пользователя.
private:
	/* Функции, связанные с выводом базы данных: */
	void _showFullBase();									// Вывод всей базы слов.
	void _showBaseEnglWords(std::size_t size);				// Вывод базы данных, английский вариант: фиксированное количество слов.
	void _showBaseRusWords(std::size_t size);				// Вывод базы данных, русский вариант: фиксированное количество слов.
	void _randomlyWords();									// Рандомизация слов в базе данных.
private:
	/* Функции, реализующие тестирование */
	void _testingWordAnswer();								// Тестирование: на входе английская или русская версия слова, требуется ответить противоположную
	void __testingWordEnter();								// Тестирование: на входе английская или русская версия слова, требуется ввести противоположную
private:
	/* Функции, работающие с локальной базой данных: */
	void _findWordBase();									// Поиск слова в базе данных.
	void _findWordInBase(const std::string & query) const;	// Запрос на поиск слова в базе данных.
	bool _findPartInWord(const Word & word, const std::string & part) const;	// Поиск посклова в слове
	bool _findPartInWord(const std::string & inWord, const std::string & part) const; // Основный алгоритм
	void _sortedWordsBase();								// Сортировка слов в базе данных.
	void _sortedWordsBaseEngl();							
	void _sortedWordsBaseRus();								
	void _sortedWordsBaseType();														
	void _deleteWord() const;								// Удаление слова из базы данных.	
private:
	 /* Взаимодейстиве программы с файлов базы данных: */
	void _setNameFileBase(const std::string & nameFile);	// Установка назание файла базы данных.
	bool _loadFileBase();									// Загрузка слов из фала базы данных.
	bool _saveLocalBaseInFile();							// Сохранение данных в файл.
	bool _deleteWordInFileBase();							// Удаление слова из фала базы данных.	
	bool _openFileBase(ModeFile mode);						// Открытие файла базы данных.
	void _closeFileBase();									// Закрытие файла базы данных.
	bool _addWordinFile(Word & word);						// Добавление слова в базу данных файла.
private:
	std::string		m_nameFile;								// Назание фала базы данных.
	std::fstream	m_filebase;								// Поток взаимодействия с файлом базы данных.
	tBase			m_base;									// База слов.
};

