/* File: part2_generic_sort.cpp
 * ----------------------------
 * This file write a fully generic heap sorting function.
 *
 * Chao Wang Mon Oct 26 2020
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "vector.h"
#include "set.h"
#include "cmpfn.h"

/*
 * Constants used to generate random vector.
 */
const int RANDOM_INT_LOW = 0;
const int RANDOM_INT_HIG = 10;
const int RANDOM_STRING_SIZE_LOW = 1;
const int RANDOM_STRING_SIZE_HIG = 5;
const int RANDOM_SET_SIZE_LOW = 1;
const int RANDOM_SET_SIZE_HIG = 5;

/*
 * Function: Parent
 * Usage: p = Parent(i);
 * ---------------------
 * Returns the position of i's parent.
 */
int Parent(int i) {
	return (i-1)/2;
}

/*
 * Function: Left
 * Usage: l = Left(i);
 * -------------------
 * Returns the position of i's left child.
 */
int Left(int i) {
	return 2*i+1;
}

/*
 * Function: Right
 * Usage: r = Right(i);
 * --------------------
 * Returns the position of i's right child.
 */
int Right(int i) {
	return 2*i+2;
}

/*
 * Function template: MaxHeapify
 * Usage: MaxHeapify(v, heapSize, pos, cmpFn);
 * -------------------------------------------
 * Lets the value at v[pos] "float down" in the max-heap
 * so that the subtree rooted at index i obeys the max-heap
 * property.
 */
template <typename T>
void MaxHeapify(Vector<T> &v, int heapSize, int i, int (cmpFn)(T, T)) {
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l < heapSize && cmpFn(v[l], v[i]) == 1) {
		largest = l;
	} else {
		largest = i;
	}
	if (r < heapSize && cmpFn(v[r], v[largest]) == 1) {
		largest = r;
	}
	if (largest != i) {
		using std::swap;
		swap(v[i], v[largest]);
		MaxHeapify(v, heapSize, largest, cmpFn);
	}
}

/*
 * Function template: BuildMaxHeap
 * Usage: BuildMaxHeap(v, cmpFn);
 * ------------------------------
 * This function builds a max heap in v.
 */
template <typename T>
void BuildMaxHeap(Vector<T> &v, int (cmpFn)(T, T)) {
	for (int i = v.size()/2 - 1; i >= 0; i--) {
		MaxHeapify(v, v.size(), i, cmpFn);
	}
}

/*
 * Function template: Sort
 * Usage: Sort(v, cmpFn);
 * ----------------------
 * This function uses heap sort algorithm to sort vector v
 * based on cmpFn.
 */
template <typename T>
void Sort(Vector<T> &v, int (cmpFn)(T, T) = OperatorCmp) {
	// Heap sort
	BuildMaxHeap(v, cmpFn);
	int heapSize = v.size();
	using std::swap;
	for (int i = v.size()-1; i > 0; i--) {
		swap(v[0], v[i]);
		heapSize--;
		MaxHeapify(v, heapSize, 0, cmpFn);
	}
}

/*
 * Function: RandomT
 * Usage: RandomT(i);
 * ------------------
 * Changes i to a random int in [RANDOM_INT_LOW, RANDOM_INT_HIG].
 */
void RandomT(int &t) {
	t = RandomInteger(RANDOM_INT_LOW, RANDOM_INT_HIG);
}

/*
 * Function: RandomT
 * Usage: RandomT(ch);
 * -------------------
 * Changes ch to a random char in ['a', 'z'].
 */
void RandomT(char &t) {
	t = RandomInteger(0, 25) + 'a';
}

/*
 * Function: RandomT
 * Usage: RandomT(str);
 * --------------------
 * Changes str to a random string, whose size is
 * in [RANDOM_STRING_SIZE_LOW, RANDOM_STRING_SIZE_HIG],
 * whose elements is in ['a', 'z'].
 */
void RandomT(string &t) {
	int size = RandomInteger(RANDOM_STRING_SIZE_LOW, RANDOM_STRING_SIZE_HIG);
	t = "";
	for (int i = 0; i < size; i++) {
		t += (RandomInteger(0, 25) + 'a');
	}
}

