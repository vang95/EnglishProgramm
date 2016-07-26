#include "stdafx.h"
#include "Programm.h"
#include <set>

bool partition_findPartInWord(const char * wordIn, std::size_t pos, const char * part, std::size_t sizePart); // ������� ��� ���������� ����� � �����

Programm::Programm()
{

}

void Programm::Menu()
{
	const std::size_t SIZE_SELECT = 4;
	const std::string description_cmd[SIZE_SELECT] = { "������ ������������", "������� ���� ����", "�������� �����", "����� �� ���������" };
	const std::string commands[SIZE_SELECT] =	{ "start", "show", "add", "exit" };
	const std::string commands_alternative[SIZE_SELECT] = { "1", "2", "3", "4" };
	const std::string preview("----Programm: English Tester v 1.0");

	system("cls");
	std::cout << preview << std::endl << std::endl;;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "������� \t\t\t �������� �������" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	for (std::size_t i = 0; i < SIZE_SELECT; ++i)
		std::cout << i + 1 << ") " << description_cmd[i] << "\t\t (" << commands[i] << ")" << std::endl;
	std::cout << std::endl;

	std::string choose;
	std::cout << ">> ������� �����: ";
	std::cin >> choose;
	while (true){
		if (choose == commands[0] || choose == commands_alternative[0]){
			Programm::testing();
		}
		else if (choose == commands[1] || choose == commands_alternative[1]){
			Programm::showBaseWords();
		}
		else if (choose == commands[2] || choose == commands_alternative[2]){
			Programm::addWord();
		}
		else if (choose == commands[3] || choose == commands_alternative[3]){
			Programm::ExitPogramm();
		}
		else{
			std::cout << ">> ������ �����, ��������� ����: ";
			std::cin >> choose;
		}
	}
}

void Programm::StartProgramm()
{
	bool flagLoadInfo = false;
	std::string select;
	while (!flagLoadInfo){
		try
		{
			Programm::setNameFileBase();
			Programm::_openFileBase(ModeFile::In);
			Programm::_loadFileBase();
		}
		catch (const excepted::bad_file & exc){
			exc.message();
			std::cout << ">> ��������� ������� (yes?)" << std::endl;
			std::cout << ">> ";
			std::cin >> select;
			if (select == "yes")
				continue;
			else
				break;
		}
		flagLoadInfo = true;
	}
	if (!flagLoadInfo)
		Programm::ExitPogramm();
	else
		Programm::Menu();
}

void Programm::addWord()
{
	system("cls");
	std::cout << "----���������� ����� � ���� ������----" << std::endl << std::endl;
	std::string wordEngl;
	std::string wordRus;
	std::string type;
	Word::Type type_;

	while (true){
		std::string choose;
		std::cout << std::endl;
		std::cout << "������� ���������� ������ �����: ";
		std::cin >> wordEngl;
		std::cout << "������� ������� ������ �����: ";
		std::cin >> wordRus;
		std::cout << "��� �����: ��������������� - n, ������ - v, �������������� - a, ������ - o: ";
		std::cin >> type;
		if (type != "n" && type != "v" && type != "a" && type != "o"){
			std::cout << ">> ������ ������, ��������� �������" << std::endl;
			std::cout << "��� �����: ��������������� - n, ������ - v, �������������� - a, ������ - o: ";
			std::cin >> type;
		}
		if (type == "n")
			type_ = Word::Type::nuon;
		else if (type == "v")
			type_ = Word::Type::verb;
		else if (type == "a")
			type_ = Word::Type::adjective;
		else if (type == "o")
			type_ = Word::Type::other;

		std::cout << std::endl;
		std::cout << "���������� ������: " << wordEngl << std::endl;
		std::cout << "������� ������: " << wordRus << std::endl;
		std::cout << "���: ";
		if (type == "n")
			std::cout << "���������������" << std::endl;
		else if (type == "v")
			std::cout << "������" << std::endl;
		else if (type == "a")
			std::cout << "��������������" << std::endl;
		else
			std::cout << "������" << std::endl;

		std::cout << ">> �������� ����� (yes) ?" << std::endl;
		std::cout << ">> ";
		std::cin >> choose;
		if (choose == "yes"){
			std::cout << ">> ����� ����� ���������� � ���� �����..." << std::endl;
			Word word(wordEngl.c_str(), wordRus.c_str(), type_);
			try{
				Programm::_addWordinFile(word);
			}
			catch (const excepted::bad_file & exc){
				exc.message();
				_gettch();
				Programm::ExitPogramm();
			}
			m_base.push_back(word);
			std::cout << ">> ���������� ���������� ����? (yes):" << std::endl;
			std::cout << ">> ";
			std::cin >> choose;
			if (choose != "yes")
				Programm::Menu();	// � ������ ���� ���������� �� ��������, ������� ��������� ������, ������  � ������� ����.
			else
				continue;
		}
		else{
			std::cout << ">> ��������� ����..." << std::endl;
		}
	}
}

