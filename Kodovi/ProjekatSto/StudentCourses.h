//============================================================================
// File Name   : StudentCourses.h
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : Class in which students and their courses are combined so
//				 student can be connected with course he attended.
// Last changed: Gegic Haris 26.11.2018.
//============================================================================


#ifndef _STUDENTCOURSES_H_
#define _STUDENTCOURSES_H_

#include "Student.h"
#include "Courses.h"
#include <iostream>
using namespace std;

class StudentCourses
{
	Student student;
	Courses courses;
public:
	StudentCourses() {};
	const StudentCourses(Student s, Courses c) : student(s), courses(c) {};
	friend istream& operator >> (istream& in, StudentCourses &sc);
	friend ostream& operator << (ostream& out, StudentCourses &sc);

	Student get_student() const { return student; }
	const Courses& get_courses() const { return courses; }
	void set_student(const Student& stud) { student = stud; };
	void set_courses(const Courses& cour) { courses = cour; };
	double get_final_score() { return courses.get_final_score(); };
	void display();
};
#endif
