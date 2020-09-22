/*
 * Program: perfect_numbers.cpp
 * --------------------
 * Program used to predicate whether a number in the range 1 to 10000 is a perfect number.
 *
 * Chao Wang Sau Sep 19 2020
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"

#define MIN_NUM 1		// Lower bound for searching perfect numbers
#define MAX_NUM	10000	// Upper bound for searching perfect numbers

/* Function prototypes */

bool IsPerfect(int n);


/*
 * Function: IsPerfect
 * Usage: is_perfect_number = IsPerfect(number);
 * -----------------------------------------
 * This function takes a number and judge whether it is a perfect number,
 * number is an integer in the range [MIN_NUM, MAX_NUM]. The predicate is
 * made by walk through the numbers less than number.
 */
bool IsPerfect(int n) {
	if (n < MIN_NUM || n > MAX_NUM) {
		return false;
	} else {
		int sum = 0;
		for (int i = 1; i < n; i++) {
			if (n % i == 0) {
				sum += i;
			}
		}
		if (sum == n) {
			return true;
		} else {
			return false;
		}
	}
}

int main ()
{
	// find perfect number from MIN_NUM to MAX_NUM
	// if found, print it
	for (int i = MIN_NUM; i <= MAX_NUM; i++) {
		if (IsPerfect(i)) {
			cout << "Find perfect number: " << i << endl;
		}
	}
	// after run, perfect numbers found are
	// 6, 28, 496, 8128

	return 0;
}