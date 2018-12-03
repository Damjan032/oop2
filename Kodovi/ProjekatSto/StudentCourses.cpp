//============================================================================
// File Name   : StudentCourses.cpp
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : Class in which student and courses are combined, so
//				 student can be connected with course he attended.
//				 The functions implemented here are:
//				 - operator>> which sets student and courses to value that
//				   was acquired from istream in
// Last changed: Gegic Haris 26.11.2018.
//============================================================================

// Your code starts here


#include "StudentCourses.h"
#include <iomanip>

void StudentCourses::display()
{
	// format ovog ispisa: |-----------|------------|--------------| samo vise
	student.display();
	courses.display();
	cout << endl;
}

istream & operator >> (istream & in, StudentCourses & sc)
{
	Student student;
	Courses courses;

	in >> student >> courses;

	sc.set_student(student);
	sc.set_courses(courses);
	return in;
}

ostream & operator<<(ostream & out, StudentCourses & sc)
{
	out << sc.student << sc.courses;
	return out;
}

