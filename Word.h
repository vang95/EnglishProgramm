#pragma once

#include <iostream>

const std::size_t SIZE_LEN = 50;

class Word
{
public:
	enum Type{ nuon, verb, adjective, other };			// ���: ���., ������, ��������������, ������
public:
	Word(const char * word_engl = "no_info", const char * word_rus = "no_info", Type type = Word::Type::other);
	Word(const Word & word);
public:
	void setWordEngl(const char * word);	// ������ ���������� ������� �����.
	void setWordRus(const char * word);		// ������ ������� ������� �����.
	void setType(Type type);				// ������ ��� �����.
	const char * wordEngl() const;			// ������� ����������� �������� �����.
	const char * wordRus() const;			// ������� �������� �������� �����.
	Type type() const;						// ������� ���� �����.
	Word & operator = (const Word & word);								// �������� ������������
	friend std::ostream & operator << (std::ostream & os, const Word & word); // ����� � �����
private:
	Type	m_type;							// ��� �����.
	char	m_word_engl[SIZE_LEN];			// ���������� ������� �����.			
	char	m_word_rus[SIZE_LEN];			// ������� ������� �����.
};


