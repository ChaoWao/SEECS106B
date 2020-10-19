/*
 * Program: part1_countways.cpp
 * ----------------------------
 * Program used to count the number of different ways 
 * to climb a staircase of a height taking strides of
 * one or two stairs at a time.
 *
 * Chao Wang Thu Oct 8 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"

int CountWays(int numStairs) {
	if (1 == numStairs || 2 == numStairs) {
		return numStairs;
	} else {
		return CountWays(numStairs-1) + CountWays(numStairs-2);
	}
}

void testCountWays () {
	while (true) {
		cout << "Enter positive integer to test, or 0 to quit: ";
		int number = GetInteger();
		if (number == 0) return;
		else if (number < 0) cout << "Wrong Input!" << endl;
		else {
			cout << CountWays(number);
			cout << endl;
		}
	}
}

int main () {
	testCountWays();
	return 0;
}