#include "stdafx.h"
#include "Word.h"
#include <cstring>


Word::Word(const char * word_engl, const char * word_rus,Type type)
{
	Word::setWordEngl(word_engl);
	Word::setWordRus(word_rus);
	Word::setType(type);
}

Word::Word(const Word & word)
{
	Word::setWordEngl(word.wordEngl());
	Word::setWordRus(word.wordRus());
	Word::setType(word.type());
}

void Word::setWordEngl(const char * word)
{
	strcpy_s(m_word_engl, word);
}

void Word::setWordRus(const char * word)
{
	strcpy_s(m_word_rus, word);
}

void Word::setType(Word::Type type)
{
	m_type = type;
}

const char * Word::wordEngl() const
{
	return m_word_engl;
}

const char * Word::wordRus() const
{
	return m_word_rus;
}

Word::Type Word::type() const
{
	return m_type;
}

Word & Word::operator = (const Word & word)
{
	if (this == &word)
		return *this;
	Word::setWordEngl(word.wordEngl());
	Word::setWordRus(word.wordRus());
	Word::setType(word.type());
	return *this;
}