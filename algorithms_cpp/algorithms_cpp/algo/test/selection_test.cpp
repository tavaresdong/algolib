#include "selection_test.h"

#include <vector>
#include <string>
#include <iostream>

namespace algo
{
    void minmax_test()
    {
        std::vector<int> v = { 5, 4, 6, 10, 12, 3, 7, 9 };
        std::cout << *algo::min(v.begin(), v.end()) << std::endl;

        std::vector<std::string> v2 = { "hello", "hellowordl", "hellowordz", "daydream", "das~~" };
        std::cout << *algo::max(v2.begin(), v2.end()) << std::endl;

        auto res = algo::minmax(v2.begin(), v2.end());
        auto res2 = algo::minmax(v.begin(), v.end());
        std::cout << *res.first << *res.second << std::endl;
        std::cout << *res2.first << *res2.second << std::endl;
    }

    void test_randomized_partition()
    {
        std::vector<int> v = { 5, 12, 34, 54, 123, 43, 32 };
        for (int i = 1; i <= v.size(); i++) {
            std::cout << *randomized_select(v.begin(), v.end(), i) << std::endl;
        }
    }
}