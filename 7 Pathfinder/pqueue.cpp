/*
 * File: pqueue.cpp
 * ----------------
 * This file implements the priority queue class template as a vector
 * of type T stored in no particular order.  This makes it easy
 * enqueue new elements, but hard to dequeue the max (have to search for it).
 *
 * Chao Wang, Thu Nov 5 2020
 */
 
#include "genlib.h"
#include <iostream>

/* Implementation notes: PQueue class
 * ----------------------------------
 */

template <typename T>
PQueue<T>::PQueue(int (cmp)(T, T))
{
	cmpFn = cmp;
}

template <typename T>
PQueue<T>::~PQueue()
{
}

template <typename T>
bool PQueue<T>::isEmpty()
{
    return (entries.isEmpty());  
}

template <typename T>
int PQueue<T>::size()
{
	return (entries.size());
}


/* Implementation notes: enqueue
 * -----------------------------
 * Since we're keeping the vector in no particular order, we just append this
 * new element to the end.  It's the easiest/fastest thing to do.
 */
template <typename T>
void PQueue<T>::enqueue(T newValue)
{
	entries.add(newValue);
}


/* Implementation notes: dequeueMax
 * --------------------------------
 * Since we're keeping the vector in no particular order, we have to search to
 * find the largest element.  Once found, we remove it from the vector and
 * return that value.
 */
template <typename T>
T PQueue<T>::dequeueMax()
{	
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
		
	int maxIndex = 0;	// assume first element is largest until proven otherwise
	T maxValue = entries[0];
	for (int i = 1; i < entries.size(); i++) {
		if (cmpFn(entries[i], maxValue) == 1) {
			maxValue = entries[i];
			maxIndex = i;
		}
	}
	entries.removeAt(maxIndex);	// remove entry from vector
	return maxValue;
}

template <typename T>
int PQueue<T>::bytesUsed() 
{
	return sizeof(*this) + entries.bytesUsed();
}

template <typename T>
string PQueue<T>::implementationName()
{
	return "unsorted vector";
}

template <typename T>
void PQueue<T>::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << entries.size() << " entries" << endl;
	for (int i = 0; i < entries.size(); i++) 
		cout << entries[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

