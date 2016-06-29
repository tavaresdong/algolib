#include "../Leetcode.h"

using namespace leetcode;

vector<int> IntersectionOfTwoArrays::
intersection(vector<int>& nums1, vector<int>& nums2)
{
    set<int> resFilter;
    set<int> filter(nums1.begin(), nums1.end());
    for (auto val : nums2)
    {
        if (filter.find(val) != filter.end())
        {
            resFilter.insert(val);
        }
    }
    return vector<int>(resFilter.begin(), resFilter.end());
}
