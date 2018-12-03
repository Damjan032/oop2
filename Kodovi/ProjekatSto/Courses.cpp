//============================================================================
// File Name   : Courses.cpp
// Authors     : You
// Version     : 1.0
// Copyright   : Your copyright notice (if applicable)
// Description : Some of the functions implemented here are:
//				 -operator>> which is responsible for loading data in objects
// Last changed: Gegic Haris 27.11.2018.
//============================================================================

//  Your code starts here


#include "Courses.h"
#include <iomanip>
#include "Menu.h"

static const double QUIZ_WEIGHT = 0.05;
static const double HOMEWORK_WEIGHT = 0.5;
static const double TEST_WEIGHT = 0.45;

double Courses::get_final_score() const
{
	return final_score;
}

void Courses::display() const
{
	cout << setw(7) << final_score << '|' << setw(6) << letter_grade << '|';

}

void Courses::calc_final_score()
{
	int sumHomework = 0;
	int sumTest = 0;
	int sumQuiz = 0;

	for (int i : homework) {
		sumHomework += i;
	}
	for (int i : test) {
		sumTest += i;
	}
	for (int i : quiz) {
		sumQuiz += i;
	}
	final_score = sumQuiz*(QUIZ_WEIGHT / NUM_QUIZZES) + sumHomework*(HOMEWORK_WEIGHT / NUM_HW) + sumTest*(TEST_WEIGHT / NUM_TESTS);

}

void Courses::calc_letter_grade()
{
	double round_final = ceil(final_score);
	if (round_final >= 90 && round_final <= 100) {
		letter_grade = 'A';
	}
	else if (round_final >= 80 && round_final <= 89) {
		letter_grade = 'B';
	}
	else if (round_final >= 70 && round_final <= 79) {
		letter_grade = 'C';
	}
	else if (round_final >= 60 && round_final <= 69) {
		letter_grade = 'D';
	}
	else {
		letter_grade = 'F';
	}
}

Courses Courses::read_from_binary_file(istream & in)
{
	char razmak = ' ', current_char = 'a';
	int current;
	vector<int> quizzes;
	vector<int> tests;
	vector<int> hworks;
	while (!in.eof()) {
		in.read((char *)&current, sizeof(int));
		hworks.push_back(current);
		in.read(&current_char, sizeof(char));
		if (in.peek() == '\n')
			break;
		if (current_char != razmak)
			throw Menu::InvalidData();

	}
	in.read(&current_char, sizeof(char));

	while (!in.eof()) {
		in.read((char *)&current, sizeof(int));
		quizzes.push_back(current);
		in.read(&current_char, sizeof(char));
		if (in.peek() == '\n')
			break;
		if (current_char != razmak)
			throw Menu::InvalidData();

	}
	in.read(&current_char, sizeof(char));
	while (!in.eof()) {
		in.read((char *)&current, sizeof(int));
		tests.push_back(current);
		in.read(&current_char, sizeof(char));
		if (in.peek() == '\n')
			break;
		if (current_char != razmak)
			throw Menu::InvalidData();
	}
	if (tests.size() != Courses::NUM_TESTS 
		|| quizzes.size() != Courses::NUM_QUIZZES 
		|| hworks.size() != Courses::NUM_HW)
		throw Menu::InvalidData();
	
	Courses c(quizzes, hworks, tests);
	c.calc_final_score();
	c.calc_letter_grade();
	return c;
}

istream & operator >> (istream & in, Courses &courses)
{
	int i, points;
	for (i = 0; i < Courses::NUM_HW; ++i) {
		in >> points;
		if (points < 0 || points > 100)
			throw Menu::InvalidData();
		courses.homework[i] = points;
		if (!check_len(in, i, Courses::NUM_HW))
			throw Menu::InvalidData();
	}
	for (i = 0; i < Courses::NUM_QUIZZES; ++i) {
		in >> points;
		if (points < 0 || points > 100)
			throw Menu::InvalidData();
		courses.quiz[i] = points;
		if (!check_len(in, i, Courses::NUM_QUIZZES))
			throw Menu::InvalidData();
	}
	for (i = 0; i < Courses::NUM_TESTS; ++i) {
		in >> points;
		if (points < 0 || points > 100)
			throw Menu::InvalidData();
		courses.test[i] = points;
		if (!check_len(in, i, Courses::NUM_TESTS))
			throw Menu::InvalidData();
	}
	courses.calc_final_score();
	courses.calc_letter_grade();
	return in;
}

ostream & operator<<(ostream & out, Courses & courses)
{
	out << courses.final_score << ' ' << courses.letter_grade;
	return out;
}

static bool check_len(istream& in, int& i, const int& possible_len) {
	char c;
	c = in.peek();
	// donju liniju treba promijeniti, suvise nerazumljiva
	if (isalpha(c))
		return false;
	if ((c != ' ') && (i < possible_len - 1))
		return false;
	return true;
}
