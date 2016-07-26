#include "stdafx.h"
#include "Programm.h"
#include <set>

bool partition_findPartInWord(const char * wordIn, std::size_t pos, const char * part, std::size_t sizePart); // Функция для нахождения части в слове

Programm::Programm()
{

}

void Programm::Menu()
{
	const std::size_t SIZE_SELECT = 4;
	const std::string description_cmd[SIZE_SELECT] = { "Начать тестирование", "Посмотр базы слов", "Добавить слово", "Выход из программы" };
	const std::string commands[SIZE_SELECT] =	{ "start", "show", "add", "exit" };
	const std::string commands_alternative[SIZE_SELECT] = { "1", "2", "3", "4" };
	const std::string preview("----Programm: English Tester v 1.0");

	system("cls");
	std::cout << preview << std::endl << std::endl;;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Команда \t\t\t Название команды" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	for (std::size_t i = 0; i < SIZE_SELECT; ++i)
		std::cout << i + 1 << ") " << description_cmd[i] << "\t\t (" << commands[i] << ")" << std::endl;
	std::cout << std::endl;

	std::string choose;
	std::cout << ">> Сделать выбор: ";
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
			std::cout << ">> Ошибка ввода, повторите ввод: ";
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
			std::cout << ">> Повторить попытку (yes?)" << std::endl;
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
	std::cout << "----Добавление слова в базу данных----" << std::endl << std::endl;
	std::string wordEngl;
	std::string wordRus;
	std::string type;
	Word::Type type_;

	while (true){
		std::string choose;
		std::cout << std::endl;
		std::cout << "Введите английскую версию слова: ";
		std::cin >> wordEngl;
		std::cout << "Введите русскую версию слова: ";
		std::cin >> wordRus;
		std::cout << "Тип слова: существительное - n, глагол - v, прилагательное - a, другое - o: ";
		std::cin >> type;
		if (type != "n" && type != "v" && type != "a" && type != "o"){
			std::cout << ">> Ошибка выбора, повторите попытку" << std::endl;
			std::cout << "Тип слова: существительное - n, глагол - v, прилагательное - a, другое - o: ";
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
		std::cout << "Английская версия: " << wordEngl << std::endl;
		std::cout << "Русская версия: " << wordRus << std::endl;
		std::cout << "Тип: ";
		if (type == "n")
			std::cout << "Существительное" << std::endl;
		else if (type == "v")
			std::cout << "Глагол" << std::endl;
		else if (type == "a")
			std::cout << "Прилагательное" << std::endl;
		else
			std::cout << "Другое" << std::endl;

		std::cout << ">> Добавить слово (yes) ?" << std::endl;
		std::cout << ">> ";
		std::cin >> choose;
		if (choose == "yes"){
			std::cout << ">> Слово будет добавленно в базу даных..." << std::endl;
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
			std::cout << ">> Продолжить добавление слов? (yes):" << std::endl;
			std::cout << ">> ";
			std::cin >> choose;
			if (choose != "yes")
				Programm::Menu();	// В случае если исключение не возникло, функция завершает работу, выходя  в главное меню.
			else
				continue;
		}
		else{
			std::cout << ">> Повторный ввод..." << std::endl;
		}
	}
}

void Programm::showBaseWords()
{
	system("cls");
	std::cout << "----Просмотр базы данных----" << std::endl;
	std::cout << ">> Количество данных в базе данных: " << m_base.size() << std::endl;
	std::cout << std::endl;

	const std::size_t COUNT_COMMANDS = 6;
	const std::string description_cmd[COUNT_COMMANDS] = { "Рандомизация слов в базе" , "Просмотр всей базы      ", "Просмотр русских слов", "Просмотр английских слов", "Поиск                      ", "Выход в меню           " };
	const std::string commands[COUNT_COMMANDS] = { "rand", "full", "rus", "engl", "find", "exit" };
	const std::string commands_alternative[COUNT_COMMANDS] = { "1", "2", "3", "4", "5", "6" };

	std::cout << "Навание команды \t\t Команда" << std::endl << std::endl;
	for (std::size_t i = 0; i < COUNT_COMMANDS; ++i){
		std::cout << i + 1 << ") " << description_cmd[i] << "\t(" << commands[i] << ")" << std::endl;
	}
	std::cout << std::endl;

	while (true){
		std::string choose;		// Манипулятор.
		std::size_t size = 0;	// Количество отображаемых данных в базе данных.
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
				std::cout << ">> Введите количество отображаемых данных: ";
				std::cin >> size;
				if (size != 0 && size <= m_base.size())
					Programm::_showBaseRusWords(size);
				else
					std::cout << ">> Значнение неккорретно, повторите ввод..." << std::endl;
			}
		}
		else if (choose == commands[3] || choose == commands_alternative[3]){
			while (true){
				std::cout << ">> Введите количество отображаемых данных: ";
				std::cin >> size;
				if (size != 0 && size <= m_base.size())
					Programm::_showBaseEnglWords(size);
				else
					std::cout << ">> Значнение неккорретно, повторите ввод..." << std::endl;
			}
		}
		else if (choose == commands[4] || choose == commands_alternative[4]){
			Programm::_findWordBase();
		}
		else if (choose == commands[5] || choose == commands_alternative[5]){
			Programm::Menu();
		}
		else
			std::cout << ">> Неккоректное значение, повторите ввод..." << std::endl;
	}
	_gettch();
	Programm::Menu();
}

