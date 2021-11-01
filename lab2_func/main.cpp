#include <Windows.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <limits>

using namespace std;

// Кодирование
string TextToBinaryString(string words)
{
	string output = "";
	try
	{
		for (char& _char : words)
			// Передаем символ, представляя его в бинарной записи
			// и конвертируем в string
			output += bitset<8>(_char).to_string();
	}
	catch (...)
	{

	}
	return output;
}
// Декодирование
string BinaryToTextString(string data)
{
	std::stringstream sstream(data);
	std::string output;
	try
	{
		// Проверка потока на ошибку/конец
		while (sstream.good())
		{
			std::bitset<8> bits; // Создали контейнер на 8 битов
			sstream >> bits; // Заполнили контейнер
			// Получили код символа и преобразовали в символ
			output += char(bits.to_ulong());
		}
	}
	catch (...)
	{

	}
	return output;
}

// Закодировать и записать в файл
void EncodeAndWriteToFile(string data)
{
	try
	{
		ofstream out;
		out.open("file.binary");
		if (out.is_open())
			out << TextToBinaryString(data);
		out.close();
	}
	catch (...)
	{

	}
}

// Прочитать и декодировать файл
string ReadAndDecodeFile(string name)
{
	string result = "";
	std::string line;
	try
	{
		std::ifstream in(name);
		if (in.is_open())
			while (getline(in, line))
				result += line;
		in.close();
	}
	catch (...)
	{

	}
	return BinaryToTextString(result);
}

// Записать в файл
void WriteToFile(string filename, string data)
{
	try
	{
		ofstream out;
		out.open(filename);
		if (out.is_open())
			out << data;
		out.close();
	}
	catch (...)
	{

	}
}

// Прочитать файл
string ReadFile(string name)
{
	string result = "";
	std::string line;
	try
	{
		std::ifstream in(name);
		if (in.is_open())
			while (getline(in, line))
				result += line;
		in.close();
	}
	catch (...)
	{

	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int choice = 0;
	while (true)
	{
		cout << "1. Прочитать файл и закодировать" << endl;
		cout << "2. Прочитать файл и декодировать" << endl;
		cout << "3. Завершить работу" << endl;
		cout << "Выбор: "; cin >> choice;

		switch (choice)
		{
		case 1: // Прочитать файл и закодировать
		{
			system("cls");
			string filename = "";
			cout << "Введите имя файла для чтения (например, file.txt): ";
			cin >> filename;
			if (filename != "")
			{
				system("cls");
				cout << "Считанный файл (" + filename + "):" << endl << endl << ReadFile(filename);
				EncodeAndWriteToFile(ReadFile(filename));
				cout << endl << endl << "Закодировано (file.binary):" << endl;
				cout << endl << ReadFile("file.binary") << endl << endl;
				system("pause");
				system("cls");
			}
			break;
		}
		case 2: // Прочитать файл и декодировать
		{
			system("cls");
			string filename = "";
			cout << "Введите имя файла для чтения (например, file.binary): ";
			cin >> filename;
			if (filename != "")
			{
				system("cls");
				cout << "Считанный файл (" + filename + "):" << endl << endl << ReadFile(filename);
				cout << endl << endl << "Декодировано (" + filename + "):" << endl;
				cout << endl << ReadAndDecodeFile(filename) << endl << endl;
				WriteToFile("SaveDecode.txt", ReadAndDecodeFile(filename));
				system("pause");
				system("cls");
			}
			break;
		}
		case 3: // Завершить работу
		{
			return 0;
		}
		default:
		{
			system("cls");
			cout << "Выбор неверный. Повторите ввод." << endl;
			system("pause");
			system("cls");
			choice = 0;
			if (char(cin.peek()) == '\n')
				cin.ignore();

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
			}
			break;
		}
		}
	}
	system("pause");
	return 0;
}