//============================================================================
// File Name   : Student.h
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : C++ group project
//============================================================================


#ifndef STUDENT_H_
#define STUDENT_H_


#include <string>
#include <iostream>

using namespace std;
class Student
{
private:
	string first_name;
	string last_name;
	string s_id;

public:
	// add required constructors
	Student() {};
	Student(string fn, string ln, string sid) :
		first_name(fn), last_name(ln), s_id(sid) {};
	string get_first_name() const { return first_name; };
	string get_last_name() const { return last_name; };
	string get_id() const { return s_id; };
	void set_first_name(const string& f_name) { first_name = f_name; };
	void set_last_name(const string& l_name) { last_name = l_name; };
	void set_s_id(const string& sid) { s_id = sid; };
	void display() const;
	friend istream& operator >> (istream& in, Student &student);
	friend ostream& operator<< (ostream& out, Student& student);

	int compare(const Student& st);
	static Student read_student_binary(istream& in);
};

static bool check_names(const string &name);
#endif /*STUDENT_H_*/
