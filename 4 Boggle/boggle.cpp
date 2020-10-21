/* File: boggle.cpp
 * ----------------
 * This file contains the main function where program starts.
 * Compared to the given program, 
 * 1. it does not support music.
 * 2. it does not output so much empty line.
 *
 * Chao Wang Thu Oct 20 2020
 */
 
#include "genlib.h"
#include "simpio.h"
#include <iostream>
#include <cstdlib>
#include "extgraph.h"
#include "random.h"
#include "vector.h"
#include "gboggle.h"
#include "lexicon.h"

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};
 
string BigBoggleCubes[25]  = 
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
"BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
"DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

Lexicon lex("lexicon.dat");

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
	 << "creating a grid of letters on which you try to form words. You go first, " 
	 << "entering all the words you can find that are formed by tracing adjoining " 
	 << "letters. Two letters adjoin if they are next to each other horizontally, " 
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;
	
    cout << "\nHit return when you're ready...";
    GetLine();
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: StringBeginWith
 * Usage: flag = StringBeginWith(s, 'y');
 * -------------------------------------
 * This function return true if s begins with the character.
 */
bool StringBeginWith(string s, char ch)
{
	if (s.size() > 0 && s[0] == ch) return true;
	return false;
}

/*
 * Function: GetYesOrNo
 * Usage: flag = GetYesOrNo(info);
 * -------------------------------------
 * This function prompts info and gets a yes or no 
 * from the user, and re-try if the user gives an 
 * irrelevent answer.
 */
bool GetYesOrNo(string prompt)
{
	while (true) {
		cout << prompt;
		string s = GetLine();
		if (StringBeginWith(s, 'y')) return true;
		if (StringBeginWith(s, 'n')) return false;
		cout << "Please answer yes or no." << endl;
	}
	// should never be here, but...
	return true;
}

/*
 * Function: AskForInstructions
 * Usage: flag = AskForInstructions();
 * -----------------------------------
 * This function prompt information to ask the user if he
 * needs instructions.
 */
bool AskForInstructions()
{
	string info = "Do you need instructions? ";
	return GetYesOrNo(info);
}

/*
 * Function: AskForBoggleSize
 * Usage: flag = AskForBoggleSize();
 * -----------------------------------
 * This function prompt information to ask the user if he
 * wants a big boggle.
 */
bool AskForBoggleSize()
{
	string info = "You can choose standard Boggle (on 4x4 grid) or Big Boggle (5x5).\nWould you like Big Boggle? ";
	return GetYesOrNo(info);
}

/*
 * Function: AskForConfiguration
 * Usage: s = AskForConfiguration(true);
 * -----------------------------------
 * This function prompt information to ask the user if he
 * wants user-defined configurations. If yes, this function
 * will re-try until it gets a correct size string based on
 * the parameter big_boggle.
 */
string AskForConfiguration(bool big_boggle)
{
	string info = "I'll give you a chance to set up the board to your specification.\n"
					"This makes it easier to confirm your boggle program is working.\n"
					"Do you want to force the board configuration? ";
	if (!GetYesOrNo(info)) return "";
	int min_length = big_boggle ? 25 : 16;
	cout << "Enter a 16-character string to identify which letters you want on the cubes.\n"
			<< "The first 4 letters are the cubes on the top row from left to right\n"
			<< "next 4 letters are the second row, etc." << endl;
	while (true) {
		cout << "Enter a string: ";
		string s = GetLine();
		if (s.size() >= min_length) return s;
		cout << "String must include " << min_length << " characters! Try again: ";
	}
	// should never be here, but...
	return "";
}

/*
 * Function: ShakeCubes
 * Usage: ShakeCubes(5, 5, BigBoggleCubes);
 * -----------------------------------
 * This function shakes the cubes accroding to number
 * of rows and columns.
 */
void ShakeCubes(int numRows, int numCols, string *pCubes)
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			int randomRow = RandomInteger(row, numRows-1);
			int randomCol = RandomInteger(col, numCols-1);
			string temp = *(pCubes + row*numRows + col);
			*(pCubes + row*numRows + col) = *(pCubes + randomRow*numRows + randomCol);
			*(pCubes + randomRow*numRows + randomCol) = temp;
		}
	}
}