void Programm::_showFullBase()
{
	system("cls");
	std::cout << "----Вывод всей базы данных----" << std::endl;
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
	std::cout << "----Вывод русских вариантов слов----" << std::endl;
	std::cout << std::endl;
	for (std::size_t i = 0; i < size; ++i)
		std::cout << i + 1 << ") " << m_base[i].wordRus() << std::endl;
	_gettch();
	Programm::showBaseWords();
}

void Programm::_showBaseEnglWords(std::size_t size)
{
	system("cls");
	std::cout << "----Вывод английских вариантов слов----" << std::endl;
	std::cout << std::endl;
	for (std::size_t i = 0; i < size; ++i)
		std::cout << i + 1 << ") " << m_base[i].wordEngl() << std::endl;
	_gettch();
	Programm::showBaseWords();
}

void Programm::_findWordBase()
{
	system("cls");
	std::cout << "----Поиск в базе данных----" << std::endl;
	std::cout << std::endl;

	std::string choose;		// Манимулятор
	std::string query;		// Запрос в базу данных
	while (true){
		std::cout << ">> Введите запрос: ";
		std::cin >> query;
		try{
			Programm::_findWordInBase(query);
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << ">> Повторить поиск? (yes)" << std::endl;
			std::cout << ">> ";
			std::cin >> choose;
			if (choose == "yes")
				continue;
			else
				Programm::Menu();
		}
		catch (const excepted::bad_base_find & exc){
			std::cout << ">> Данных по запросу \"" << query << "\" не найдено в базе данных, повторить? (yes)" << std::endl;
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
	std::size_t countRes = 0;				// Количество результатов по поиску
	for (std::size_t i = 0; i < size; ++i){
		bool good = Programm::_findPartInWord(m_base[i], query);
		if (good){
			std::cout << countRes + 1 << ")" << m_base[i] << std::endl;
			++countRes;
		}	
	}
	if (countRes == 0){
		std::string message(">> Поиск не удался");
		throw excepted::bad_base_find(message);
	}
}

bool Programm::_findPartInWord(const Word & word, const std::string & part) const
{
	std::string inWordEngl = word.wordEngl();
	std::string	inWordRus = word.wordRus();
	bool flagSearchEngl = Programm::_findPartInWord(inWordEngl, part);	// Поиск в английском варианте
	bool flagSearchRus = Programm::_findPartInWord(inWordRus, part);	// Поиск в русском варианте	
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

		Word * wordOne = &m_base[indexOne];			// Выбор первого элемента для перестоновки
		Word * wordTwo = &m_base[indexTwo];		// Выбор второго элемента для перестоновки
		std::swap(*wordOne, *wordTwo);
	}
	std::cout << ">> Рандомизация была произведeна" << std::endl;
}

void Programm::testing()
{
	system("cls");
	std::cout << "----Тестирование----" << std::endl;
	std::cout << ">> Количество данных в базе данных: " << m_base.size() << std::endl;
	std::cout << std::endl;
	
	const std::size_t SIZE_COMMANDS = 3;
	const std::string description_cmd[SIZE_COMMANDS] = { "Тестирование:[Say me a answer] на входе английская или русская версия слова, требуется ответить противоположную", "Тестирование:[Write me a answer] на входе английская или русская версия слова, требуется ввести противоположную", "Выход в меню" };
	const std::string commands_alternative[SIZE_COMMANDS] = { "1", "2", "3" };

	for (std::size_t i = 0; i < SIZE_COMMANDS; ++i)
		std::cout << commands_alternative[i] << ") " << description_cmd[i] << std::endl;
	std::cout << std::endl;

	if (m_base.size() == 0){
		std::cout << ">> База данных пуста, для выхода в меню нажмите любую кнопку." << std::endl;
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
			std::cout << ">> Ошибка выбора, повторите ввод" << std::endl;
			continue;
		}
	}
}

