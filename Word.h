#pragma once

#include <iostream>

const std::size_t SIZE_LEN = 50;

class Word
{
public:
	enum Type{ nuon, verb, adjective, other };			// Тип: сущ., глагол, прилагательное, другое
public:
	Word(const char * word_engl = "no_info", const char * word_rus = "no_info", Type type = Word::Type::other);
	Word(const Word & word);
public:
	void setWordEngl(const char * word);	// Задать аеглийский вариант слова.
	void setWordRus(const char * word);		// Задать русский вариант слова.
	void setType(Type type);				// Задать тип слова.
	const char * wordEngl() const;			// Возврат английского варианта слова.
	const char * wordRus() const;			// Возврат русского варианта слова.
	Type type() const;						// Возврат типа слова.
	Word & operator = (const Word & word);								// оператор присваивания
	friend std::ostream & operator << (std::ostream & os, const Word & word); // Вывод в поток
private:
	Type	m_type;							// Тип слова.
	char	m_word_engl[SIZE_LEN];			// Английский вариант слова.			
	char	m_word_rus[SIZE_LEN];			// Русский вариант слова.
};


