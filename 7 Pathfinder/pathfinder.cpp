/* pathfinder.cpp
 * ---------------
 * A starter file with some starting constants and handy utility routines.
 */
 
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "mgraph.h"
#include "vector.h"
#include "set.h"
#include "pqueue.h"

/* Constants
 * --------
 * A few program-wide constants concerning the graphical display.
 */
const double CircleRadius =.05;     	// the radius of a node
const int LabelFontSize = 9;          // for node name labels


/* Type: coordT
 * ------------
 * Just a simple struct to handle a pair of x,y coordinate values.
 */
struct coordT {
	double x, y;
};

/* Type: Path
 * ------------
 * Just a simple struct to handle a path with its length.
 * The path is represented as the vertex sequence.
 */
class Path {
public:
    Vector<int> path;
    double length;
};

/* Type: Arc
 * ------------
 * Just a simple struct to represent a arc with its length.
 */
class Arc {
public:
    int start, end;
    double length;
};


/* Function: DrawFilledCircleWithLabel
 * Usage:  DrawFilledCircleWithLabel(center, "Green", "You are here");
 * -------------------------------------------------------------------
 * Uses facilities from extgraph to draw a circle filled with
 * color specified. The circle is centered at the given coord has the
 * specified radius.  A label is drawn to the right of the circle.
 * You can leave off the last argument if no label is desired.
 */
void DrawFilledCircleWithLabel(coordT center, string color, string label = "")
{
	MovePen(center.x + CircleRadius, center.y);
	SetPenColor(color);
	StartFilledRegion(1.0);
	DrawArc(CircleRadius, 0, 360);
	EndFilledRegion();
	if (!label.empty()) {
		MovePen(center.x + CircleRadius, center.y);
		SetFont("Helvetica");
		SetPointSize(LabelFontSize);
		DrawTextString(label);
	}
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */
void DrawLineBetween(coordT start, coordT end, string color)
{
	SetPenColor(color);
	MovePen(start.x, start.y);
	DrawLine(end.x - start.x, end.y - start.y);
}


/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
	coordT where;
	WaitForMouseDown();
	WaitForMouseUp();
	where.x = GetMouseX();
	where.y = GetMouseY();
	return where;
}

/* Function: WithinDistance
 * Usage:  if (WithinDistance(click, pt))...
 * -----------------------------------------
 * Returns true if the Cartesian distance between the two coordinates
 * is <= the specified distance, false otherwise. If not specified,
 * the distance is assumed to be size of the node diameter on screen.
 */
bool WithinDistance(coordT pt1, coordT pt2, double maxDistance = CircleRadius*2)
{
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double distance = sqrt(dx*dx + dy*dy);
	return (distance <= maxDistance);
}

/* Function: getCoordFromVertex
 * Usage:  coord = getCoordFromVertex(v)
 * -------------------------------------
 * Transform from vertex type to coordT type.
 */
inline coordT getCoordFromVertex(Vertex &v) {
	coordT c;
	c.x = v.x;
	c.y = v.y;
	return c;
}

/* Function: askForFile
 * Usage:  name = askForFile()
 * ---------------------------
 * Ask the user to provide a file name. Retry if the
 * file is not exists.
 */
string askForFile() {
	string file_name;
	ifstream in;
	while (true) {
		cout << "Please enter name of graph data file: ";
		// GetLine will not get error, but since GetInteger will,
		// use cin constantly.
		cin >> file_name;
		in.open(file_name.c_str());
		if (in.fail()) {
			in.clear();
			cout << "Unable to open file named \"" << file_name << "\". Please try again." << endl;
		} else {
			in.close();
			return file_name;
		}
	}
}

/* Function: readGraph
 * Usage:  readGraph(m, in)
 * ------------------------
 * Read the graph to m from the stream in. The stream
 * struction is specified by the handout #34 of the course.
 */
void readGraph(MGraph &m, istream &in) {
	string s;
	double x, y;
	// "NODES" marks beginning of list of nodes
	in >> s;
	while (!in.fail() && s != "NODES") {
	}
	// read vertexes
	Vertex v;
	in >> s;
	while (!in.fail() && s != "ARCS") {
		in >> x >> y;
		// this is before c++ 11, and statements such as "v = {s, x, y}"
		// is not supported
		v.name = s;
		v.x = x;
		v.y = y;
		m.addVertex(v);
		in >> s;
	}
	// read arcs;
	string v1, v2;
	double length;
	while (true) {
		in >> v1 >> v2 >> length;
		if (in.fail()) {
			break;
		}
		m.addArc(m.getVertexIndex(v1), m.getVertexIndex(v2), length);
	}
}

/* Function: drawGraphVertexes
 * Usage:  drawGraphVertexes(m)
 * ----------------------------
 * Draws all the vertexes of the graph to the graphics.
 */
