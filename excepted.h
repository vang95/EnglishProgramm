#pragma once

#include <iostream>
#include <string>

// Классы исключений, характеризующие ошибки
namespace excepted
{
	// Исключение, связанное с файлом
	class bad_file 
	{
	public:
		bad_file(const std::string & message) : m_message(message) {}
		virtual ~bad_file() {}
		virtual std::string message() const; // Сообщение об ошибки
	private:
		std::string m_message;	// Сообщение, характеризующее описание ошибки
	};

	inline std::string bad_file::message() const
	{
		std::cout << m_message << std::endl;
		return m_message;
	}

	// Исключение открытия файла
	class bad_file_open : public bad_file
	{
	public:
		bad_file_open(const std::string & message) : bad_file(message) {}
	};

	// Исключение записи в файл
	class bad_file_write : public bad_file
	{
	public:
		bad_file_write(const std::string & message) : bad_file(message) {}
	};

	// Исключение чтения файла
	class bad_file_read : public bad_file
	{
	public:
		bad_file_read(const std::string & message) : bad_file(message) {}
	};
	
	// Исключение записи в файл
	class bad_file_rite : public bad_file
	{
	public:
		bad_file_rite(const std::string & message) : bad_file(message) {}
	};

	// Исключение сохранения базы в файл
	class bad_file_save : public bad_file
	{
	public:
		bad_file_save(const std::string & message) : bad_file(message) {}
	};

	// Исключение, связанное с работай локальной базы данных
	class bad_base
	{
	public:
		bad_base(const std::string & message) : m_message(message) {}
		virtual ~bad_base() {}
		virtual std::string message() const; // Сообщение об ошибки
	private:
		std::string m_message;	// Сообщение, характеризующее описание ошибки
	};

	inline std::string bad_base::message() const
	{
		std::cout << m_message << std::endl;
		return m_message;
	}

	// Исключение неудавшегося поиск
	class bad_base_find : public bad_base
	{
	public:
		bad_base_find(const std::string & message) : bad_base(message) {}
	};
}