void Programm::showBaseWords()
{
	system("cls");
	std::cout << "----�������� ���� ������----" << std::endl;
	std::cout << ">> ���������� ������ � ���� ������: " << m_base.size() << std::endl;
	std::cout << std::endl;

	const std::size_t COUNT_COMMANDS = 6;
	const std::string description_cmd[COUNT_COMMANDS] = { "������������ ���� � ����" , "�������� ���� ����      ", "�������� ������� ����", "�������� ���������� ����", "�����                      ", "����� � ����           " };
	const std::string commands[COUNT_COMMANDS] = { "rand", "full", "rus", "engl", "find", "exit" };
	const std::string commands_alternative[COUNT_COMMANDS] = { "1", "2", "3", "4", "5", "6" };

	std::cout << "������� ������� \t\t �������" << std::endl << std::endl;
	for (std::size_t i = 0; i < COUNT_COMMANDS; ++i){
		std::cout << i + 1 << ") " << description_cmd[i] << "\t(" << commands[i] << ")" << std::endl;
	}
	std::cout << std::endl;

	while (true){
		std::string choose;		// �����������.
		std::size_t size = 0;	// ���������� ������������ ������ � ���� ������.
		std::cout << ">> ";		
		std::cin >> choose;
		if (choose == commands[0] || choose == commands_alternative[0]){
			Programm::_randomlyWords();
		}
		else if (choose == commands[1] || choose == commands_alternative[1]){
			Programm::_showFullBase();
		}
		else if (choose == commands[2] || choose == commands_alternative[2]){
			while (true){
				std::cout << ">> ������� ���������� ������������ ������: ";
				std::cin >> size;
				if (size != 0 && size <= m_base.size())
					Programm::_showBaseRusWords(size);
				else
					std::cout << ">> ��������� �����������, ��������� ����..." << std::endl;
			}
		}
		else if (choose == commands[3] || choose == commands_alternative[3]){
			while (true){
				std::cout << ">> ������� ���������� ������������ ������: ";
				std::cin >> size;
				if (size != 0 && size <= m_base.size())
					Programm::_showBaseEnglWords(size);
				else
					std::cout << ">> ��������� �����������, ��������� ����..." << std::endl;
			}
		}
		else if (choose == commands[4] || choose == commands_alternative[4]){
			Programm::_findWordBase();
		}
		else if (choose == commands[5] || choose == commands_alternative[5]){
			Programm::Menu();
		}
		else
			std::cout << ">> ������������ ��������, ��������� ����..." << std::endl;
	}
	_gettch();
	Programm::Menu();
}

void Programm::_showFullBase()
{
	system("cls");
	std::cout << "----����� ���� ���� ������----" << std::endl;
	std::cout << std::endl;
	for (std::size_t i = 0; i < m_base.size(); ++i){
		std::cout << i + 1 << ") " << m_base[i] << std::endl;
	}
	_gettch();
	Programm::showBaseWords();
}

void Programm::_showBaseRusWords(std::size_t size)
{
	system("cls");
	std::cout << "----����� ������� ��������� ����----" << std::endl;
	std::cout << std::endl;
	for (std::size_t i = 0; i < size; ++i)
		std::cout << i + 1 << ") " << m_base[i].wordRus() << std::endl;
	_gettch();
	Programm::showBaseWords();
}

void Programm::_showBaseEnglWords(std::size_t size)
{
	system("cls");
	std::cout << "----����� ���������� ��������� ����----" << std::endl;
	std::cout << std::endl;
	for (std::size_t i = 0; i < size; ++i)
		std::cout << i + 1 << ") " << m_base[i].wordEngl() << std::endl;
	_gettch();
	Programm::showBaseWords();
}

