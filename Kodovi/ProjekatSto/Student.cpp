//============================================================================
// File Name   : Student.cpp
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : C++ group project
//============================================================================




#include "Student.h"
#include "Menu.h"
#include <iomanip>
void Student::display() const
{
	cout << '|' << left << setw(10) << s_id << '|' << setw(11) << first_name << '|' << setw(30)
		<< last_name << '|';
}

int Student::compare(const Student & st)
{
	int name_comp = last_name.compare(st.get_last_name());
	if (name_comp != 0)
		return name_comp;
	name_comp = first_name.compare(st.get_first_name());
	if (name_comp != 0)
		return name_comp;
	name_comp = s_id.compare(st.get_id());
	return name_comp;
}

Student Student::read_student_binary(istream & in)
{
	string sid = "", f_name = "", l_name = "";
	char razmak = ' ', current_char = 'a';
	while (!in.eof()) { // ucitava id
		in.read(&current_char, sizeof(char));
		if (current_char == razmak)
			break;
		sid += current_char;
	}
	if (in.eof())
		throw Menu::InvalidData();
	while (!in.eof()) { // ucitava ime
		in.read(&current_char, sizeof(char));
		if (current_char == razmak)
			break;
		f_name += current_char;
	}
	if (in.eof())
		throw Menu::InvalidData();
	while (!in.eof()) { // ucitava prezime
		in.read(&current_char, sizeof(char));
		if (current_char == '\n')
			break;
		l_name += current_char;
	}
	if (in.eof())
		throw Menu::InvalidData();
	return Student(f_name, l_name, sid);
}

istream & operator >> (istream & in, Student &student)
{
	string f_name, l_name, id;
	in >> f_name >> l_name >> id;
	if (!check_names(f_name) || !check_names(l_name))
		throw Menu::InvalidData();
	student.set_first_name(f_name);
	student.set_last_name(l_name);
	student.set_s_id(id);
	return in;
}

ostream & operator<<(ostream & out, Student & student)
{
	out << student.s_id << ' ' << student.first_name << ' ' << student.last_name << ' ';
	return out;
}


static bool check_names(const string &name) {
	for (char c : name) {
		if (isdigit(c))
			return false;
	}
	return true;
}
