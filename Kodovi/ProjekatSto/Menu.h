//============================================================================
// File Name   : Menu.h
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : Zaglavlje za meni. Funkcije su implementirane
//				 u fajlu Menu.cpp.
//============================================================================



#include <string>
#include <stdexcept>
#include "GroupOfStudents.h"

using std::string;

class Menu
{
public:
	struct InvalidData : std::runtime_error {
		InvalidData(): runtime_error("Invalid input data format") {}
	};

	struct InvalidFile : std::runtime_error {
		InvalidFile(): runtime_error("Invalid input file name") {}
	};

	enum OPTIONS{INFO=1, READ_FILE, DISPLAY,  HIGHEST, DISPLAY_SORTED, ALL_STUDENTS, WRITE_FILE, EXIT};
	Menu();
	static bool loaded;
	void display_menu() const;
	void display_info() const;
	void read_students(string &input, string &file_type, string &output);
	void display_student() const;
	void display_students() const;
	void display_students_sorted() const;
	void display_highest_score() const;
	void write_students(string &file_type, string &output) const;
private:
	GroupOfStudents gs;	
};
