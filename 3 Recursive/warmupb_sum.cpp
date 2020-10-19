/*
 * Program: warmupb_sum.cpp
 * --------------------
 * Program used to solve subset sum problem.
 *
 * Chao Wang Tue Oct 6 2020
 */
#include <iostream>
#include "vector.h"

bool CanMakeSum(Vector<int> & nums, int targetSum) {
	if (nums.size() == 0) return false;
	else if (targetSum == 0) return true;
	else {
		int first = nums[0];
		nums.removeAt(0);
		if (CanMakeSum(nums, targetSum-first) || CanMakeSum(nums, targetSum)) {
			return true;
		} else {
			nums.insertAt(0, first);
			return false;
		}
	}
}

int main ()
{
	Vector<int> nums;
	nums.add(3);
	nums.add(7);
	nums.add(1);
	nums.add(8);
	nums.add(-3);
	cout << (CanMakeSum(nums, 4) ? "Found" : "Not Found") << endl;
	cout << (CanMakeSum(nums, 10) ? "Found" : "Not Found") << endl;
	return 0;
}
