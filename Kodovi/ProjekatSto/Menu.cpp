//============================================================================
// File Name   : Menu.cpp
// Authors     : You
// Version     : 1.4
// Copyright   : Your copyright notice (if applicable)
// Description : Implementation of functions from Menu.h;
//				 Currently, functions implemented are:
//				 - display_menu(), which displays menu when called;
//				 - display_info(), which displays information about authors
//				   of the project in a very well designed and copied ascii art form;
// Last change : Gegic Haris 26.11.2018.
//============================================================================


#include <iostream>
#include "Menu.h"
#include <iomanip>
#include <fstream>
#include "GroupOfStudents.h"
using namespace std;

bool Menu::loaded = false;

Menu::Menu()
{
}

void Menu::display_menu() const {
	system("CLS");
	cout << setfill('.') << left << setw(50) << "| ----\tOPCIJE:" << '|' << endl;
	cout << left << setw(50) << "| 1 - \tPRIKAZ OSNOVNIH INFORMACIJA O AUTORIMA" << '|' << endl;
	cout << left << setw(50) << "| 2 - \tUCITAVANJE STUDENATA IZ DATOTEKE" << '|' << endl;
	cout << left << setw(50) << "| 3 - \tPRIKAZ INFORMACIJA O STUDENTU" << '|' << endl;
	cout << left << setw(50) << "| 4 - \tPRIKAZ STUDENATA SA NAJBOLJIM PROSJEKOM" << '|' << endl;
	cout << left << setw(50) << "| 5 - \tSORTIRANJE STUDENATA" << '|' << endl;
	cout << left << setw(50) << "| 6 - \tPRIKAZ INFORMACIJA O SVIM STUDENTIMA" << '|' << endl;
	cout << left << setw(50) << "| 7 - \tUPIS STUDENATA U IZLAZNU DATOTEKU" << '|' << endl;
	cout << left << setw(50) << "| 8 - \tIZLAZ IZ PROGRAMA" << '|' << endl;
}

void Menu::display_info() const
{
	system("CLS");
	cin.ignore();
	cout << 
"             ____________________________________________________\n" <<
"            /                                                    \\\n" <<
"           |    _____________________________________________     |\n" <<
"           |   |                                             |    |\n" <<
"           |   |  AUTORI OVOGA PROJEKTA SU:                  |    |\n" <<
"           |   |  - SW20/2017 MANOJLOVIC DAMJAN              |    |\n" <<
"           |   |  - SW70/2017 GEGIC HARIS                    |    |\n" <<
"           |   |  - SW??/2017 JEVTIC NEMANJA	              |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |  - Pritisnite enter za povratak...          |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |                                             |    |\n" <<
"           |   |_____________________________________________|    |\n" <<
"           |                                                      |\n" <<
"            \\_____________________________________________________/\n" <<
"                   \\_______________________________________/		\n" <<
"                _______________________________________________	\n" <<
"             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_	\n" <<
"          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_\n" <<
"       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_\n" <<
"    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_\n" <<
" _-'.-.-.-.-.-. .---.-. .-----------------------------. .-.---. .---.-.-.-.`-_\n" <<
":-----------------------------------------------------------------------------:\n" <<
"`---._.-----------------------------------------------------------------._.---'\n";
	cin.get();
}

void Menu::read_students(string &input, string &type, string &output)
{
	if (loaded) {
		cout << "\tPodaci su vec ucitani u sistem\n\tPritisnite enter za povratak...\n";
		cin.ignore();
		cin.get();
		return;
	}
	if (type == "txt") {
		ifstream ifs(input);
		if (!ifs) { throw InvalidFile(); };
		ifs.exceptions(ifstream::badbit);
		ifs >> gs;
		ifs.close();
	} else {
		gs.binary_read_from_file(input);
	}
	cout << "\tUspesno ucitano!\n\tPritisnite enter za povratak..." << endl;
	cin.ignore();
	cin.get();
	loaded = true;
	
}

void Menu::display_student() const
{
	system("CLS");
	if (!loaded) {
		cout << "\tPodaci jos uvijek nisu ucitani. Pretraga je onemogucena.\n";
		cout << "\tPritisnite enter za povratak...\n";
		cin.ignore();
		cin.get();
		return;
	}
	bool is_chosen = false;
	string id;

	system("CLS");
	cout << "\tUNESITE IDENTIFIKACIONI BROJ STUDENTA:\n> ";
	cin >> id;
	StudentCourses chosen;
	vector<StudentCourses> scvec = gs.get_student_courses();
	for (StudentCourses stc : scvec) {
		string currid = stc.get_student().get_id();
		if (currid == id) {
			chosen = stc;
			is_chosen = true;
			break;
		}
	}
	if (!is_chosen) {
		cerr << "\tNe postoji student sa ovim identifikacionim brojem.\n";
		cin.ignore();
		cin.get();
		return;
	}
	cout << '|' << left << setw(10) << "ID" << '|' << setw(11)
		<< "Ime" << '|' << setw(30) << "Prezime" << '|' << setw(7) << "Bodova"
		<< '|' << setw(6) << "Ocena" << '|' << endl;
	chosen.display();
	cout << "\tPritisnite enter za povratak..." << endl;
	cin.ignore();
	cin.get();

}

void Menu::display_students() const
{
	if (!loaded) {
		cout << "\tPodaci jos uvijek nisu ucitani. Prikaz je onemogucen.\n";
		cout << "\tPritisnite enter za povratak...\n";
		cin.ignore();
		cin.get();
		return;
	}
	system("CLS");
	gs.display();
	cin.ignore();
	cin.get();
}

void Menu::display_students_sorted() const
{
	if (!loaded) {
		cout << "\tPodaci jos uvijek nisu ucitani. Prikaz je onemogucen.\n";
		cout << "\tPritisnite enter za povratak...\n";
		cin.ignore();
		cin.get();
		return;
	}
	system("CLS");
	gs.display_sorted();
	cin.ignore();
	cin.get();
}

void Menu::display_highest_score() const
{
	if (!loaded) {
		cout << "\tPodaci jos uvijek nisu ucitani. Prikaz je onemogucen.\n";
		cout << "\tPritisnite enter za povratak...\n";
		cin.ignore();
		cin.get();
		return;
	}
	system("CLS");
	gs.display_highest();
	cin.ignore();
	cin.get();
}

void Menu::write_students(string &file_type, string &output) const
{
	if (!loaded) {
		cout << "\tPodaci jos uvijek nisu ucitani. Upis je onemogucen.\n";
		cout << "\tPritisnite enter za povratak...\n";
		cin.ignore();
		cin.get();
		return;
	}
	if (file_type == "txt")
		gs.write_to_file(output);
	else {
		gs.binary_write_to_file(output.insert(output.size() - 4, "_bin"));
		gs.write_to_file(output);
		//ovo donje je kad konvertujem u binarnu. sluzi da bih napravio binarnu iz koje mogu da uctavam poslije
		//gs.convert_to_bin(output.insert(output.size() - 4, "_binconverted"));
	}
	
	cout << "\tUpis uspesan.\n\tPritisnite enter za povratak..." << endl;
	cin.ignore();
	cin.get();
}
