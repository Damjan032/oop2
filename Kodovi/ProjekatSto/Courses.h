//============================================================================
// File Name   : Courses.h
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : This file represents a place where the class Courses is declared
//============================================================================

#ifndef COURSES_H_
#define COURSES_H_


#include <iostream>
#include <vector>

using namespace std;

class Courses
{
public:
	static const int NUM_QUIZZES = 10;
	static const int NUM_HW = 6;
	static const int NUM_TESTS = 4;

private:
	// private data
	vector<int> quiz;
	vector<int> homework;
	vector<int> test;
	double final_score;
	char letter_grade;

public:
	// constructors
	Courses (): quiz(NUM_QUIZZES), homework(NUM_HW), test(NUM_TESTS) {}
	Courses(const vector<int>& q, const vector<int>& h, const vector<int>& t)
		: quiz(q), homework(h), test(t), final_score(0), letter_grade('F') {}
	friend istream& operator >> (istream& in, Courses &courses);
	friend ostream& operator<< (ostream& out, Courses &courses);
	const vector<int> & get_homework() const { return homework; };
	const vector<int> & get_quiz() const { return quiz; };
	const vector<int> & get_test() const { return test; };

	void set_quiz(const vector<int> &q) { quiz = q; };
	void set_homework(const vector<int> &hw) { homework = hw; };
	void set_test(const vector<int> &t) { test = t; };
	double get_final_score() const;
	char get_letter_grade() const { return letter_grade; };
	void display() const;
	void calc_final_score();
	void calc_letter_grade();
	static Courses read_from_binary_file(istream& in);
};
static bool check_len(istream& in, int& i, const int& possible_len);


#endif 
