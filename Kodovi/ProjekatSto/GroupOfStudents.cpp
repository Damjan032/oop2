//============================================================================
// File Name   : GroupOfStudents.cpp
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : C++ group project
//============================================================================

//  Your code starts here


#include "GroupOfStudents.h"
#include <iomanip>
#include <fstream>
#include "Menu.h"

void GroupOfStudents::display() const
{
	for (StudentCourses sc : st_vec)
		sc.display();
}

void GroupOfStudents::display_sorted() const
{
	cout << '|' << left << setw(10) << "ID" << '|' << setw(11)
		<< "Ime" << '|' << setw(30) << "Prezime" << '|' << setw(7) << "Bodova"
		<< '|' << setw(6) << "Ocena" << '|' << endl;
	vector<StudentCourses> vec = st_vec;
	merge_sort(vec, SortType::STUDENT_NAME);
	for (StudentCourses sc : vec)
		sc.display();
}

void GroupOfStudents::display_highest() const
{
	cout << '|' << left << setw(10) << "ID" << '|' << setw(11)
		<< "Ime" << '|' << setw(30) << "Prezime" << '|' << setw(7) << "Bodova"
		<< '|' << setw(6) << "Ocena" << '|' << endl;
	vector<StudentCourses> vec = st_vec;
	merge_sort(vec, SortType::GRADE);
	if (vec.size() > 3)
		vec.resize(3);
	for (StudentCourses sc : vec)
		sc.display();
}

void GroupOfStudents::write_to_file(const string & output) const
{
	vector<StudentCourses> vec = st_vec;
	merge_sort(vec, SortType::ID);
	ofstream ofs(output);
	for (StudentCourses sc : vec)
		ofs << sc << endl;
	ofs.close();
}
void GroupOfStudents::binary_write_to_file(const string & output) const
{
	char razmak = ' ', novi_red = '\n';
	char* p1 = &razmak, *p2 = &novi_red;
	string sid, f_name, l_name;
	double f_score;
	char l_grade;
	vector<StudentCourses> vec = st_vec;

	merge_sort(vec, SortType::ID);
	ofstream ofs(output, ios_base::binary);

	for (StudentCourses sc : vec) {
		sid = sc.get_student().get_id();
		//postavljanje promenljivih za bolje snalazenje
		f_name = sc.get_student().get_first_name();
		l_name = sc.get_student().get_last_name();
		f_score = sc.get_courses().get_final_score();
		l_grade = sc.get_courses().get_letter_grade();

		//upis
		ofs.write(sid.c_str(), sid.size());							// upisuje id studenta
		ofs.write(p1, sizeof(char));								// p1 pokazuje na razmak

		ofs.write(f_name.c_str(), f_name.size());					// upisuje ime
		ofs.write(p1, sizeof(char));

		ofs.write(l_name.c_str(), l_name.size());					// upisuje prezime
		ofs.write(p1, sizeof(char));								

		ofs.write((char*)&f_score, sizeof(double));					// upisuje final score
		ofs.write(p1, sizeof(char));

		ofs.write((char*)&l_grade, sizeof(char));					// upisuje slovnu ocenu
		ofs.write(p2, sizeof(char));
	}

	ofs.close();
}
void GroupOfStudents::convert_to_bin(const string & output) const
{
	char razmak = ' ', novi_red = '\n';
	char* p1 = &razmak, *p2 = &novi_red;
	string sid, f_name, l_name;
	vector<StudentCourses> vec = st_vec;

	merge_sort(vec, SortType::ID);
	ofstream ofs(output, ios_base::binary);

	for (StudentCourses sc : vec) {
		sid = sc.get_student().get_id();
		//postavljanje promenljivih za bolje snalazenje
		f_name = sc.get_student().get_first_name();
		l_name = sc.get_student().get_last_name();

		//upis
		ofs.write(sid.c_str(), sid.size());							// upisuje id studenta
		ofs.write(p1, sizeof(char));								// p1 pokazuje na razmak

		ofs.write(f_name.c_str(), f_name.size());					// upisuje ime
		ofs.write(p1, sizeof(char));

		ofs.write(l_name.c_str(), l_name.size());					// upisuje prezime
		ofs.write(p2, sizeof(char));								// p2 pokazuje na novi red

		for (int i : sc.get_courses().get_homework()) {
			ofs.write((char*)&i, sizeof(int));					// upisuje hw
			ofs.write(p1, sizeof(char));
		}
		ofs.write(p2, sizeof(char));								// p2 pokazuje na novi red
		for (int i : sc.get_courses().get_quiz()) {
			ofs.write((char*)&i, sizeof(int));					// upisuje kvizove
			ofs.write(p1, sizeof(char));
		}
		ofs.write(p2, sizeof(char));								// p2 pokazuje na novi red
		for (int i : sc.get_courses().get_test()) {
			ofs.write((char*)&i, sizeof(int));					// upisuje kvizove
			ofs.write(p1, sizeof(char));
		}
		ofs.write(p2, sizeof(char));
	}

	ofs.close();
}

