/*
 * File: pqheap.cpp
 * ----------------
 * This file implements the priority queue class as a heap
 * of integers.  This is hard to understand for people but
 * brings high overall performance.
 *
 * Chao Wang Tue Nov 3 2020
 */
 
#include "pqueue.h"
#include "genlib.h"
#include <iostream>
#include <limits>

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqheap looks like this:
 *
 *	int Parent(int i) { return (i-1)/2; }
	int Left(int i) { return 2*i+1; }
	int Right(int i) { return 2*i+2; }
	void increaseKey(int i, int key);
	void maxHeapify(int i);
	Vector<int> heap;
 */


PQueue::PQueue()
{
}

PQueue::~PQueue()
{
}

bool PQueue::isEmpty()
{
    return (heap.isEmpty());  
}

int PQueue::size()
{
	return (heap.size());
}

/* Implementation notes: increaseKey
 * ---------------------------------
 * increaseKey traverses a simple path from this node (i) toward
 * the root to find a proper place for the newly increased key.
 */
void PQueue::increaseKey(int i, int key) {
	if (key < heap[i]) {
		Error("new key is smaller than current key");
	}
	heap[i] = key;
	while (heap[Parent(i)] < heap[i]) {
		using std::swap;
		swap(heap[i], heap[Parent(i)]);
		i = Parent(i);
		if (i == 0) break;
	}
}

/* Implementation notes: enqueue
 * -----------------------------
 * Since we're keeping the vector as a heap, we just append minus infinity
 * to the end. And then increase that key to the newValue.
 */
void PQueue::enqueue(int newValue)
{
	heap.add(numeric_limits<int>::min());
	increaseKey(heap.size()-1, newValue);
}

/*
 * Implementation notes: maxHeapify
 * --------------------------------
 * Lets the value at v[pos] "float down" in the max-heap
 * so that the subtree rooted at index i obeys the max-heap
 * property.
 */
void PQueue::maxHeapify(int i) {
	int heapSize = heap.size();
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l < heapSize && heap[l] > heap[i]) {
		largest = l;
	} else {
		largest = i;
	}
	if (r < heapSize && heap[r] > heap[largest]) {
		largest = r;
	}
	if (largest != i) {
		using std::swap;
		swap(heap[i], heap[largest]);
		maxHeapify(largest);
	}
}

/* Implementation notes: dequeueMax
 * --------------------------------
 * Since we're keeping the vector as a heap, we just return the root
 * to be the largest element.  Then, we remove it from heap and matain
 * the heap.
 */
int PQueue::dequeueMax()
{	
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
		
	int maxValue = heap[0];
	heap[0] = heap[heap.size()-1];
	heap.removeAt(heap.size()-1);
	maxHeapify(0);
	return maxValue;
}
		
int PQueue::bytesUsed() 
{
	return sizeof(*this) + heap.bytesUsed();
}


string PQueue::implementationName()
{
	return "heap";
}

void PQueue::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << heap.size() << " entries" << endl;
	for (int i = 0; i < heap.size(); i++) 
		cout << heap[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

