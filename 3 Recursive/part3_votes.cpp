/*
 * Program: part3_votes.cpp
 * ----------------------------
 * Program used to count the number of situations
 * in which a block's vote is critical. 
 *
 * Chao Wang Sun Oct 18 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

/*
 * Function: recursive_find
 * Usage: number = recursive_find(left_blocks, Alice, Bob, to_win);
 * -------------------------------------------------------
 * This fucntion recursively find the number of situations where
 * a critical votes occurs.
 * Alice is the votes of the first candidate, Bob is the other.
 * to_win is the number required for the candidate to win.
 */
int recursive_find(Vector<int> &left_blocks, int Alice, int Bob, int to_win) {
	if (left_blocks.size() == 0) {
		if (Alice >= to_win || Bob >= to_win) return 0;
		else return 1;
	}
	int result = 0;
	Vector<int> new_left_blocks = left_blocks;
	new_left_blocks.removeAt(0);
	result += recursive_find(new_left_blocks, Alice+left_blocks[0], Bob, to_win);
	result += recursive_find(new_left_blocks, Alice, Bob+left_blocks[0], to_win);
	return result;
}

/*
 * Function: CountCriticalVotes
 * Usage: number = CountCriticalVotes(blocks, blockIndex);
 * -------------------------------------------------------
 * This fucntion the number of situations in which a block's 
 * vote is critical. The block is given by its index.
 */
int CountCriticalVotes(Vector<int> &blocks, int blockIndex) {
	if (blockIndex < 0 || blockIndex >= blocks.size()) {
		return -1;
	}
	int sum = 0;
	for (int i = 0; i < blocks.size(); i++) {
		sum += blocks[i];
	}
	int to_win = (sum + 1)/2;
	blocks.removeAt(blockIndex);
	return recursive_find(blocks, 0, 0, to_win);
}

void testCountCriticalVotes () {
	Vector<int> blocks;
	while (true) {
		cout << "Enter a new block (or 0 to finish): ";
		int block = GetInteger();
		if (block == 0) {
			if (blocks.size() != 0) {
				break;
			} else {
				cout << "You have not entered a block, exiting...";
				return;
			}
		} else if (block < 0) {
			cout << "Negtive Integer, Re-Enter..." << endl;
		} else {
			blocks.add(block);
		}
	}
	int index = 0;
	while (true) {
		cout << "Enter a index between [0, " << blocks.size()-1 << "]: ";
		index = GetInteger();
		if (index < 0 || index >= blocks.size()) {
			cout << "You have entered a number exceeded the bound, Re-Enter..." << endl;
		} else {
			break;
		}
	}
	cout << "Critical Votes: " << CountCriticalVotes(blocks, index) << endl;
}

int main() {
	testCountCriticalVotes();
	return 0;
}