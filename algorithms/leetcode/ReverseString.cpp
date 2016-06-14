#include "Leetcode.h"
#include <algorithm>

using namespace leetcode;

std::string ReverseString::reverseString(std::string s)
{
    std::reverse(s.begin(), s.end());
    return s;
}