/*
 * Function: GetCube
 * Usage: cube = GetCube(conf, true);
 * -----------------------------------
 * This function randomly generates a cube, standard or big
 * accroding to the parameter big_boggle if conf == "".
 * Otherwise, generates accroding to conf.
 */
Vector<string> GetCube(string conf, bool big_boggle)
{
	Vector<string> result;
	int numRows = big_boggle ? 5 :4;
	int numCols = numRows;
	if (conf.size() >= numRows*numCols) {
		int k = 0;
		for (int i = 0; i < numRows; i++) {
			result.add("");
			for (int j = 0; j < numCols; j++) {
				result[i] += conf[k++];
			}
		}
	} else {
		string *pCubes = big_boggle ? StandardCubes : BigBoggleCubes;
		ShakeCubes(numRows, numCols, pCubes);
		for (int i = 0; i < numRows; i++) {
			result.add("");
			for (int j = 0; j < numCols; j++) {
				result[i] += (*(pCubes+i))[RandomInteger(0, 5)];
			}
		}
	}
	return result;
}

/*
 * Function: ShowCube
 * Usage: ShowCube(cube);
 * ----------------------
 * This function show the cube on the graphic windows.
 */
void ShowCube(Vector<string> &cube)
{
	int numRows = cube.size();
	int numCols = cube[0].size();
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			LabelCube(i, j, cube[i][j]);
		}
	}
}

/*
 * Function: NewWord
 * Usage: flag = NewWord("lean", existing_words);
 * ----------------------
 * This function returns true if the word i has 
 * not already been included in words.
 */
bool NewWord(string word, Vector<string> &words)
{
	for (int i = 0; i < words.size(); i++) {
		if (words[i] == word) return false;
	}
	return true;
}

/*
 * Function: SameChar
 * Usage: flag = SameChar('a', 'A');
 * ----------------------
 * This function returns true if the two char are the same
 * char when ignoring case.
 */
bool SameChar(char a, char b) {
	if (a == b || a+'A' == b+'a' || a+'a' == b+'A') {
		return true;
	}
	return false;
}

/*
 * Function: WordOnCube
 * Usage: path = WordOnCube(-1, -1, "lean", cube, walked);
 * ----------------------
 * This function recursively walks on the cube based on walked flags
 * which indicates whether one square is walked and current position.
 * If it finds the word, return a full path; otherwise return empty
 * vector.
 * Initially, set the walked vector size equals the cube vector
 * size and set its content '0'.
 */
Vector<Vector<int> > WordOnCube(int row, int col, string word, Vector<string> &cube, Vector<string> &walked)
{
	Vector<Vector<int> > result;
	if (word == "") {
		return result;
	}
	if (row == -1 && col == -1) {
		// init situation
		for (int i = 0; i < cube.size(); i++) {
			for (int j = 0; j < cube[0].size(); j++) {
				if (SameChar(word[0], cube[i][j])) {
					word.erase(0, 1);
					Vector<Vector<int>> one_try = WordOnCube(i, j, word, cube, walked);
					if (word == "" || one_try.size() != 0) {
						Vector<int> position;
						position.add(i);
						position.add(j);
						one_try.insertAt(0, position);
						return one_try;
					}
					word.insert(0, string(1, cube[i][j]));
				}
			}
		}
	} else {
		// recursive situations
		walked[row][col] = '1';
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (row+i < 0 || row+i >= cube.size() || col+j < 0 || col+j >= cube[0].size()) {
					continue;
				}
				if (SameChar(word[0], cube[row+i][col+j]) && walked[row+i][col+j] != '1') {
					word.erase(0, 1);
					Vector<Vector<int>> one_try = WordOnCube(row+i, col+j, word, cube, walked);
					if (word == "" || one_try.size() != 0) {
						Vector<int> position;
						position.add(row+i);
						position.add(col+j);
						one_try.insertAt(0, position);
						return one_try;
					}
					word.insert(0, string(1, cube[row+i][col+j]));
				}
			}
		}
	}
	return result;
}

/*
 * Function: ClearWalked
 * Usage: walked = cube; ClearWalked(cube);
 * ----------------------
 * This function clear walked to '0's. This function
 * often used after walked = cube.
 */
void ClearWalked(Vector<string> &walked) {
	for (int i = 0; i < walked.size(); i++) {
		for (int j = 0; j < walked[i].size(); j++) {
			walked[i][j] = '0';
		}
	}
}

