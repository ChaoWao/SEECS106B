/*
 * Program: part2_drawruler.cpp
 * ----------------------------
 * Program used to draw ruler of traditional English
 * system of measurement.
 *
 * Chao Wang Thu Oct 8 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"

#define SUFFICIENTLY_SMALL 0.25

void DrawRuler(double x, double y, double w, double h) {
	MovePen(x+w/2, y);
	DrawLine(0, h);
	if (h <= SUFFICIENTLY_SMALL || w <= SUFFICIENTLY_SMALL) {
		return;
	} else {
		DrawRuler(x,y,w/2,h/2);
		DrawRuler(x+w/2,y,w/2,h/2);
	}
}

void testDrawRuler () {
	cout << "Enter x: ";
	double x = GetReal();
	cout << "Enter y: ";
	double y = GetReal();
	cout << "Enter w: ";
	double w = GetReal();
	cout << "Enter h: ";
	double h = GetReal();
	DrawRuler(x,y,w,h);
}

int main () {
	InitGraphics();
	testDrawRuler();
	return 0;
}