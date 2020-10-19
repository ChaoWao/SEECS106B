/*
 * Program: part4_cellphone.cpp
 * ----------------------------
 * Program used to print all words from the lexicon
 * that can be formed by extending the given digit sequence.
 *
 * Chao Wang Sun Oct 18 2020
 */
#include <iostream>
#include <string>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"
#include "lexicon.h"

/*
 * Function: ListPrefix
 * Usage: ListPrefix(digits, prefix, prefixs);
 * ------------------------------------------------------------
 * This fucntion translate digits to avaliable prefixs based on
 * existing prefix, and add result to vector prefixs.
 * Initially, you may pass prefix = "" and an empty vector prefixs.
 */
void ListPrefix(string digits, string prefix, Vector<string> &prefixs) {
	if (digits.length() == 0) {
		prefixs.add(prefix);
		return;
	}
	char ch = digits[0];
	digits.erase(0, 1);
	switch (ch) {
		case '2':
			ListPrefix(digits, prefix+"a", prefixs);
			ListPrefix(digits, prefix+"b", prefixs);
			ListPrefix(digits, prefix+"c", prefixs);
			break;
		case '3':
			ListPrefix(digits, prefix+"d", prefixs);
			ListPrefix(digits, prefix+"e", prefixs);
			ListPrefix(digits, prefix+"f", prefixs);
			break;
		case '4':
			ListPrefix(digits, prefix+"g", prefixs);
			ListPrefix(digits, prefix+"h", prefixs);
			ListPrefix(digits, prefix+"i", prefixs);
			break;
		case '5':
			ListPrefix(digits, prefix+"j", prefixs);
			ListPrefix(digits, prefix+"k", prefixs);
			ListPrefix(digits, prefix+"l", prefixs);
			break;
		case '6':
			ListPrefix(digits, prefix+"m", prefixs);
			ListPrefix(digits, prefix+"n", prefixs);
			ListPrefix(digits, prefix+"o", prefixs);
			break;
		case '7':
			ListPrefix(digits, prefix+"p", prefixs);
			ListPrefix(digits, prefix+"q", prefixs);
			ListPrefix(digits, prefix+"r", prefixs);
			ListPrefix(digits, prefix+"s", prefixs);
			break;
		case '8':
			ListPrefix(digits, prefix+"t", prefixs);
			ListPrefix(digits, prefix+"u", prefixs);
			ListPrefix(digits, prefix+"v", prefixs);
			break;
		case '9':
			ListPrefix(digits, prefix+"w", prefixs);
			ListPrefix(digits, prefix+"x", prefixs);
			ListPrefix(digits, prefix+"y", prefixs);
			ListPrefix(digits, prefix+"z", prefixs);
			break;
		default :
			break;
	}
}

/*
 * Function: ListCompletionsBasedOnPrefix
 * Usage: ListCompletionsBasedOnPrefix(prefix, lexicon);
 * -----------------------------------------------------
 * This fucntion uses prefix to generate all possible word in the
 * lexicon.
 */
void ListCompletionsBasedOnPrefix(string prefix, Lexicon &lex) {
	if (lex.containsWord(prefix)) {
		cout << prefix << endl;
	}
	if (!lex.containsPrefix(prefix)) {
		return;
	}
	for (char ch = 'a'; ch <= 'z'; ch++) {
		ListCompletionsBasedOnPrefix(prefix+ch, lex);
	}
}

/*
 * Function: ListCompletions
 * Usage: ListCompletions(digits, lexicon);
 * ----------------------------------------
 * This fucntion firstly calls ListPrefix to get all possible prefix,
 * and then calls ListCompletionsBasedOnPrefix to generate all possible
 * words.
 */
void ListCompletions(string digits, Lexicon &lex) {
	Vector<string> prefixs;
	ListPrefix(digits, "", prefixs);
	for (int i = 0; i < prefixs.size(); i++) {
		ListCompletionsBasedOnPrefix(prefixs[i], lex);
	}
}

void testListCompletions () {
	Lexicon lex("lexicon.dat");
	while (true) {
		cout << "Enter digits [2-9], or non-digits or [0-1] to quit: ";
		string digits = GetLine();
		for (int i = 0; i < digits.size(); i++) {
			if (digits[i] <= '1' || digits[i] > '9') {
				cout << "Quiting..." << endl;
				return;
			}
		}
		ListCompletions(digits, lex);
		cout << endl;
	}
}

int main() {
	testListCompletions();
	return 0;
}