/*
 * Program: part1.cpp
 * --------------------
 * Program used to randomly generate strings based on Markov model.
 *
 * Chao Wang San Oct 4 2020
 */

/*
 * Uh ohh... After I finished this program, I found this requirement
 * of the assignment:
 *		You will be creating and messaging lots of objects, but will 
 *		write your code in the procedural style, starting with the 
 *		main function and decomposing into ordinary global functions.
 * However, part 1 is encapsluted to Markov class, which is a OO styel.
 * But, I decided to keep it since I think OO is good too.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "map.h"
#include "vector.h"

/*
 * Class: Markov
 * ----------
 * This interface defines a class that used to analyze and generate
 * texts accroding to markov model.
 * The order of Markov model can be set in two ways.
 * 1. Markov m(order);
 * 2. Markov m; m.setorder(order);
 * when you call setorder, it will clear the old analyze result and
 * need to analyze texts before generating.
 */
class Markov {
public:

	/*
	 * Constructor: Markov
	 * Usage: Markov m;
	 *	      Markov m(3);
	 *        Markov *mp = new Markov;
	 * -----------------------------------------------
	 * The constructor initializes a new Markov model. The optional 
	 * argument is its initial order.  If not specified, it is 
	 * initialized with default number 1.
     */
	explicit Markov(int k = 1);

	/*
	 * Member function: setorder
	 * Usage: success = m.setorder(k);
	 * -------------------------------
	 * This member function clears old analyzing results in m,
	 * set analyzed to false and set order to k if k is in [1, 10].
	 */
	bool setorder(int k);

	/*
	 * Member function: getorder
	 * Usage: order = m.getorder();
	 * ----------------------------
	 * This member function returns the order of the Markov model.
	 */
	int getorder() { return order; }

	/*
	 * Member function: analyze
	 * Usage: success = m.analyze(in);
	 * -------------------------------
	 * This member function analyze the istream (in) based on the order.
	 * Also set analyzed flag to true.
	 */
	bool analyze(istream &in);

	/*
	 * Member function: analyze
	 * Usage: success = m.generate(out, n);
	 * ------------------------------------
	 * This member function generates string, which length is n,
	 * based on m, when analyzed is set. The string is to ostream (out).
	 */
	bool generate(ostream &out, int n);
private:
	int order;
	bool analyzed;
	Map<Vector<char>> m;
};

Markov::Markov(int k) {
	m.clear();
	analyzed = false;
	if (k >= 1 && k <= 10) {
		order = k;
	} else {
		order = 1;
	}
}

bool Markov::setorder(int k) {
	if (k >= 1 && k <= 10) {
		m.clear();
		analyzed = false;
		order = k;
		return true;
	}
	return false;
}

bool Markov::analyze(istream &in) {
	cout << "Analzying... please wait." << endl;
	string s = "";
	for (int i = 0; i < order; i++) {
		char ch = in.get();
		if (in.fail()) {
			break;
		}
		s = s + ch;
	}
	char ch = in.get();
	if (in.fail() || s.length() != order) {
		return false;
	}
	// add each existence of char after string to (string -> vector<char>) map
	while (!in.fail()) {
		m[s].add(ch);
		s = s.substr(1, order-1) + ch;
		ch = in.get();
	}
	cout << endl;
	analyzed = true;
	return true;
}

bool Markov::generate(ostream &out, int n) {
	if (n < order || analyzed == false) return false;
	// find (the first) most frequent sequence
	string seed = "";
	Map<Vector<char>>::Iterator itr = m.iterator();
	while (itr.hasNext()) {
		string key = itr.next();
		if (seed == "") seed = key;
		else if (m[seed].size() < m[key].size()) seed = key;
	}
	// output the most frequent sequence
	out << seed;
	n -= order;
	// randomly generate other character based on analyzed map m
	Randomize();
	while (n--) {
		if (!m.containsKey(seed)) {
			// if there are no characters to choose, stop writing early
			break;
		}
		char ch = m[seed][RandomInteger(0, m[seed].size()-1)];
		out << ch;
		seed = seed.substr(1, order-1) + ch;
	}
	return true;
}

void random_writer ()
{
	// asking for file name
	string file_name;
	fstream in;
	while (true) {
		cout << "Please enter filename containing source text: ";
		file_name = GetLine();
		in.open(file_name.c_str());
		if (in.fail()) {
			in.clear();
			cout << "Could not open file named \"" << file_name << "\". Please try again." << endl;
		} else {
			break;
		}
	}
	// asking for order of Markov model
	int order = 0;
	while (true) {
		cout << "What order of analysis? (a number from 1 to 10): ";
		order = GetInteger();
		if (order < 1 || order > 10) {
			cout << "Try again." << endl;
		} else {
			break;
		}
	}
	// initialize Markov model
	Markov m(order);
	// analyze
	if (m.analyze(in)) {
		// generate
		cout << endl;
		if (!m.generate(cout, 2000)) {
			// should not be here, but
			cout << "Generating failed, please check." << endl;
		}
		cout << endl;
	} else {
		// should not be here, but
		cout << "Analyzing failed, please check." << endl;
	}
}