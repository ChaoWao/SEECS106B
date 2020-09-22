/*
 * Program: part5.cpp
 * --------------------
 * Program to produce histogram from a file of exam scores.
 *
 * Chao Wang Sau Sep 22 2020
 */

#include <iostream>
#include <fstream>
#include <string>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

/* Function prototypes */

Vector<string> histogram(fstream &in);

/*
 * Function: histogram
 * Usage: h = histogram(in);
 * ------------------------------------------------
 * According to the table, return 0-6 if letter is A-Z;
 * otherwise, return 7.
 */
Vector<string> histogram(fstream &in) {
	Vector<string> result;
	for (int i = 0; i < 10; i++) {
		result.add("");
	}
	int score;
	while (in >> score) {
		if (score >= 100 || score < 0) {
			continue;
		}
		result[score/10].append("X");
	}
	return result;
}

int main ()
{
	string file_name;
	fstream in;
	while (true) {
		cout << "Enter the name of the file containing scores: ";
		file_name = GetLine();
		in.open(file_name.c_str());
		if (in.fail()) {
			in.clear();
			cout << "Error when opening file! Re-prompting..." << endl;
		} else {
			break;
		}
	}
	Vector<string> h = histogram(in);
	for (int i = 0; i < 10; i++) {
		cout << 0+i*10 << "-" << 9+i*10 << ": " << h[i] << endl;
	}
	return 0;
}