/*
 * Function: RandomT
 * Usage: RandomT(set);
 * --------------------
 * Changes set to a random set<int>, whose size is
 * in [RANDOM_SET_SIZE_LOW, RANDOM_SET_SIZE_HIG],
 * whose elements is in [RANDOM_INT_LOW, RANDOM_INT_HIG].
 */
void RandomT(Set<int> &set) {
	int size = RandomInteger(RANDOM_SET_SIZE_LOW, RANDOM_SET_SIZE_HIG);
	for (int i = 0; i < size; i++) {
		set.add(RandomInteger(RANDOM_INT_LOW, RANDOM_INT_HIG));
	}
}

/*
 * Function template: GetRandomVector
 * Usage: Vector<T> vec = GetRandomVector<T>(size);
 * --------------------------------------=---------
 * This function randomly generates a vector of type T
 * whose size is specified by the parameter.
 */
template <typename T>
Vector<T> GetRandomVector(int size) {
	Vector<T> result;
	for (int i = 0; i < size; i++) {
		T tmp;
		RandomT(tmp);
		result.add(tmp);
	}
	return result;
}

/*
 * Function: StringSizeCmp
 * Usage: bigger = StringSizeCmp(s1, s2);
 * --------------------------------------
 * String comparison function sort a vector of strings
 * in order of increasing string length, breaking ties 
 * by alphabetical ordering. 
 */
int StringSizeCmp(string s1, string s2) {
	if (s1.size() == s2.size()) {
		for (int i = 0; i < s1.size(); i++) {
			if (s1[i] < s2[i]) {
				return -1;
			} else if (s1[i] > s2[i]) {
				return 1;
			}
		}
		return 0;
	} else if (s1.size() < s2.size()) {
		return -1;
	} else {
		return 1;
	}
}

/*
 * Function: Sum
 * Usage: sum = Sum(set);
 * ----------------------
 * Returns the sum of the elements in the set.
 */
int Sum(Set<int> &set) {
	int result = 0;
	Set<int>::Iterator itr = set.iterator();
	while (itr.hasNext()) {
		result += itr.next();
	}
	return result;
}

/*
 * Function: SetSumCmp
 * Usage: bigger = SetSumCmp(s1, s2);
 * ----------------------------------
 * Set comparison function sorts a Vector of 
 * Set<int> in order of increasing sum.
 */
int SetSumCmp(Set<int> set1, Set<int> set2) {
	int sum1 = Sum(set1);
	int sum2 = Sum(set2);
	if (sum1 == sum2) {
		return 0;
	} else if (sum1 < sum2) {
		return -1;
	} else {
		return 1;
	}
}

/*
 * Function template: Print
 * Usage: Print(vec);
 * ------------------
 * This function prints elements in vec seperated by table.
 * There should be an overloaded version operator<< for the
 * type of vec's elements.
 */
template <typename T>
void Print(Vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
		cout << '\t' << v[i];
	}
	cout << endl << endl;
}

/*
 * Operator Overloading: operator<<
 * Usage: os << set;
 * -----------------
 * This function overloads the operator<< for Set<int>.
 */
ostream &operator<<(ostream &os, Set<int> set) {
	Set<int>::Iterator itr = set.iterator();
	while (itr.hasNext()) {
		os << itr.next() << ' ';
	}
	os << endl;
	return os;
}

int main ()
{
	Randomize();
	// random ints to test
	Vector<int> ivec = GetRandomVector<int>(5);
	Print(ivec);
	Sort(ivec);
	Print(ivec);
	// random chars to test
	Vector<char> cvec = GetRandomVector<char>(5);
	Print(cvec);
	Sort(cvec);
	Print(cvec);
	// random strings to test
	Vector<string> svec = GetRandomVector<string>(5);
	Print(svec);
	Sort(svec, StringSizeCmp);
	Print(svec);
	// random sets to test
	Vector<Set<int>> setvec = GetRandomVector<Set<int>>(5);
	Print(setvec);
	Sort(setvec, SetSumCmp);
	Print(setvec);
	return 0;
}