void drawGraphVertexes(MGraph &m) {
	// draw nodes
	for (int i = 0; i < m.vertexNum(); i++) {
		Vertex v = m.getVertex(i);
		DrawFilledCircleWithLabel(getCoordFromVertex(v), "Black", v.name);
	}
}

/* Function: drawGraphArcs
 * Usage:  drawGraphArcs(m)
 * ------------------------
 * Draws all the arcs of the graph to the graphics.
 */
void drawGraphArcs(MGraph &m) {
	// draw lines
	Vector<Vector<int>> lines = m.getAllArcs();
	for (int i = 0; i < lines.size(); i++) {
		DrawLineBetween(getCoordFromVertex(m.getVertex(lines[i][0])), getCoordFromVertex(m.getVertex(lines[i][1])), "Black");
	}
}

/* Function: buildFromFile
 * Usage:  buildFromFile(m, file_name)
 * ------------------------
 * Builds the graph m from file and show the background
 * picture on the graphics.
 */
void buildFromFile(MGraph &m, string &file_name) {
	ifstream in;
	in.open(file_name.c_str());
	string bg_name;
	getline(in, bg_name);
	DrawNamedPicture(bg_name);
	readGraph(m, in);
}

/* Function: askForClick
 * Usage:  index = askForClick(m, prompt_info)
 * -------------------------------------------
 * Prompt the info, ask the user to click a vertex, returns
 * the index of the vertex clicked.
 * Retry if the user has not clicked a vertex.
 */
int askForClick(MGraph &m, string &info) {
	while (true) {
		cout << info;
		coordT c = GetMouseClick();
		for (int i = 0; i < m.vertexNum(); i++) {
			Vertex v = m.getVertex(i);
			if (WithinDistance(getCoordFromVertex(v), c)) {
				string name = m.getVertex(i).name;
				cout << name << " chosen." << endl;
				return i;
			}
		}
		cout << "Invalid click. Please try again." << endl;
	}
	// should never be here, but...
	return -1;
}

/* Function: askForChoice
 * Usage:  index = askForChoice()
 * ------------------------------
 * Prompt the menu, ask the user to choose.
 */
int askForChoice() {
	while (true) {
		cout << endl << "Your options are:" << endl
			<< "\t<1> Choose a new graph data file" << endl
			<< "\t<2> Find shortest path using Dijkstra's algorithm" << endl
			<< "\t<3> Compute the minimal spanning tree using Kruskal's algorithm" << endl
			<< "\t<4> Quit" << endl
			<< "Enter choice: ";
		/* 
		 * int number = GetInteger();
		 * this function call causes errors 0xc0000005
		 * access vilation at 0x00000024 getloc function
		 * since it's stanford library, I cannot debug it.\
		 * use cin instead.
		 */
		//int number = GetInteger();
		int number;
		cin >> number;
		if (cin.fail() || number < 1 || number > 4) {
			cout << "Invalid choice. Please try again." << endl;
			continue;
		} else {
            cout << endl;
			return number;
		}
	}
}

/* Function: waitConfirm
 * Usage:  waitConfirm()
 * ---------------------
 * Prompt the info, ask the user to hit to continue.
 * Getline will do this, but simpio.h library has bugs.
 * In this assignment, I use cin instead.
 */
void waitConfirm() {
	cout << "Hit return to continue: ";
	cin.clear();
	cin.ignore();
	getchar();
}

/* Function: pathCmp
 * Usage:  bigger = pathCmp(p1, p2)
 * --------------------------------
 * Comparison function of priority queue for path.
 * Shorter length, higher priority.
 */
int pathCmp(Path p1, Path p2) {
    if (p1.length < p2.length) {
        return 1;
    } else if (p1.length == p2.length) {
        return 0;
    } else {
        return -1;
    }
}

/* Function: printPath
 * Usage:  printPath(m, path)
 * --------------------------
 * Print the path as red lines.
 */
void printPath(MGraph &m, Vector<int> &path) {
    for (int i = 1; i < path.size(); i++) {
		DrawLineBetween(getCoordFromVertex(m.getVertex(path[i-1])), getCoordFromVertex(m.getVertex(path[i])), "Red");
    }
}

/* Function: inPath
 * Usage:  if (inPath(p, node)) ...
 * --------------------------------
 * Returns true if the node is already in the path.
 */
bool inPath(Path &p, int node) {
    for (int i = 0; i < p.path.size(); i++) {
        if (p.path[i] == node) return true;
    }
    return false;
}

/* Function: Dijkstra
 * Usage:  Dijkstra(m, index1, index2)
 * -----------------------------------
 * Implement the Dijkstra's algorithm to find the shortest
 * path from node index1 to node index2.
 */