void Programm::_testingWordAnswer()
{
	std::srand(time(0));
	system("cls");
	std::cout << "----Тестирование:[Say me a answer]----" << std::endl;
	std::cout << ">> Количество слов в базе данных: " << m_base.size() << std::endl;
	std::cout << std::endl;

	// Результат теста
	class ResultTest
	{
	public:
		ResultTest(int badWord, int goodWord) : m_countBadWord(badWord), m_countGoodWord(goodWord) {};
		void showResult() const
		{
			std::cout << std::endl;
			std::cout << "----Тест окончен----" << std::endl;
			std::cout << "Количество правильных ответов: " << m_countGoodWord << std::endl;
			std::cout << "Количество неправильных ответов: " << m_countBadWord << std::endl;
			std::cout << std::endl;
		}
	private:
		int m_countBadWord;
		int m_countGoodWord;
	};

	enum Type{ rus, engl };
	std::string	choose;						// Манипулятор
	Type		typeInWord;					// Тип слова, на входе при тестировании
	int			count_word = 0;				// Количество слов в тесте
	
	std::cout << ">> Версия слова на входе: русская / английская? " << std::endl;
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
			std::cout << ">> Ошибка ввода" << std::endl;
			continue;
		}
	}

	std::cout << ">> Задать количество слов теста? (yes)" << std::endl;
	std::cout << ">> ";
	std::cin >> choose;

	if (choose == "yes"){
		while (true){
			int size;
			std::cout << ">> Введите число: ";
			std::cin >> size;
			if (size > 1 && size <= m_base.size()){
				count_word = size;
				break;
			}
			else{
				std::cout << ">> Неккоретное значение..." << std::endl;
				continue;
			}
		}
	}
	else
		count_word = m_base.size();

	// Тест
	int				count_goodWord = 0;			// Количество слов, отвечанных правильно
	int				count_badWord = 0;			// Количество слов, отчечанных неправильно
	std::set<int>	tempChooseIndex;			// set, хранящий индексы слов, которые уже были выбораны в тесте. // Повторно слова редлагаться не будут
	int				randIndex;					// Выбор рандомного индекса, для получения рандомного слова

	for (std::size_t i = 0; i < count_word; ++i)
	{
		while (true){										// Выбор индекса рандомного
			randIndex = std::rand() % m_base.size();
			if (tempChooseIndex.find(randIndex) == tempChooseIndex.end()){
				tempChooseIndex.insert(randIndex);
				break;
			}
			else
				continue;
		}
		std::cout << std::endl;
		std::cout << ">> Подтверждение - 1 | Отказ - 2 | Выход - q " << std::endl;
		std::cout << "Вопрос №" << i + 1 << ": ";
		std::cout << (typeInWord == Type::engl ? "English: " : "Russian: ") << (typeInWord == Type::engl ? m_base[randIndex].wordEngl() : m_base[randIndex].wordRus()) << std::endl;
		while (true){
			std::cout << "Знаешь ответ?: ";
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
				std::cout << ">> Ошибка выбора, повторите попытку" << std::endl;
		}
		std::cout << "Ответ: " << (typeInWord == Type::engl ? m_base[randIndex].wordRus() : m_base[randIndex].wordEngl()) << std::endl;
	}
	
	ResultTest result(count_badWord, count_goodWord);
	result.showResult();
	_gettch();
	Programm::Menu();
}

