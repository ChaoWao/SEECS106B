/*
 * Program: part4.cpp
 * --------------------
 * Program implementing Soundex code algorithms.
 *
 * Chao Wang Sau Sep 20 2020
 */

#include <iostream>
#include <string>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

/* Function prototypes */

char letter_to_digit(char letter);
string surname_to_intercode(string surname);
string remove_consecutive_duplicate(string code);

// Translate table
Vector<string> table;

/*
 * Function: letter_to_digit
 * Usage: digit = letter_to_digit(letter);
 * ------------------------------------------------
 * According to the table, return 0-6 if letter is A-Z;
 * otherwise, return 7.
 */
char letter_to_digit(const char letter) {
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].length(); j++) {
			if (table[i][j] == letter) {
				return '0' + i;
			}
		}
	}
	return '7';
}

/*
 * Function: surname_to_intercode
 * Usage: code = surname_to_intercode(surname);
 * ------------------------------------------------
 * Translate surname to unduplicated Soundex code.
 */
string surname_to_intercode(const string surname) {
	if (surname.length() == 0) return "";
	string result = "";
	// find first non-letter characters
	int i = 0;
	for (; i < surname.length(); i++) {
		if (surname[i] >= 'a' && surname[i] <= 'z') {
			result += surname[i] - 'a' + 'A';
			break;
		} else if (surname[i] >= 'A' && surname[i] <= 'Z') {
			result += surname[i];
			break;
		}
	}
	for (i++; i < surname.length(); i++) {
		if (surname[i] >= 'a' && surname[i] <= 'z') {
			result += letter_to_digit(surname[i] - 'a' + 'A');
		} else if (surname[i] >= 'A' && surname[i] <= 'Z') {
			result += letter_to_digit(surname[i]);
		}
	}
	return result;
}

/*
 * Function: remove_consecutive_duplicate
 * Usage: new_code = remove_consecutive_duplicate(code);
 * ------------------------------------------------
 * If there are consecutive duplicate digits in code, remove it.
 * Otherwise, it keeps unchanged.
 */
string remove_consecutive_duplicate(const string code) {
	if (code.length() <= 1) return "";
	string result = "";
	char ch = code[0];
	result += ch;
	for (int i = 1; i < code.length(); i++) {
		if (code[i] != '0' && ch != code[i]) {
			ch = code[i];
			result += ch;
		}
	}
	return result;
}

int main ()
{
	table.add("AEIOUHWY");
	table.add("BFPV");
	table.add("CGJKQSXZ");
	table.add("DT");
	table.add("MN");
	table.add("L");
	table.add("R");
	// Result for Zelenski should be Z542, maybe an error in H09-Assign1SimpleC.pdf
	while (true) {
		cout << "Enter surname (RETURN to quit): ";
		string surname = GetLine();
		if (surname == "RETURN") break;
		string code = surname_to_intercode(surname);
		code = remove_consecutive_duplicate(code);
		if (code.length() > 4) {
			code = code.substr(0, 4);
		} else {
			while (code.length() != 4) {
				code += '0';
			}
		}
		cout << "Soundex code for " << surname << " is " << code << endl;
	}
	return 0;
}