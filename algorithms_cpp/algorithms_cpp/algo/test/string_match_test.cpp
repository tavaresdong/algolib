#include "string_match_test.h"
#include "../StringMatching.h"

#include <iostream>

namespace algo
{
    void test_next()
    {
        std::cout << kmp("ababababca", "bab") << std::endl;
        std::cout << kmp("ababababca", "abc") << std::endl;
        std::cout << kmp("ababababca", "ca") << std::endl;
        std::cout << kmp("ababababca", "cb") << std::endl;
        std::cout << kmp("BBC ABCDAB ABCDABCDABDE", "ABCDABD") << std::endl;
    }
}