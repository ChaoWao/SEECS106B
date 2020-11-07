/*
 * File: mgraph.h
 * --------------
 * Defines the graph data structures as a adjust matrix. 
 * 
 * Chao Wang, Thu Nov 5 2020
 */
 
 
#ifndef _mgraph_h
#define _mgraph_h

#include "genlib.h"
#include "vector.h"

/* Type: Vertex
 * ------------
 * Just a simple class to handle a pair of x,y coordinate values
 * and its name.
 */
class Vertex {
public:
	string name;
	double x, y;
};

/* Type: MGraph
 * ------------
 * Matrix Graph (MGraph) specifies the interface of a graph.
 * This graph is implemented as a adjust matrix.
 * Node information is kept in a vector of Vertex. Arc information
 * is kept in a vector of vector of double, where -1 means no arc.
 */
class MGraph {
public:

	/* 
	 * Constructor: MGraph
	 * Usage: MGraph m;
	 *        MGraph *mp = new MGraph;
	 * -------------------------------
	 * The constructor initializes a new graph with no vertexes and no arcs.
	 */
	MGraph();

	// Vertex

	/*
	 * Member function: addVertex
	 * Usage: m.addVertex(v);
	 * ----------------------
	 * This member function adds a vertex v to graph m.
	 */
	void addVertex(Vertex &v);

	/*
	 * Member function: vertexExist
	 * Usage: isExist = m.vertexExist(name);
	 * ----------------------------------
	 * Returns true if the graph contains a vertex named name.
	 */
	bool vertexExist(string &name);

	/*
	 * Member function: vertexExist
	 * Usage: isExist = m.vertexExist(index);
	 * --------------------------------------
	 * Returns true if the index is valid to find a vertex.
	 */
	bool vertexExist(int index);

	/*
	 * Member function: getVertexIndex
	 * Usage: index = m.getVertexIndex(name);
	 * --------------------------------------
	 * Returns the index of the vertex, returns -1 if not found.
	 */
	int getVertexIndex(string &name);

	/*
	 * Member function: getVertex
	 * Usage: vertex = m.getVertex(index);
	 * -----------------------------------
	 * Returns the indexed vertex.
	 * Undefined if index is not valid.
	 */
	Vertex getVertex(int index);

	/*
	 * Member function: removeVertex
	 * Usage: m.removeVertex(index);
	 * -----------------------------
	 * Remove the indexed vertex.
	 * Unchanged if index is not valid.
	 */
	void removeVertex(int vertex);

	/*
	 * Member function: vertexNum
	 * Usage: num = m.vertexNum();
	 * ---------------------------
	 * Returns the number of the vertexes.
	 */
	int vertexNum();

	/*
	 * Member function: getAllVertexNames
	 * Usage: names = m.getAllVertexNames();
	 * -------------------------------------
	 * Returns all the names of the vertexes.
	 */
	Vector<string> getAllVertexNames();

	/*
	 * Member function: getAdjustVertexes
	 * Usage: adjust_nodes = m.getAdjustVertexes(index);
	 * -------------------------------------------------
	 * Returns all the adjust nodes of the indexed vertex.
	 */
	Vector<int> getAdjustVertexes(int vertex);

	// Arc
	/*
	 * Member function: addArc
	 * Usage: m.addArc(index1, index2, length);
	 * ----------------------------------------
	 * Add a arc between index1 node and index2 node.
	 */
	void addArc(int vertex1, int vertex2, double length);

	/*
	 * Member function: arcExist
	 * Usage: isExist = m.arcExist(index1, index2);
	 * --------------------------------------------
	 * Returns true if the graph already has a arc from 
	 * index1 node to index2 node.
	 */
	bool arcExist(int vertex1, int vertex2);

	/*
	 * Member function: arcLength
	 * Usage: length = m.arcLength(index1, index2);
	 * --------------------------------------------
	 * Returns the length if the graph already has a arc from 
	 * index1 node to index2 node. Returns -1 otherwise.
	 */
	double arcLength(int vertex1, int vertex2);

	/*
	 * Member function: removeArc
	 * Usage: m.removeArc(index1, index2);
	 * -----------------------------------
	 * Removes the arc if the graph already has a arc from 
	 * index1 node to index2 node.
	 * Unchanged if not.
	 */
	void removeArc(int vertex1, int vertex2);

	/*
	 * Member function: arcNum
	 * Usage: num = m.arcNum();
	 * -------------------------
	 * Returns the number of the arcs.
	 */
	int arcNum();

	/*
	 * Member function: getAllArcs
	 * Usage: arcs = m.getAllArcs();
	 * -----------------------------
	 * Returns all the arcs in a vector. The arc is specified
	 * as a vector of two elements, the start index and the 
	 * end index.
	 */
	Vector<Vector<int>> getAllArcs();

	// debug
	/*
	 * Member function: printInfo
	 * Usage: m.printInfo();
	 * ---------------------
	 * Prints the graph.
	 */
	void printInfo();

	// clear
	/*
	 * Member function: clear
	 * Usage: m.clear();
	 * -----------------
	 * Clear the graph. After this, there shall be no vertex and no arc.
	 */
	void clear();
private:
	// Data member: vertexes, store all the vertexes.
	Vector<Vertex> vertexes;
	// Data member: arcs, store all the arcs.
	Vector<Vector<double>> arcs;
};

#endif