void Programm::ExitPogramm()
{
	std::string choose;
	std::cout << ">> Завершение программы..." << std::endl;
	std::cout << ">> Сохранить данные в файл \"" << m_nameFile << "\" ? (yes)" << std::endl;
	std::cin >> choose;
	try
	{
		if (choose == "yes")
			Programm::_saveLocalBaseInFile();
		std::cout << ">> Данные сохранены в файл" << std::endl;
	}
	catch (const excepted::bad_file & exc)
	{
		exc.message();
		std::cout << "Данные не были сохранены в файл" << std::endl;
	}
	system("pause");
	exit(0);
}

void Programm::setNameFileBase()
{
	std::string DEFAULT_FILE_NAME("base.bin");
	std::string nameFile;
	std::cout << ">> Выбрать файл базы данных по умалчанию \"base.bin\" (yes) ?: " << std::endl;
	std::cout << ">> ";
	std::string choose;
	std::cin >> choose;
	if (choose == "yes"){
		Programm::_setNameFileBase(DEFAULT_FILE_NAME);
		return;
	}
	std::cout << ">> Введите назание фала базы данных" << std::endl;
	while(true){
		std::cout << ">> Название файла: ";
		std::cin >> nameFile;
		std::cout << ">> Выбранный файл \"" << nameFile << "\" ? (yes / no)" << std::endl;
		std::string select;
		std::cin >> select;
		if (select == "yes"){
			std::cout << std::endl;
			std::cout << ">> Выбран файл \"" << nameFile << "\"" << std::endl;
			Programm::_setNameFileBase(nameFile);
			return;
		}
		else if (select == "no"){
			std::cout << ">> Ввод будет повторен.." << std::endl;
		}
		else{
			std::cout << ">> Ошибка ввода, ввод будет повторен..." << std::endl;
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
		std::string message(">> Ошибка открытия файла");
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
	int pos = m_filebase.tellg();			// Текущая позиция, фиксированная при чтении файла
	m_filebase.seekg(0, std::ios::end);
	int posEnd = m_filebase.tellg();		// Конечная позиция файла
	m_filebase.seekg(0, std::ios::beg);

	if (pos == posEnd){
		std::cout << ">> Файл Пуст" << std::endl;
		_gettch();
		Programm::_closeFileBase();
		return true;
	}
	while (m_filebase.good()){
		Word word;
		m_filebase.read(reinterpret_cast<char *>(&word), sizeof(word));
		if (!m_filebase.fail()){		// Если ввод успешен - добавляем в локальную базу данных 
			m_base.push_back(word);
		}
		pos = m_filebase.tellp();
	}
	Programm::_closeFileBase();
	//if (pos != posEnd){
	//	std::string message(">> Ошибка чтения данных из файла");
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
		std::string message("Ошибка открытия файла");
		throw excepted::bad_file_save(message);
	}
	std::size_t size = m_base.size();
	for (std::size_t i = 0; i < size; ++i)
		m_filebase.write(reinterpret_cast<char *>(&m_base[i]), sizeof(Word));
	m_filebase.close();
	return true;
}