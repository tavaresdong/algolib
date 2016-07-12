#include <iostream>
#include "leetcode/Leetcode.h"
#include "ds/PriorityQueue.h"
#include "algo/HeapSort.h"
#include "algo/RadixSort.h"

using namespace leetcode;
using namespace ds;
using namespace algo;

void hash_test()
{
	IntersectionOfTwoArraysII inter;
	inter.test();

	BullsAndCows bc;
	cout << bc.getHint("1123", "0111") << endl;
}



int main()
{
	// algo::test_build_max_heap();
	algo::test_radix_sort();
	return 0;
}