void Dijkstra(MGraph &m, int v1, int v2) {
    cout << "Finding shortest path using Dijkstra..." << endl;
    PQueue<Path> queue(pathCmp);
    Path p;
    Vector<int> path;
    path.add(v1);
    p.path = path;
    p.length = 0;
    queue.enqueue(p);
    int cnt = -1;
    while (!queue.isEmpty()) {
        p = queue.dequeueMax();
        cnt++;
        int node = p.path[p.path.size()-1];
        if (node == v2) {
            printPath(m, p.path);
            cout << "Done! The shortest path from " << m.getVertex(v1).name
                << " to " << m.getVertex(v2).name << " is " << p.length << " miles." << endl;
            cout << "The algorithm dequeued " << cnt << " paths to find the optimal one." << endl;
            return;
        } else {
            Vector<int> adjnodes = m.getAdjustVertexes(node);
            for (int i = 0; i < adjnodes.size(); i++) {
                Path tmp = p;
                if (!inPath(tmp, adjnodes[i])) {
                    tmp.path.add(adjnodes[i]);
                    tmp.length += m.arcLength(node, adjnodes[i]);
                    queue.enqueue(tmp);
                }
            }
        }
    }
}

/* Function: arcCmp
 * Usage:  bigger = arcCmp(p1, p2)
 * -------------------------------
 * Comparison function of priority queue for arc.
 * Shorter length, higher priority.
 */
int arcCmp(Arc a1, Arc a2) {
    if (a1.length < a2.length) {
        return 1;
    } else if (a1.length == a2.length) {
        return 0;
    } else {
        return -1;
    }
}

/* Function: findSet
 * Usage:  index = findSet(sets, node)
 * -----------------------------------
 * Returns the index of the set if there is a set
 * in sets contains the node.
 * Returns -1 if not.
 */
int findSet(Vector<Set<int>> &sets, int node) {
	for (int i = 0; i < sets.size(); i++) {
		if (sets[i].contains(node)) return i;
	}
	return -1;
}

/* Function: MST
 * Usage:  MST(m)
 * --------------
 * Prints the minimus spanning tree of graph m.
 */
void MST(MGraph &m) {
    Vector<Vector<int>> arcs = m.getAllArcs();
    PQueue<Arc> queue(arcCmp);
    for (int i = 0; i < arcs.size(); i++) {
        Arc a;
        a.start = arcs[i][0];
        a.end = arcs[i][1];
        a.length = m.arcLength(arcs[i][0], arcs[i][1]);
        queue.enqueue(a);
    }
    Vector<Set<int>> sets;
    for (int i = 0; i < m.vertexNum(); i++) {
        Set<int> set;
        set.add(i);
        sets.add(set);
    }
	double length = 0;
    while (!queue.isEmpty()) {
        Arc a = queue.dequeueMax();
        int index1 = findSet(sets, a.start);
        int index2 = findSet(sets, a.end);
        if (index1 != index2) {
		    DrawLineBetween(getCoordFromVertex(m.getVertex(a.start)), getCoordFromVertex(m.getVertex(a.end)), "Red");
            sets[index1].unionWith(sets[index2]);
            sets.removeAt(index2);
			length += a.length;
			Pause(0.1);
        }
    }
	cout << "Minimal Spanning tree now displayed." << endl
		<< "Total network length is " << length << " miles." << endl;
}

int main()
{
	InitGraphics();
	SetWindowTitle("CS106 Pathfinder");
    cout << "This masterful piece of work is a graph extravaganza!" << endl
        << "The main attractions include a lovely visual presentation of the graph" << endl
        << "along with an implementation of Dijkstra's shortest path algorithm and" << endl
        << "the computation of a minimal spanning tree.  Enjoy!" << endl;
	MGraph m;
	string file_name;
	int choice = 1;
	while (true) {
		switch (choice) {
		case 1: {
			file_name = askForFile();
			InitGraphics();
			m.clear();
			buildFromFile(m, file_name);
			drawGraphVertexes(m);
			drawGraphArcs(m);
			break;
		}
		case 2: {
			int v1_index = askForClick(m, string("Click on starting location...  "));
			Vertex v1 = m.getVertex(v1_index);
			DrawFilledCircleWithLabel(getCoordFromVertex(v1), "Red", v1.name);
			int v2_index = askForClick(m, string("Click on ending location...  "));
			Vertex v2 = m.getVertex(v2_index);
			DrawFilledCircleWithLabel(getCoordFromVertex(v2), "Red", v2.name);
			cout << endl;
			Dijkstra(m, v1_index, v2_index);
			waitConfirm();
			drawGraphVertexes(m);
			drawGraphArcs(m);
			break;
		}
		case 3: {
			// there is not methods to clear the lines, so
			// clear all things and repaint without lines.
			InitGraphics();
			m.clear();
			buildFromFile(m, file_name);
			drawGraphVertexes(m);
            MST(m);
			waitConfirm();
			drawGraphVertexes(m);
			drawGraphArcs(m);
			break;
        }
		case 4:
			return 0;
		default:
			break;
		}
		choice = askForChoice();
	}
    return (0);
}