/*
 * Function: HighlightPath
 * Usage: HighlightPath(path);
 * ----------------------
 * This function highlights the path representing
 * the word user found.
 */
void HighlightPath(Vector<Vector<int>> &path) {
	for (int i = 0; i < path.size(); i++) {
		HighlightCube(path[i][0], path[i][1], true);
	}
	Pause(0.5);
	for (int i = 0; i < path.size(); i++) {
		HighlightCube(path[i][0], path[i][1], false);
	}
}

/*
 * Function: UserTurn
 * Usage: words = UserTurn(cube);
 * ----------------------
 * This function asks the user to find word until they
 * input an empty line to finish.
 */
Vector<string> UserTurn(Vector<string> &cube)
{
	Vector<string> words;
	while (true) {
		cout << "Enter a word: ";
		string s = GetLine();
		if (s.size() == 0) break;
		else if (s.size() < 4) {
			cout << "I'm sorry, but we have our standards.\n"
				<< "That word doesn't meet the minimum word length." << endl;
		} else if (!lex.containsWord(s)) {
			cout << "You can't make that word!" << endl;
		} else if (!NewWord(s, words)) {
			cout << "You've already guessed that!" << endl;
		} else {
			Vector<string> walked = cube;
			ClearWalked(walked);
			Vector<Vector<int> > path = WordOnCube(-1, -1, s, cube, walked);
			if (path.size() == 0) {
				cout << "You can't make that word!" << endl;
			} else {
				HighlightPath(path);
				RecordWordForPlayer(s, Human);
				words.add(s);
			}
		}
	}
	return words;
}

/*
 * Function: SearchOnCube
 * Usage: SearchOnCube(int row, int col, "lean", cube, walked, words);
 * ----------------------
 * This function recursively seraches on the cube based on walked flags
 * which indicates whether one square is walked and current position.
 * Initially, set the walked vector size equals the cube vector
 * size and set its content '0'. words contains the words user found.
 */
void SearchOnCube(int row, int col, string prefix, Vector<string> &cube, Vector<string> &walked, Vector<string> &words)
{
	if (prefix.size() >= 4 && lex.containsWord(prefix) && NewWord(prefix, words)) {
		RecordWordForPlayer(prefix, Computer);
		words.add(prefix);
	}
	if (!lex.containsPrefix(prefix)) return;
	walked[row][col] = '1';
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (row+i < 0 || row+i >= cube.size() || col+j < 0 || col+j >= cube[0].size()) {
				continue;
			}
			if (walked[row+i][col+j] != '1') {
				SearchOnCube(row+i, col+j, prefix+cube[row+i][col+j], cube, walked, words);
			}
		}
	}
	walked[row][col] = '0';
}

/*
 * Function: ComputerTurn
 * Usage: ComputerTurn(cube, words);
 * ----------------------
 * This function represent the computer player to find
 * word that human had not found.
 */
void ComputerTurn(Vector<string> &cube, Vector<string> &words)
{
	Vector<string> walked = cube;
	ClearWalked(walked);
	for (int i = 0; i < cube.size(); i++) {
		for (int j = 0; j < cube[i].size(); j++) {
			SearchOnCube(i, j, string(1, cube[i][j]), cube, walked, words);
		}
	}
}

/*
 * Function: AskForAnotherTurn
 * Usage: flag = AskForAnotherTurn();
 * -----------------------------------
 * This function prompt information to ask the user if he
 * wants another turn.
 */
bool AskForAnotherTurn()
{
	string info = "Would you like to play again? ";
	return GetYesOrNo(info);
}

int main()
{
	SetWindowSize(9, 5);
	InitGraphics();
	Randomize();
	Welcome();
	if (AskForInstructions()) {
		GiveInstructions();
	}
	bool big_boggle = AskForBoggleSize();
	DrawBoard(big_boggle ? 5 : 4, big_boggle ? 5 : 4);
	while (true) {
		string conf = AskForConfiguration(big_boggle);
		Vector<string> cube = GetCube(conf, big_boggle);
		ShowCube(cube);
		Vector<string> words = UserTurn(cube);
		ComputerTurn(cube, words);
		if (!AskForAnotherTurn()) {
			exit(EXIT_SUCCESS);
		}
		InitGraphics();
		DrawBoard(big_boggle ? 5 : 4, big_boggle ? 5 : 4);
	}
	return 0;
}