void Programm::_findWordBase()
{
	system("cls");
	std::cout << "----����� � ���� ������----" << std::endl;
	std::cout << std::endl;

	std::string choose;		// �����������
	std::string query;		// ������ � ���� ������
	while (true){
		std::cout << ">> ������� ������: ";
		std::cin >> query;
		try{
			Programm::_findWordInBase(query);
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << ">> ��������� �����? (yes)" << std::endl;
			std::cout << ">> ";
			std::cin >> choose;
			if (choose == "yes")
				continue;
			else
				Programm::Menu();
		}
		catch (const excepted::bad_base_find & exc){
			std::cout << ">> ������ �� ������� \"" << query << "\" �� ������� � ���� ������, ���������? (yes)" << std::endl;
			std::cout << ">> ";
			std::cin >> choose;
			if (choose == "yes")
				continue;
			else
				Programm::Menu();
		}
	}
}

void Programm::_findWordInBase(const std::string & query) const
{
	std::size_t size = m_base.size();
	std::size_t countRes = 0;				// ���������� ����������� �� ������
	for (std::size_t i = 0; i < size; ++i){
		bool good = Programm::_findPartInWord(m_base[i], query);
		if (good){
			std::cout << countRes + 1 << ")" << m_base[i] << std::endl;
			++countRes;
		}	
	}
	if (countRes == 0){
		std::string message(">> ����� �� ������");
		throw excepted::bad_base_find(message);
	}
}

bool Programm::_findPartInWord(const Word & word, const std::string & part) const
{
	std::string inWordEngl = word.wordEngl();
	std::string	inWordRus = word.wordRus();
	bool flagSearchEngl = Programm::_findPartInWord(inWordEngl, part);	// ����� � ���������� ��������
	bool flagSearchRus = Programm::_findPartInWord(inWordRus, part);	// ����� � ������� ��������	
	return flagSearchEngl || flagSearchRus;
}

bool Programm::_findPartInWord(const std::string & inWord, const std::string & part) const
{
	bool flag = false;
	const std::size_t sizePart = part.size();
	const std::size_t sizeInWord = inWord.size();
	if (sizePart > sizeInWord)
		return false;
	char * buffer = new char[sizeInWord];
	for (std::size_t i = 0; i < sizeInWord - sizePart + 1; ++i)
	{
		flag = partition_findPartInWord(inWord.c_str(), i, part.c_str(), sizePart);
		if (flag)
			break;
	}
	delete[] buffer;
	return flag;
}

bool partition_findPartInWord(const char * wordIn, std::size_t pos, const char * part, std::size_t sizePart)
{
	for (std::size_t i = pos, j = 0; j < sizePart; ++i, ++j){
		if (wordIn[i] != part[j])
			return false;
	}
	return true;
}

void Programm::_randomlyWords()
{
	std::srand(time(0));
	std::size_t size = m_base.size();
	for (std::size_t i = 0; i < size; ++i){
		std::size_t indexOne = std::rand() % size;
		std::size_t indexTwo = std::rand() % size;

		Word * wordOne = &m_base[indexOne];			// ����� ������� �������� ��� ������������
		Word * wordTwo = &m_base[indexTwo];		// ����� ������� �������� ��� ������������
		std::swap(*wordOne, *wordTwo);
	}
	std::cout << ">> ������������ ���� ��������e��" << std::endl;
}

void Programm::testing()
{
	system("cls");
	std::cout << "----������������----" << std::endl;
	std::cout << ">> ���������� ������ � ���� ������: " << m_base.size() << std::endl;
	std::cout << std::endl;
	
	const std::size_t SIZE_COMMANDS = 3;
	const std::string description_cmd[SIZE_COMMANDS] = { "������������:[Say me a answer] �� ����� ���������� ��� ������� ������ �����, ��������� �������� ���������������", "������������:[Write me a answer] �� ����� ���������� ��� ������� ������ �����, ��������� ������ ���������������", "����� � ����" };
	const std::string commands_alternative[SIZE_COMMANDS] = { "1", "2", "3" };

	for (std::size_t i = 0; i < SIZE_COMMANDS; ++i)
		std::cout << commands_alternative[i] << ") " << description_cmd[i] << std::endl;
	std::cout << std::endl;

	if (m_base.size() == 0){
		std::cout << ">> ���� ������ �����, ��� ������ � ���� ������� ����� ������." << std::endl;
		_gettch();
		Programm::Menu();
	}

	while (true){
		std::string choose;
		std::cout << ">> ";
		std::cin >> choose;

		if (choose == commands_alternative[0]){
			Programm::_testingWordAnswer();
		}
		else if (choose == commands_alternative[1]){
			
		}
		else if (choose == commands_alternative[2]){
			Programm::Menu();
		}
		else{
			std::cout << ">> ������ ������, ��������� ����" << std::endl;
			continue;
		}
	}
}

