//============================================================================
// File Name   : GroupOfStudents.h
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : C++ group project
//============================================================================


#ifndef GROUPOFSTUDENTS_H_
#define GROUPOFSTUDENTS_H_


#include <vector>
#include <iostream>
#include "StudentCourses.h"

using namespace std;

class GroupOfStudents
{
private:
	vector<StudentCourses> st_vec;
public:
	enum SortType{ STUDENT_NAME, GRADE, ID };
	GroupOfStudents() {}
	GroupOfStudents(vector< StudentCourses >& v) : st_vec(v) {};
	friend istream& operator>> (istream& in, GroupOfStudents& gs);

	void add_student_courses(StudentCourses sc) { st_vec.push_back(sc); };
	void display() const;
	void display_sorted() const;
	void display_highest() const;
	void write_to_file(const string& output) const;
	void binary_write_to_file(const string& output) const;
	void convert_to_bin(const string& output) const;

	void binary_read_from_file(const string& input);
	const vector<StudentCourses>& get_student_courses() const;
};
void merge_sort(vector<StudentCourses>& vec, GroupOfStudents::SortType st);
void mergeStudent(vector<StudentCourses>& vec, vector<StudentCourses>& left, vector<StudentCourses>& right);
void mergeGrade(vector<StudentCourses>& vec, vector<StudentCourses>& left, vector<StudentCourses>& right);
void mergeID(vector<StudentCourses>& vec, vector<StudentCourses>& left, vector<StudentCourses>& right);


#endif /*GROUPOFSTUDENTS_H_*/
