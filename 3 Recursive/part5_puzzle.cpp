/*
 * Program: part5_puzzle.cpp
 * ----------------------------
 * Program used to find out if the puzzle is solvable.
 *
 * Chao Wang Sun Oct 18 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

/*
 * Function: walk_to_end
 * Usage: flag = walk_to_end(now, squares, walked);
 * ---------------------------------------------------
 * This function recursively walks on the squares based on now
 * position and walked flags which indicates whether one square
 * is walked.
 * Initially, set the walked vector size equals the squares vector
 * size and set its content 0.
 * ATTENTION, this function will change the walked vector and change
 * back when not reach the end; but it never changes the squares
 * vector as required.
 */
bool walk_to_end(int now, Vector<int> &squares, Vector<int> &walked) {
	if (now == squares.size()-1) {
		return true;
	}
	int distance = squares[now];
	walked[now] = 1;
	int right_next = now + distance;
	if (right_next < squares.size() && walked[right_next] == 0) {
		if (walk_to_end(right_next, squares, walked)) return true;
	}
	int left_next = now - distance;
	if (left_next >= 0 && walked[left_next] == 0) {
		if (walk_to_end(left_next, squares, walked)) return true;
	}
	walked[now] = 0;
	return false;
}

/*
 * Function: Solvable
 * Usage: to_the_end = Solvable(start, squares);
 * -------------------------------------------------
 * This fucntion judges if you can walk to the end of the squares from
 * the start. It calls walk_to_end with initially an vector walked
 * whose size equals to the size of squares, and which fills with 0.
 */
bool Solvable(int start, Vector<int>& squares) {
	Vector<int> walked;
	for (int i = 0; i < squares.size(); i++) {
		walked.add(0);
	}
	return walk_to_end(start, squares, walked);
}

void testSolvable () {
	Vector<int> squares;
	while (true) {
		cout << "Enter positive integer to continue, or enter 0 to finish: ";
		int number = GetInteger();
		if (number == 0) {
			squares.add(number);
			break;
		} else if (number < 0) {
			cout << "Negtive Integer, Re-Enter..." << endl;
		} else {
			squares.add(number);
		}
	}
	int index = 0;
	while (true) {
		cout << "Enter a start position between [0, " << squares.size()-1 << "]: ";
		index = GetInteger();
		if (index < 0 || index >= squares.size()) {
			cout << "You have entered a number exceeded the bound, Re-Enter..." << endl;
		} else {
			break;
		}
	}
	cout << "This puzzle is " << (Solvable(index, squares) ? "solvable." : "unsolvable.") << endl;
}

int main() {
	testSolvable();
	return 0;
}