void GroupOfStudents::binary_read_from_file(const string & input)
{
	int k = 0;
	char novi_red = '\n', current;
	ifstream ifs(input, ios_base::binary);
	ifs.exceptions(ios_base::badbit | ios_base::failbit);
	if (!ifs)
		throw Menu::InvalidFile();
	while (true) {
		++k;
		Student s = Student::read_student_binary(ifs);
		Courses c = Courses::read_from_binary_file(ifs);
		ifs.read(&current, sizeof(char));
		if (current != novi_red)
			throw Menu::InvalidData();
		StudentCourses sc(s, c);
		st_vec.push_back(sc);
		if (ifs.peek() == -1)
			break;
	}

}


const vector<StudentCourses>& GroupOfStudents::get_student_courses() const
{
	return st_vec;
}


istream & operator>> (istream & in, GroupOfStudents & gs)
{
	StudentCourses sc;
	while (!in.eof()) {
		in >> sc;
		gs.add_student_courses(sc);
	}
	return in;
}


void merge_sort(vector<StudentCourses>& vec, GroupOfStudents::SortType st)
{

	int len = vec.size(), mid = len / 2, len2 = len - mid;

	if (len <= 1)
		return;
	vector<StudentCourses> left;
	vector<StudentCourses> right;

	for (int j = 0; j < mid; j++)
		left.push_back(vec[j]);

	for (int j = 0; j < len2; j++)
		right.push_back(vec[mid + j]);

	merge_sort(left, st);
	merge_sort(right, st);
	if (st == GroupOfStudents::SortType::STUDENT_NAME)
		mergeStudent(vec, left, right);
	else if (st == GroupOfStudents::SortType::ID)
		mergeID(vec, left, right);
	else
		mergeGrade(vec, left, right);
}

void mergeStudent(vector<StudentCourses>& vec, vector<StudentCourses>& left, vector<StudentCourses>& right) {
	int left_size = left.size(), right_size = right.size();
	int i = 0, j = 0, k = 0, comp = 0;

	while (j < left_size && k < right_size) {
		comp = left[j].get_student().compare(right[i].get_student());
		if (comp < 0) {
			vec[i] = left[j];
			++j;
		}
		else {
			vec[i] = right[k];
			++k;
		}
		++i;
	}
	while (j < left_size) {
		vec[i] = left[j];
		++i; ++j;
	}
	while (k < right_size) {
		vec[i] = right[k];
		++i; ++k;
	}
}

void mergeGrade(vector<StudentCourses>& vec, vector<StudentCourses>& left, vector<StudentCourses>& right)
{
	int left_size = left.size(), right_size = right.size();
	int i = 0, j = 0, k = 0, comp = 0;

	while (j < left_size && k < right_size && i < 4) {
		double left_grade = left[j].get_courses().get_final_score();
		double right_grade = right[k].get_courses().get_final_score();
		if (left_grade > right_grade) {
			vec[i] = left[j];
			++j;
		}
		else {
			vec[i] = right[k];
			++k;
		}
		++i;
	}
	while (j < left_size) {
		vec[i] = left[j];
		++i; ++j;
	}
	while (k < right_size) {
		vec[i] = right[k];
		++i; ++k;
	}
}
void mergeID(vector<StudentCourses>& vec, vector<StudentCourses>& left, vector<StudentCourses>& right)
{
	int left_size = left.size(), right_size = right.size();
	int i = 0, j = 0, k = 0, comp = 0;

	while (j < left_size && k < right_size && i < 4) {
		int comp = left[j].get_student().get_id().compare(right[k].get_student().get_id());
		if (comp < 0) {

			vec[i] = left[j];
			++j;
		}
		else {
			vec[i] = right[k];
			++k;
		}
		++i;
	}
	while (j < left_size) {
		vec[i] = left[j];
		++i; ++j;
	}
	while (k < right_size) {
		vec[i] = right[k];
		++i; ++k;
	}
}