void Programm::_testingWordAnswer()
{
	std::srand(time(0));
	system("cls");
	std::cout << "----������������:[Say me a answer]----" << std::endl;
	std::cout << ">> ���������� ���� � ���� ������: " << m_base.size() << std::endl;
	std::cout << std::endl;

	// ��������� �����
	class ResultTest
	{
	public:
		ResultTest(int badWord, int goodWord) : m_countBadWord(badWord), m_countGoodWord(goodWord) {};
		void showResult() const
		{
			std::cout << std::endl;
			std::cout << "----���� �������----" << std::endl;
			std::cout << "���������� ���������� �������: " << m_countGoodWord << std::endl;
			std::cout << "���������� ������������ �������: " << m_countBadWord << std::endl;
			std::cout << std::endl;
		}
	private:
		int m_countBadWord;
		int m_countGoodWord;
	};

	enum Type{ rus, engl };
	std::string	choose;						// �����������
	Type		typeInWord;					// ��� �����, �� ����� ��� ������������
	int			count_word = 0;				// ���������� ���� � �����
	
	std::cout << ">> ������ ����� �� �����: ������� / ����������? " << std::endl;
	while (true){
		std::cout << ">> r / e: ";
		std::cin >> choose;
		if (choose == "r"){
			typeInWord = Type::rus;
			break;
		}
		else if (choose == "e"){
			typeInWord = Type::engl;
			break;
		}
		else{
			std::cout << ">> ������ �����" << std::endl;
			continue;
		}
	}

	std::cout << ">> ������ ���������� ���� �����? (yes)" << std::endl;
	std::cout << ">> ";
	std::cin >> choose;

	if (choose == "yes"){
		while (true){
			int size;
			std::cout << ">> ������� �����: ";
			std::cin >> size;
			if (size > 1 && size <= m_base.size()){
				count_word = size;
				break;
			}
			else{
				std::cout << ">> ����������� ��������..." << std::endl;
				continue;
			}
		}
	}
	else
		count_word = m_base.size();

	// ����
	int				count_goodWord = 0;			// ���������� ����, ���������� ���������
	int				count_badWord = 0;			// ���������� ����, ���������� �����������
	std::set<int>	tempChooseIndex;			// set, �������� ������� ����, ������� ��� ���� �������� � �����. // �������� ����� ����������� �� �����
	int				randIndex;					// ����� ���������� �������, ��� ��������� ���������� �����

	for (std::size_t i = 0; i < count_word; ++i)
	{
		while (true){										// ����� ������� ����������
			randIndex = std::rand() % m_base.size();
			if (tempChooseIndex.find(randIndex) == tempChooseIndex.end()){
				tempChooseIndex.insert(randIndex);
				break;
			}
			else
				continue;
		}
		std::cout << std::endl;
		std::cout << ">> ������������� - 1 | ����� - 2 | ����� - q " << std::endl;
		std::cout << "������ �" << i + 1 << ": ";
		std::cout << (typeInWord == Type::engl ? "English: " : "Russian: ") << (typeInWord == Type::engl ? m_base[randIndex].wordEngl() : m_base[randIndex].wordRus()) << std::endl;
		while (true){
			std::cout << "������ �����?: ";
			std::cin >> choose;
			if (choose == "1"){
				++count_goodWord;
				break;
			}
			else if (choose == "2"){
				++count_badWord;
				break;
			}
			else if (choose == "q"){
				ResultTest	result(count_badWord, count_goodWord);
				result.showResult();
				_gettch();
				Programm::Menu();
			}
			else
				std::cout << ">> ������ ������, ��������� �������" << std::endl;
		}
		std::cout << "�����: " << (typeInWord == Type::engl ? m_base[randIndex].wordRus() : m_base[randIndex].wordEngl()) << std::endl;
	}
	
	ResultTest result(count_badWord, count_goodWord);
	result.showResult();
	_gettch();
	Programm::Menu();
}

