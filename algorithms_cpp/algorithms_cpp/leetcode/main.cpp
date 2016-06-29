#include <iostream>
#include "Leetcode.h"

using namespace std;
using namespace leetcode;

void hash_test()
{
	IntersectionOfTwoArraysII inter;
	inter.test();

	BullsAndCows bc;
	cout << bc.getHint("1123", "0111") << endl;
}

int main()
{
	hash_test();

	return 0;
}