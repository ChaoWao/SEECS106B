/*
 * File: pqchunklist.cpp
 * ------------------
 * This file implements the priority queue class as a sorted chunklist
 * This trades off the advantages of vector and sorted list.
 *
 * Chao Wang Wen Oct 28 2020
 */
 
#include "pqueue.h"
#include "genlib.h"
#include <iostream>
#include <new>

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqchunklist looks like this:
 *
 *	static const unsigned MaxElemsPerBlock = 4;
	struct Block {
		int size;
		int value[MaxElemsPerBlock];
		Block *next;
	};
	Block *head;
 */


/* Implementation notes: constructor
 * ---------------------------------
 * We do not have a dummy cell, since it really won't help us much.
 * When the head is NULL, the pqueue is empty.
 */
PQueue::PQueue()
{
    head = NULL;
}

PQueue::~PQueue()
{
    while (head != NULL) {
    	Block *next = head->next;
    	delete head;
    	head = next;
    }
}

bool PQueue::isEmpty()
{
    return (head == NULL);  
}

/* Implementation notes: size
 * --------------------------
 * This version doesn't cache the number of entries, so we must traverse the list to count.
 */
int PQueue::size()
{
    int count = 0;
    for (Block *cur = head; cur != NULL; cur = cur->next)
    	count += cur->size;
    return count;
}


/* Implementation notes: enqueue
 * -----------------------------
 * We have to search to find the proper position, which needs a lot of
 * effort to understand. We use two pointers to find the position where
 * new value is between prev's max value and cur's max value.
 * As a sorted chunklist,
 * 1. If we found such a prev and prev's size is less than the max number
 * a bank can keep, we insert the new value to prev's sorted values.
 * 2. If we found such a prev and prev's size is already the max number,
 * we need a new bank to store values. AND ATTENTION HERE, I do not want
 * to split a new bank to two banks, both keeping half values. I use the
 * strategy that let those values who is greater than the new value in the
 * new bank, who is no greater in the old bank. This strategy minimizes the
 * number values are moved.
 * 3. If we cannot found such prev and cur exists, we insert to cur if we
 * can, otherwise we create a new bank using the same strategy described in 2.
 * 4. If cur does not exists too, which means head is null, we create a
 * new bank for head.
 */
void PQueue::enqueue(int newValue)
{
 	Block *cur, *prev;
 	
 	for (prev = NULL, cur = head; cur != NULL; prev=cur, cur = cur->next) {
 		if (newValue > cur->value[0]) break;
 	}
	if (prev) {
		int i = 0;
		while (i < prev->size && newValue <= prev->value[i]) {
			i++;
		}
		if (prev->size == MaxElemsPerBlock) {
			if (i == MaxElemsPerBlock) {
				Block *newOne = new Block;
				newOne->size = 0;
				newOne->value[newOne->size++] = newValue;
				newOne->next = cur;
				prev->next = newOne;
			} else {
				Block *newOne = new Block;
				newOne->size = 0;
				for (int j = i; j < MaxElemsPerBlock; j++) {
					newOne->value[newOne->size++] = prev->value[j];
				}
				prev->value[i] = newValue;
				prev->size = i+1;
				newOne->next = cur;
				prev->next = newOne;
			}
		} else {
			for (int j = prev->size; j > i; j--) {
				prev->value[j] = prev->value[j-1];
			}
			prev->value[i] = newValue;
			prev->size++;
		}
	}
	else {
		if (cur) {
			if (cur->size == MaxElemsPerBlock) {
				head = new Block;
				head->size = 0;
				head->value[head->size++] = newValue;
				head->next = cur;
			} else {
				for (int j = cur->size; j > 0; j--) {
					cur->value[j] = cur->value[j-1];
				}
				cur->value[0] = newValue;
				cur->size++;
			}
		} else {
			head = new Block;
			head->size = 0;
			head->value[head->size++] = newValue;
			head->next = NULL;
		}
	}
}


/* Implementation notes: dequeueMax
 * --------------------------------
 * The maximum value is kept at the head of the list, so it's easy to find and
 * remove. Note we take care to free the memory for the deleted bank whose size
 * is zero.
 */
int PQueue::dequeueMax()
{
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
	
	int value = head->value[0];
	if (head->size == 1) {
 		Block *toBeDeleted = head;
 		head = head->next; 	// splice head cell out
		delete toBeDeleted;
	} else {
		head->size--;
		for (int j = 0; j < head->size; j++) {
			head->value[j] = head->value[j+1];
		}
	}
	return value;
}


/* Implementation notes: bytesUsed
 * -------------------------------
 * The space needed is the sum of the object + the size of all the
 * allocated list banks.
 */
int PQueue::bytesUsed()
{
	int total = sizeof(*this);
 	for (Block *cur = head; cur != NULL; cur = cur->next)
 		total += sizeof(*cur);
 	return total;
}
	

string PQueue::implementationName()
{
	return "sorted chunklist";
}

/*
 * Implementation notes: printDebuggingInfo
 * ----------------------------------------
 * The version for the sorted chunklist prints the node structure
 * in order as a debugging aid to keeping track of the bank contents
 * and the pointers between them. It prints each bank in order.
 */
void PQueue::printDebuggingInfo()
{
   int count = 0;

	cout << "------------------ START DEBUG INFO ------------------" << endl;
	for (Block *cur = head; cur != NULL; cur = cur->next) {
       cout << "Block #" << count << " (at address " << cur << ") values are [";
	   for (int i = 0; i < cur->size; i++) {
		   cout << cur->value[i];
		   if (i != cur->size-1) {
			   cout << ", ";
		   }
	   }
       cout << "] next = " << cur->next << endl;
       count++;
	}
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}