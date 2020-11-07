/*
 * File: mgraph.cpp
 * ----------------
 * Implements the graph data structures as a adjust matrix. 
 * 
 * Chao Wang, Thu Nov 5 2020
 */
 

#include "genlib.h"
#include "simpio.h"
#include "vector.h"
#include <iostream>
#include "mgraph.h"

MGraph::MGraph() {
}

// Vertex
void MGraph::addVertex(Vertex &v) {
	if (!vertexExist(v.name)) {
		vertexes.add(v);
		if (arcs.size() == 0) {
			Vector<double> v;
			v.add(-1);
			arcs.add(v);
		} else {
			Vector<double> newVertex = arcs[0];
			for (int i = 0; i < newVertex.size(); i++) {
				newVertex[i] = -1;
			}
			arcs.add(newVertex);
			for (int i = 0; i < arcs.size(); i++) {
				arcs[i].add(-1);
			}
		}
	}
}

bool MGraph::vertexExist(string &name) {
	return (getVertexIndex(name) != -1);
}

bool MGraph::vertexExist(int index) {
	return (0 <= index && index < vertexes.size());
}

int MGraph::getVertexIndex(string &name) {
	for (int i = 0; i < vertexes.size(); i++) {
		if (vertexes[i].name == name) {
			return i;
		}
	}
	return -1;
}

Vertex MGraph::getVertex(int index) {
	if (vertexExist(index)) {
		return vertexes[index];
	}
	return Vertex();
}

void MGraph::removeVertex(int vertex) {
	if (vertexExist(vertex)) {
		arcs.removeAt(vertex);
		for (int i = 0; i < arcs.size(); i++) {
			arcs[i].removeAt(vertex);
		}
		vertexes.removeAt(vertex);
	}
}

int MGraph::vertexNum() {
	return vertexes.size();
}

Vector<string> MGraph::getAllVertexNames() {
	Vector<string> result;
	for (int i = 0; i < vertexes.size(); i++) {
		result.add(vertexes[i].name);
	}
	return result;
}

Vector<int> MGraph::getAdjustVertexes(int vertex) {
	Vector<int> result;
	if (vertexExist(vertex)) {
		for (int i = 0; i < arcs[vertex].size(); i++) {
			if (arcs[vertex][i] > 0) result.add(i);
		}
	}
	return result;
}

// Arc
void MGraph::addArc(int vertex1, int vertex2, double length) {
	if (vertexExist(vertex1) && vertexExist(vertex2)) {
		arcs[vertex1][vertex2] = length;
		arcs[vertex2][vertex1] = length;
	}
}

bool MGraph::arcExist(int vertex1, int vertex2) {
	if (vertexExist(vertex1) && vertexExist(vertex2) && arcs[vertex1][vertex2] > 0) {
		return true;
	}
	return false;
}

double MGraph::arcLength(int vertex1, int vertex2) {
	if (vertexExist(vertex1) && vertexExist(vertex2)) {
		return arcs[vertex1][vertex2];
	}
	return -1;
}

void MGraph::removeArc(int vertex1, int vertex2) {
	if (vertexExist(vertex1) && vertexExist(vertex2)) {
		arcs[vertex1][vertex2] = -1;
		arcs[vertex2][vertex1] = -1;
	}
}

int MGraph::arcNum() {
	int cnt = 0;
	for (int i = 0; i < arcs.size(); i++) {
		for (int j = 0; j <= i; j++) {
			if (arcs[i][j] > 0) {
				cnt++;
			}
		}
	}
	return cnt;
}

Vector<Vector<int>> MGraph::getAllArcs() {
	Vector<Vector<int>> allArcs;
	for (int i = 0; i < arcs.size(); i++) {
		for (int j = 0; j <= i; j++) {
			if (arcs[i][j] > 0) {
				Vector<int> vec;
				vec.add(i);
				vec.add(j);
				allArcs.add(vec);
			}
		}
	}
	return allArcs;
}

// debug
void MGraph::printInfo() {
	cout << "Vertexes are:" << endl;
	for (int i = 0; i < vertexes.size(); i++) {
		cout << i << '\t' << vertexes[i].name << endl;
	}
	cout << "Arcs are:" << endl;
	Vector<Vector<int>> result = getAllArcs();
	for (int i = 0; i < result.size(); i++) {
		cout << vertexes[result[i][0]].name << '\t'
			<< vertexes[result[i][1]].name << '\t'
			<< arcs[result[i][0]][result[i][1]] << endl;
	}
}

// clear
void MGraph::clear() {
	vertexes.clear();
	arcs.clear();
}