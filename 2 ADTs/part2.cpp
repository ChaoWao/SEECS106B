/*
 * Program: part2.cpp
 * --------------------
 * Program used to create perfect maze and solve it.
 *
 * Chao Wang Mon Oct 5 2020
 */
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "set.h"
#include "vector.h"
#include "queue.h"
#include "random.h"
#include "extgraph.h"
#include "maze.h"

/*
 * Function: cmp_point
 * Usage: euqal = cmp_point(p1, p2);
 * ------------------------------------------------
 * Compare two pointTs and return 1 if equal, return 0 if not.
 */
int cmp_point(pointT p1, pointT p2) {
	if (p1.row == p2.row) {
		if (p1.col == p2.col) {
			return 0;
		} else if (p1.col < p2.col) {
			return -1;
		} else {
			return 1;
		}
	} else if (p1.row < p2.row) {
		return -1;
	} else {
		return 1;
	}
}

/*
 * Function: left
 * Usage: left_point = left(p);
 * ------------------------------------------------
 * Return left point of p.
 */
pointT left(pointT p) {
	pointT result = {p.row, p.col-1};
	return result;
}

/*
 * Function: up
 * Usage: up_point = up(p);
 * ------------------------------------------------
 * Return up point of p.
 */
pointT up(pointT p) {
	pointT result = {p.row+1, p.col};
	return result;
}

/*
 * Function: right
 * Usage: right_point = right(p);
 * ------------------------------------------------
 * Return right point of p.
 */
pointT right(pointT p) {
	pointT result = {p.row, p.col+1};
	return result;
}

/*
 * Function: down
 * Usage: down_point = down(p);
 * ------------------------------------------------
 * Return down point of p.
 */
pointT down(pointT p) {
	pointT result = {p.row-1, p.col};
	return result;
}

typedef pointT (*gen_type)(pointT);

/*
 * Function: get_neighbors
 * Usage: neighbors = get_neighbors(p, maze);
 * ------------------------------------------------
 * Return avaliable neighbors of p in maze.
 */
Vector<pointT> get_neighbors(pointT p, Maze &m) {
	Vector<pointT> result;
	Vector<gen_type> gen;
	gen.add(left);
	gen.add(up);
	gen.add(right);
	gen.add(down);
	for (int i = 0; i < gen.size(); i++) {
		if (m.pointInBounds(gen[i](p))) {
			result.add(gen[i](p));
		}
	}
	return result;
}

/*
 * Function: aldous_broder
 * Usage: aldous_broder(maze);
 * ------------------------------------------------
 * Build a perfect maze using Aldous-Broder algorithm.
 */
void aldous_broder(Maze &m) {
	Set<pointT> excluded(cmp_point);
	for (int i = 0; i < m.numRows(); i++) {
		for (int j = 0; j < m.numCols(); j++) {
			pointT p = {i, j};
			excluded.add(p);
		}
	}
	if (excluded.size() < 1) {
		return;
	}
	pointT curr = {RandomInteger(0, m.numRows()-1), RandomInteger(0, m.numCols()-1)};
	excluded.remove(curr);
	while (!excluded.isEmpty()) {
		Vector<pointT> neighbors = get_neighbors(curr, m);
		pointT next = neighbors[RandomInteger(0, neighbors.size()-1)];
		if (excluded.contains(next)) {
			m.setWall(curr, next, false);
			excluded.remove(next);
			Pause(0.01);
		}
		curr = next;
	}
}

/*
 * Function: available_neighbors
 * Usage: neighbors = available_neighbors(p, maze);
 * ------------------------------------------------
 * Return all availiable neighbors of point p in maze.
 */
Vector<pointT> available_neighbors(pointT p, Maze& m) {
	Vector<pointT> neighbors = get_neighbors(p, m);
	Vector<pointT> result;
	for (int i = 0; i < neighbors.size(); i++) {
		if (!m.isWall(p, neighbors[i])) {
			result.add(neighbors[i]);
		}
	}
	return result;
}

/*
 * Function: available_neighbors
 * Usage: neighbors = available_neighbors(p, maze);
 * ------------------------------------------------
 * Return all availiable neighbors of point p in maze.
 */
typedef Vector<pointT> Path;
bool walked(pointT p, Path path) {
	for (int i = 0; i < path.size(); i++) {
		if (cmp_point(p, path[i]) == 0) {
			return true;
		}
	}
	return false;
}

/*
 * Function: solve
 * Usage: path = solve(maze);
 * ------------------------------------------------
 * Find a path from (0,0) to (row_num-1, col_num-1) 
 * using BFS algorithm.
 */
Path solve(Maze &m) {
	Queue<Path> fringe;
	pointT curr = {0, 0};
	Path path;
	path.add(curr);
	pointT end = {m.numRows()-1, m.numCols()-1};
	fringe.enqueue(path);
	while (!fringe.isEmpty()) {
		path = fringe.dequeue();
		curr = path[path.size()-1];
		if (cmp_point(curr, end) == 0) {
			return path;
		}
		Vector<pointT> neighbors = available_neighbors(curr, m);
		for (int i = 0; i < neighbors.size(); i++) {
			pointT next = neighbors[i];
			if (!walked(next, path)) {
				Path new_path = path;
				new_path.add(next);
				fringe.enqueue(new_path);
			}
		}
	}
	// should never be here, but
	path.clear();
	return path;
}

/*
 * Function: draw_path
 * Usage: draw_path(path, maze);
 * ------------------------------------------------
 * Draw path acrroding to path.
 */
void draw_path(Path path, Maze& m) {
	for (int i = 0; i < path.size(); i++) {
		m.drawMark(path[i], "blue");
		Pause(0.01);
	}
}

/*
 * Function: perfect_maze
 * Usage: perfect_maze();
 * ------------------------------------------------
 * Top level function to organize sub-functions to build
 * and solve maze.
 */
void perfect_maze() {
	cout << "Building maze... ";
	int row_num = 17;
	int col_num = 30;
	Maze m(row_num, col_num, true);
	m.draw();
	aldous_broder(m);
	cout << "Done!" << endl;
	cout << "Hit RETURN to solve: ";
	GetLine();
	draw_path(solve(m), m);
}