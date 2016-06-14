#include "Leetcode.h"

using namespace leetcode;

vector<int> IntersectionOfTwoArraysII::intersect
(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> result;
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    auto iter1 = nums1.begin();
    auto iter2 = nums2.begin();
    for (;iter1 != nums1.end() && iter2 != nums2.end();)
    {
        if (*iter1 == *iter2)
        {
            result.push_back(*iter1);
            iter1++, iter2++;
        }
        else if (*iter1 < *iter2)
        {
            iter1++;
        }
        else
        {
            iter2++;
        }
    }
    return result;
}

bool IntersectionOfTwoArraysII::test()
{
    vector<int> vec1={1,3,7,5,6,4,11,9,10};
    vector<int> vec2={5,4,10,12,8};
    auto res = intersect(vec1, vec2);
    for (auto val : res)
    {
        cout << val << endl;
    }
    return true;
}
