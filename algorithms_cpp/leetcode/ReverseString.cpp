#include "Leetcode.h"

using namespace leetcode;

std::string ReverseString::reverseString(std::string s)
{
    std::reverse(s.begin(), s.end());
    return s;
}
