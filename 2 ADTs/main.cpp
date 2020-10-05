/*
 * Program: main.cpp
 * --------------------
 * Program used to create menu for assignment 2.
 *
 * Chao Wang San Oct 4 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "graphics.h"

extern void random_writer();
extern void perfect_maze();

int main() {
	InitGraphics();
	Randomize();
	while (true) {
		cout << "Here is the menu:" << endl;
		cout << "\tEnter 0 to quit" << endl;
		cout << "\tEnter 1 for Random Writer" << endl;
		cout << "\tEnter 2 for Maze" << endl;
		cout << "Choice: ";
		int choice = -1;
		choice = GetInteger();
		if (choice == 0) {
			exit(0);
		} else if (choice == 1) {
			random_writer();
		} else if (choice == 2) {
			perfect_maze();
		} else {
			cout << "Try again!" << endl;
		}
		cout << endl;
	}
	// should never be here, but...
	return 0;
}