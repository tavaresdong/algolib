#ifndef _LEETCODE_H_
#define _LEETCODE_H_
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

namespace leetcode
{
    class ReverseString {
    public:
        std::string reverseString(std::string s);
    };

    class IntersectionOfTwoArraysII {
    public:
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2);
        bool test();
    };

}
#endif // _LEETCODE_H_
