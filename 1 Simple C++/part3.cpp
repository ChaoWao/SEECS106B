/*
 * Program: part3.cpp
 * --------------------
 * Program used to explore "Chaos Game".
 *
 * Chao Wang Sau Sep 22 2020
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "graphics.h"
#include "extgraph.h"

// data structure of 2-D points
struct Point {
	double x;
	double y;
};

int main ()
{
	// init
	InitGraphics();
	Randomize();
	cout << "Initialization finished!" << endl;
	cout << "Click three times to draw a triangle..." << endl;
	// get points A, B, C
	Point tri[3];
	for (int i = 0; i < 3; i++) {
		WaitForMouseDown();
		tri[i].x = GetMouseX();
		tri[i].y = GetMouseY();
		WaitForMouseUp();
		cout << i+1 << " time finished! The point clicked is (" << tri[i].x << ", " << tri[i].y << ")." << endl;
	}
	cout << "Drawing triangle..." << endl;
	for (int i = 0; i < 3; i++) {
		MovePen(tri[i].x, tri[i].y);
		DrawLine(tri[(i+1)%3].x - tri[i].x, tri[(i+1)%3].y - tri[i].y);
	}
	cout << "Triangle drawed!" << endl;
	// randomly choose current point
	cout << "Randomly choosing the current point..." << endl;
	Point curr;
	int tmp = RandomInteger(0, 2);
	if (tmp == 0) {
		curr = tri[0];
	} else if (tmp == 1) {
		curr = tri[1];
	} else if (tmp == 2) {
		curr = tri[2];
	}
	cout << "Choose the " << tmp << "th point as current point." << endl;
	// loop until user click the mouse
	cout << "Loop started! Click to stop." << endl;
	const double r = 0.1;
	const double density = 0.5;
	while (!MouseButtonIsDown()) {
		cout << "Current point: (" << curr.x << ", " << curr.y << ")." << endl;
		MovePen(curr.x, curr.y+r);
		StartFilledRegion(density);
		DrawArc(r, 0, 360);
		EndFilledRegion();
		UpdateDisplay();
		// update position of current point
		tmp = RandomInteger(0, 2);
		if (tmp == 0) {
			curr.x = (tri[0].x + curr.x) / 2;
			curr.y = (tri[0].y + curr.y) / 2;
		} else if (tmp == 1) {
			curr.x = (tri[1].x + curr.x) / 2;
			curr.y = (tri[1].y + curr.y) / 2;
		} else if (tmp == 2) {
			curr.x = (tri[2].x + curr.x) / 2;
			curr.y = (tri[2].y + curr.y) / 2;
		}
	}
	return 0;
}