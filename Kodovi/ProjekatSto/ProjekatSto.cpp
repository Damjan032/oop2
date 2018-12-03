//============================================================================
// File Name   : ProjekatSto.cpp 
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : C++ group project
//============================================================================


#include <iostream>
#include "Menu.h"


using namespace std;

bool validate_arguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	// za argumente koji se ucitavaju kroz komandnu liniju
	if (!validate_arguments(argc, argv)) return 1;
	string input = argv[1];
	string type = argv[2];
	string output = input;
	if (argc == 4 && argv[3] != input) output = argv[3];
	else output.insert(output.size() - 4, "_out");
	Menu m;
	int option;
	m.display_menu();

	do
	{
		cout << "> ";
		while (!(cin >> option) || option < 1 || option > Menu::EXIT)
		{
			if (cin.fail())	// we found something that wasn’t an integer
			{
				cin.clear();	// we’d like to look at the characters
				char ch;
				while (cin >> ch && !isdigit(ch))
				{
					cerr << "Nevalidan unos. Pokusajte ponovo." << endl;
					cout << "> ";
				}
				cin.unget();
			}
			else
			{	// option < 1 || option > Menu::EXIT */
				cerr << "Nevalidan unos. Pokusajte ponovo." << endl;
				cout << "> ";
			}
		}

		switch (option)
		{
		case Menu::INFO:
			m.display_info();
			break;
		case Menu::READ_FILE:
			try
			{
				m.read_students(input, type, output);
			}
			catch (const Menu::InvalidFile& excp)
			{
				cerr << excp.what() << endl;
				return 1;
			}
			catch (const Menu::InvalidData& excp)
			{
				cerr << excp.what() << endl;
				return 1;
			}
			break;
		case Menu::DISPLAY:
			m.display_student();
			break;
		case Menu::DISPLAY_SORTED:
			m.display_students_sorted();
			break;
		case Menu::HIGHEST:
			m.display_highest_score();
			break;
		case Menu::ALL_STUDENTS:
			m.display_students();
			break;
		case Menu::WRITE_FILE:
			m.write_students(type, output);
			break;
		}
		m.display_menu();
	} while (option != Menu::EXIT);
	return 0;
}

bool validate_arguments(int argc, char * argv[])
{
	if (argc < 3 || argc > 4) {
		cout << "Broj ulaznih parametara nije validan" << endl;
		cout << "Neophodno je unijeti dva dodatna argumenta" << endl;
		cout << "Treci je opcioni argument." << endl;
		cout << "Argumenti: putanja do ulazne datoteke, tip datoteke i\nputanja izlazne datoteke." << endl;
		cout << "Primer:\n\t/ime_programa arg1 arg2\n\t/ime_programa arg1 arg2 arg3\n";

		return false;
	}
	return true;
}