void Programm::ExitPogramm()
{
	std::string choose;
	std::cout << ">> ���������� ���������..." << std::endl;
	std::cout << ">> ��������� ������ � ���� \"" << m_nameFile << "\" ? (yes)" << std::endl;
	std::cin >> choose;
	try
	{
		if (choose == "yes")
			Programm::_saveLocalBaseInFile();
		std::cout << ">> ������ ��������� � ����" << std::endl;
	}
	catch (const excepted::bad_file & exc)
	{
		exc.message();
		std::cout << "������ �� ���� ��������� � ����" << std::endl;
	}
	system("pause");
	exit(0);
}

void Programm::setNameFileBase()
{
	std::string DEFAULT_FILE_NAME("base.bin");
	std::string nameFile;
	std::cout << ">> ������� ���� ���� ������ �� ��������� \"base.bin\" (yes) ?: " << std::endl;
	std::cout << ">> ";
	std::string choose;
	std::cin >> choose;
	if (choose == "yes"){
		Programm::_setNameFileBase(DEFAULT_FILE_NAME);
		return;
	}
	std::cout << ">> ������� ������� ���� ���� ������" << std::endl;
	while(true){
		std::cout << ">> �������� �����: ";
		std::cin >> nameFile;
		std::cout << ">> ��������� ���� \"" << nameFile << "\" ? (yes / no)" << std::endl;
		std::string select;
		std::cin >> select;
		if (select == "yes"){
			std::cout << std::endl;
			std::cout << ">> ������ ���� \"" << nameFile << "\"" << std::endl;
			Programm::_setNameFileBase(nameFile);
			return;
		}
		else if (select == "no"){
			std::cout << ">> ���� ����� ��������.." << std::endl;
		}
		else{
			std::cout << ">> ������ �����, ���� ����� ��������..." << std::endl;
		}
	}
}

void Programm::_setNameFileBase(const std::string & nameFile)
{
	m_nameFile = nameFile;
}

bool Programm::_openFileBase(ModeFile mode)
{
	m_filebase.open(m_nameFile.c_str(), (mode == In ? std::ios::in : std::ios::out) | (mode == In ? std::ios::ate : std::ios::app) | std::ios::binary);
	if (!m_filebase.is_open()){
		std::string message(">> ������ �������� �����");
		throw excepted::bad_file_open(message);
	}
	return true;
}

void Programm::_closeFileBase()
{
	m_filebase.close();
}

bool Programm::_loadFileBase()
{
	m_base.clear();
	m_filebase.seekg(0, std::ios::beg);
	int pos = m_filebase.tellg();			// ������� �������, ������������� ��� ������ �����
	m_filebase.seekg(0, std::ios::end);
	int posEnd = m_filebase.tellg();		// �������� ������� �����
	m_filebase.seekg(0, std::ios::beg);

	if (pos == posEnd){
		std::cout << ">> ���� ����" << std::endl;
		_gettch();
		Programm::_closeFileBase();
		return true;
	}
	while (m_filebase.good()){
		Word word;
		m_filebase.read(reinterpret_cast<char *>(&word), sizeof(word));
		if (!m_filebase.fail()){		// ���� ���� ������� - ��������� � ��������� ���� ������ 
			m_base.push_back(word);
		}
		pos = m_filebase.tellp();
	}
	Programm::_closeFileBase();
	//if (pos != posEnd){
	//	std::string message(">> ������ ������ ������ �� �����");
	//	throw excepted::bad_file_read(message);
	//}
	return true;
}

bool Programm::_addWordinFile(Word & word)
{
	try{
		Programm::_openFileBase(ModeFile::Out);
	}
	catch (const excepted::bad_file & exc){
		exc.message();
		_gettch();
		Programm::ExitPogramm();
	}
	m_filebase.write(reinterpret_cast<char *>(&word), sizeof(Word));
	Programm::_closeFileBase();
	return true;
}

bool Programm::_saveLocalBaseInFile()
{
	m_filebase.open(m_nameFile, std::ios::out | std::ios::binary);
	if (!m_filebase.is_open()){
		std::string message("������ �������� �����");
		throw excepted::bad_file_save(message);
	}
	std::size_t size = m_base.size();
	for (std::size_t i = 0; i < size; ++i)
		m_filebase.write(reinterpret_cast<char *>(&m_base[i]), sizeof(Word));
	m_filebase.close();
	return true;
}