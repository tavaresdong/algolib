#include "hashtable_test.h"

#include <functional>
#include <iostream>

namespace algo {
    void test_hashtable()
    {
        HashTable<int,
            int,
            std::identity<int>,
            std::identity<int>,
            std::equal_to<int>
        > iht(50, std::identity<int>(), std::equal_to<int>());

        std::cout << iht.bucket_count() << std::endl;
        std::cout << iht.size() << std::endl;

        iht.insert_unique(59);
        iht.insert_unique(63);
        iht.insert_unique(108);
        iht.insert_unique(2);
        iht.insert_unique(53);
        iht.insert_unique(55);
        std::cout << iht.size() << std::endl;

        for (size_t i = 0; i < iht.bucket_count(); ++i)
        {
            int n = iht.elems_in_bucket(i);
            if (n != 0)
                std::cout << "bucket[" << i << "] has " 
                          << n << " elems." << std::endl;
        }

        for (int i = 0; i <= 48; i++)
        {
            if (i != 2)
                iht.insert_unique(i);
        }

        std::cout << iht.size() << std::endl;
        std::cout << iht.bucket_count() << std::endl;

        for (size_t i = 0; i < iht.bucket_count(); ++i)
        {
            int n = iht.elems_in_bucket(i);
            if (n != 0)
                std::cout << "bucket[" << i << "] has "
                << n << " elems." << std::endl;
        }
    }
}
