#include <Windows.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <limits>

using namespace std;

// �����������
string TextToBinaryString(string words)
{
	string output = "";
	try
	{
		for (char& _char : words)
			// �������� ������, ����������� ��� � �������� ������
			// � ������������ � string
			output += bitset<8>(_char).to_string();
	}
	catch (...)
	{

	}
	return output;
}
// �������������
string BinaryToTextString(string data)
{
	std::stringstream sstream(data);
	std::string output;
	try
	{
		// �������� ������ �� ������/�����
		while (sstream.good())
		{
			std::bitset<8> bits; // ������� ��������� �� 8 �����
			sstream >> bits; // ��������� ���������
			// �������� ��� ������� � ������������� � ������
			output += char(bits.to_ulong());
		}
	}
	catch (...)
	{

	}
	return output;
}

// ������������ � �������� � ����
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

// ��������� � ������������ ����
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

// �������� � ����
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

// ��������� ����
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
		cout << "1. ��������� ���� � ������������" << endl;
		cout << "2. ��������� ���� � ������������" << endl;
		cout << "3. ��������� ������" << endl;
		cout << "�����: "; cin >> choice;

		switch (choice)
		{
		case 1: // ��������� ���� � ������������
		{
			system("cls");
			string filename = "";
			cout << "������� ��� ����� ��� ������ (��������, file.txt): ";
			cin >> filename;
			if (filename != "")
			{
				system("cls");
				cout << "��������� ���� (" + filename + "):" << endl << endl << ReadFile(filename);
				EncodeAndWriteToFile(ReadFile(filename));
				cout << endl << endl << "������������ (file.binary):" << endl;
				cout << endl << ReadFile("file.binary") << endl << endl;
				system("pause");
				system("cls");
			}
			break;
		}
		case 2: // ��������� ���� � ������������
		{
			system("cls");
			string filename = "";
			cout << "������� ��� ����� ��� ������ (��������, file.binary): ";
			cin >> filename;
			if (filename != "")
			{
				system("cls");
				cout << "��������� ���� (" + filename + "):" << endl << endl << ReadFile(filename);
				cout << endl << endl << "������������ (" + filename + "):" << endl;
				cout << endl << ReadAndDecodeFile(filename) << endl << endl;
				WriteToFile("SaveDecode.txt", ReadAndDecodeFile(filename));
				system("pause");
				system("cls");
			}
			break;
		}
		case 3: // ��������� ������
		{
			return 0;
		}
		default:
		{
			system("cls");
			cout << "����� ��������. ��������� ����." << endl;
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