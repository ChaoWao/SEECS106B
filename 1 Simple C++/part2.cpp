/*
 * Program: part2.cpp
 * --------------------
 * Program used to simulating voting technologies.
 *
 * Chao Wang Sau Sep 20 2020
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "random.h"

/* Function prototypes */

bool election(int voters, double spread, double error);


/*
 * Function: election
 * Usage: right = election(voters, spread, error);
 * ------------------------------------------------
 * This function takes the number of voters, the percentage spread
 * between candidates and the voting error percentage to simulate
 * the voting result.
 */
bool election(int voters, double spread, double error) {
	// voters of first candidate and second candidate
	int first = voters / 2 + voters * spread / 2;
	int second = voters - first;
	// statistic of voters
	int v_first = 0, v_second = 0;
	for (int i = 0; i < first; i++) {
		double tmp = RandomReal(0, 1);
		if (tmp < error) {
			v_second += 1;
		} else {
			v_first += 1;
		}
	}
	for (int i = 0; i < second; i++) {
		double tmp = RandomReal(0, 1);
		if (tmp < error) {
			v_first += 1;
		} else {
			v_second += 1;
		}
	}
	return (first > second && v_first > v_second) || (first < second && v_first < v_second);
}

int main ()
{
	// init
	Randomize();
	// ask user for input
	cout << "Enter number of voters:";
	int voters = GetInteger();
	// spread means rate of first candidates - rate of second candidates
	// for the case mentioned in H09-Assign1SimpleC.pdf, spread is 0.01
	cout << "Enter percentage spread between candidates:";
	double spread = GetReal();
	cout << "Enter voting error percentage:";
	double error = GetReal();
	while (voters <= 0 || spread < 0 || spread > 1) {
		cout << "Errors found in your input. Re-prompting..." << endl;
		cout << "Enter number of voters:";
		voters = GetInteger();
		cout << "Enter percentage spread between candidates:";
		spread = GetReal();
		cout << "Enter voting error percentage:";
		error = GetReal();
	}
	// simulating 500 trys
	const int total_try = 500;
	int invalid_numbers = 0;
	for (int i = 0; i < total_try; i++) {
		bool is_right = election(voters, spread, error);
		if (!is_right) invalid_numbers++;
	}
	cout << "Chance of an invalid election result after 500 trials = " << (100.0 * invalid_numbers / total_try) << "%";
	return 0;
}