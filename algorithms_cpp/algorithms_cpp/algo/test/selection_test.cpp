#include "selection_test.h"

#include <vector>
#include <string>
#include <iostream>
#include "../Selection.h"

namespace algo
{
    void minmax_test()
    {
        std::vector<int> v = { 5, 4, 6, 10, 12, 3, 7, 9 };
        std::cout << *min(v.begin(), v.end()) << std::endl;

        std::vector<std::string> v2 = { "hello", "hellowordl", "hellowordz", "daydream", "das~~" };
        std::cout << *max(v2.begin(), v2.end()) << std::endl;

        auto res = minmax(v2.begin(), v2.end());
        auto res2 = minmax(v.begin(), v.end());
        std::cout << *res.first << *res.second << std::endl;
        std::cout << *res2.first << *res2.second << std::endl;
    }

}