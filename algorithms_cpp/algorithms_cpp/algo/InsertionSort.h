#pragma once
#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

namespace algo
{
    template <typename RandomIter>
    void insertion_sort(RandomIter begin, RandomIter end)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        if (begin == end)
            return;
        for (RandomIter i = begin + 1; i != end; i++)
        {
            T value = *i;
            if (value < *begin)
            {
                std::copy_backward(begin, i, i + 1);
                *begin = value;
            }
            else
            {
                RandomIter cur = i;
                cur--;
                // Definitely won't reach the left border
                // We call this unguarded, very efficient when
                // the data amount is huge, because this is a
                // very fundamental algorithm
                while (value < *cur)
                {
                    *(cur + 1) = *cur;
                    cur--;
                }
                *(cur + 1) = value;
            }
        }
    }

}


#endif