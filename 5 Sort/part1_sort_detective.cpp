/* File: part1_sort_detective.cpp
 * ------------------------------
 * This file tests the five MysterySort function
 * and gives my guess accroding to the results.
 *
 * Chao Wang Mon Oct 26 2020
 */

#include <iostream>
#include <ctime>
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "vector.h"
#include "mysterysort.h"

/*
 * If you stop in the middle and see the result,
 * then this problem is not much interesting, so
 * ignore the parameter time.
 * Before C++ 11, I don't know if there is a 'bind'
 * function or somthing, so I just write five new
 * functions.
 */
void Sort1(Vector<int> &v) {
	MysterySort1(v);
}

void Sort2(Vector<int> &v) {
	MysterySort2(v);
}

void Sort3(Vector<int> &v) {
	MysterySort3(v);
}

void Sort4(Vector<int> &v) {
	MysterySort4(v);
}

void Sort5(Vector<int> &v) {
	MysterySort5(v);
}

/*
 * I have 5 sorts to test and store them in an array.
 */
const int numSorts = 5;
void (*f[])(Vector<int> &) = {Sort1, Sort2, Sort3, Sort4, Sort5};

/*
 * Function: GetAscendingVector
 * Usage: GetAscendingVector(size);
 * --------------------------------
 * This function returns a ascending vector from 0 to size-1.
 */
Vector<int> GetAscendingVector(int size) {
	Vector<int> result;
	for (int i = 0; i < size; i++) {
		result.add(i);
	}
	return result;
}

/*
 * Function: GetRandomVector
 * Usage: GetRandomVector(size);
 * -----------------------------
 * This function returns a random vector,
 * whose elements is in [0, size-1],
 * whose size is specified by the parameter.
 */
Vector<int> GetRandomVector(int size) {
	Vector<int> result;
	for (int i = 0; i < size; i++) {
		result.add(RandomInteger(0, size-1));
	}
	return result;
}

/*
 * Function: GetRuntime
 * Usage: GetRuntime(f, v, times);
 * -------------------------------
 * This function returns the average runtime got by
 * run times function f whose argument is v.
 */
double GetRuntime(void (*f)(Vector<int> &), Vector<int> &v, int times) {
	double result = 0;
	for (int i = 0; i < times; i++) {
		double start = double(clock()) / CLOCKS_PER_SEC;
		f(v);
		double finish = double(clock()) / CLOCKS_PER_SEC;
		result += finish - start;
	}
	return result / times;
}

/*
 * Function: TestAll
 * Usage: result = TestAll(test_size);
 * --------------------------
 * This function test all the five MysterySort on different
 * sizes specified by test_size vector, and uses both ascending
 * vector as argument and random vector as argument.
 * ATTENTION :: result is a vector (different sort functions)
 * of vector ([0] is ascending and [1] is random)
 * of vector (different vector size)
 * of double (runtime).
 */
Vector<Vector<Vector<double>>> TestAll(Vector<int> &test_size) {
	Vector<Vector<Vector<double>>> result;
	for (int i = 0; i < numSorts; i++) {
		Vector<Vector<double>> single_f_result;
		Vector<double> single_f_ascending_result;
		for (int j = 0; j < test_size.size(); j++) {
			double runtime = GetRuntime(f[i], GetAscendingVector(test_size[j]), test_size[test_size.size()-1]/test_size[j]);
			single_f_ascending_result.add(runtime);
		}
		single_f_result.add(single_f_ascending_result);
		Vector<double> single_f_random_result;
		for (int j = 0; j < test_size.size(); j++) {
			double runtime = GetRuntime(f[i], GetRandomVector(test_size[j]), test_size[test_size.size()-1]/test_size[j]);
			single_f_random_result.add(runtime);
		}
		single_f_result.add(single_f_random_result);
		result.add(single_f_result);
	}
	return result;
}

/*
 * Function template: Print
 * Usage: Print(vec);
 * -------------------------------------
 * This function prints elements in vec seperated by table.
 * There should be an overloaded version operator<< for the
 * type of vec's elements.
 */
template <typename T>
void Print(Vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << '\t';
	}
	cout << endl << endl;
}

/*
 * Function : Print
 * Usage: Print(result);
 * -------------------------------------
 * This function prints the result by calling Print
 * template and formatting the result.
 */
void Print(Vector<Vector<Vector<double>>> &result) {
	for (int i = 0; i < result.size(); i++) {
		cout << "MysterySort" << i+1 << ":" << endl;
		cout << "Ascending Result:" << endl;
		Print(result[i][0]);
		cout << "Random Result:" << endl;
		Print(result[i][1]);
	}
}

int main ()
{
	Vector<int> test_size;
	test_size.add(100);
	test_size.add(1000);
	test_size.add(10000);
	test_size.add(100000);
	cout << "Test Sizes:" << endl;
	Print(test_size);
	Vector<Vector<Vector<double>>> test_result = TestAll(test_size);
	Print(test_result);

	return 0;
}

/* After running, I got
 * Test sizes:
 * 100	1000	10000	100000
 * MysterySort1:
 * Ascending:
 * 0	0.001	0.001	0.001
 * Random:
 * 0	0.002	0.1452	139.991
 * MysterySort2:
 * Ascending:
 * 0	0.008	0.831	85.183
 * Random:
 * 0	0.008	0.765	0.07
 * MysterySort3:
 * Ascending:
 * 0	0.0009	0.012	0.14
 * Random:
 * 0	0.0008	0.012	0.181
 * MysterySort4:
 * Ascending:
 * 0	0.218	2.198	218.874
 * Random:
 * 0	0.218	2.182	220.527
 * MysterySort5:
 * Ascending:
 * 0	0		0.001	0
 * Random:
 * 0	0.0003	0.2995	306.44
 */
/* As you can see it, 
 * 1. ascending ~= random: MysterySort3, MysterySort4
 * and 3 <<= 4, so MysterySort3 is MergeSort and MysterySort4 is SelectionSort
 * 2. ascending >>= random: MysterySort2, so this is QuickSort
 * 3. ascending <<= random: MysterySort1, MysterySort5
 * and when random MysterySort1 < MysterySort5
 * so MysterySort1 is InsertionSort and MysterySort5 is BubbleSort
 */