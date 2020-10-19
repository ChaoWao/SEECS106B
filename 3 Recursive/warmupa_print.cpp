/*
 * Program: warmupa_print.cpp
 * --------------------
 * Program used to print number in binary.
 *
 * Chao Wang Tue Oct 6 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"

void PrintInBinary(int number) {
	if (number == 0 || number == 1) {
		cout << number;
	} else {
		PrintInBinary(number >> 1);
		cout << number % 2;
	}
}

void test () {
	while (true) {
		cout << "Enter non-negative integer to test, or -1 to quit: ";
		int number = GetInteger();
		if (number == -1) return;
		else if (number < -1) cout << "Wrong Input!" << endl;
		else {
			PrintInBinary(number);
			cout << endl;
		}
	}
}


int main ()
{
	test();
	return 0;
}
