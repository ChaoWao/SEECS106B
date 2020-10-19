/*
 * Program: part5_puzzle.cpp
 * -------------------------
 * Program used to figure out the minimum number of
 * stock pipes required to satisfy the list of requests.
 *
 * Chao Wang Mon Oct 19 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

/*
 * Function: minimum
 * Usage: minimum_number = minimum(requests, stockLength, left);
 * -------------------------------------------------------------
 * This fucntion gives a minimum number needed to cut the reqeusts,
 * accroding to the stockLength and the existing left pipes.
 * This function using a recursive method to solve the problem.
 * Initially, if there is no pipes already used, make left an empty
 * vector and call this function.
 */
int minimum(Vector<int>& requests, int stockLength, Vector<int> &left) {
	if (requests.size() == 0) return left.size();
	int request = requests[requests.size()-1];
	requests.removeAt(requests.size()-1);
	// try a new a pipe
	left.add(stockLength-request);
	int result = minimum(requests, stockLength, left);
	left.removeAt(left.size()-1);
	// using exiting avaliable pipes to try
	for (int i = left.size()-1; i >= 0; i--) {
		if (left[i] >= request) {
			left[i] -= request;
			int one_try = minimum(requests, stockLength, left);
			left[i] += request;
			if (one_try < result) result = one_try;
		}
	}
	requests.add(request);
	return result;
}

/*
 * Function: CutStock
 * Usage: minimum_number = CutStock(requests, stockLength);
 * --------------------------------------------------------
 * This fucntion gives a minimum number needed to cut the reqeusts,
 * accroding to the stockLength. It calls minimum with initially an
 * empty vector left.
 */
int CutStock(Vector<int>& requests, int stockLength) {
	Vector<int> left;
	return minimum(requests, stockLength, left);
}

/*
 * Function: checkStockLength
 * Usage: flag = checkStockLength(requests, stockLength);
 * ------------------------------------------------------
 * This fucntion checks if  all elements in the vector are
 * no longer than the stock pipe length.
 */
bool checkStockLength(Vector<int> &requests, int stockLength) {
	for (int i = 0; i < requests.size(); i++) {
		if (stockLength < requests[i]) return false;
	}
	return true;
}

void testCutStock () {
	Vector<int> requests;
	while (true) {
		cout << "Enter positive integer to add a request, or enter 0 to finish: ";
		int number = GetInteger();
		if (number == 0) {
			break;
		} else if (number < 0) {
			cout << "Negtive Integer, Re-Enter..." << endl;
		} else {
			requests.add(number);
		}
	}
	if (requests.size() == 0) {
		cout << "NO REQUESTS, EXITING..." << endl;
		return;
	}
	int stockLength = 0;
	while (true) {
		cout << "Enter the length of the stock: ";
		stockLength = GetInteger();
		if (!checkStockLength(requests, stockLength)) {
			cout << "You have entered a number less than a request, Re-Enter..." << endl;
		} else {
			break;
		}
	}
	cout << "This minimum number of pipes is " << CutStock(requests, stockLength) << "." << endl;
}

int main() {
	testCutStock();
	return 0;
}