#pragma once
#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <ctime>

#include "HeapSort.h"
#include "InsertionSort.h"

namespace algo
{
    const int _stl_threshold = 16;

    template <class T>
    inline const T& median_of_three(const T& a, const T& b, const T& c)
    {
        if (a < b)
            if (b < c)
                return b;
            else if (c < a)
                return a;
            else
                return c;
        else if (a < c)
            return a;
        else if (b < c)
            return c;
        else
            return b;
    }

    // Here end points to one past the last
    // Element of the range
    template <typename RandomIter, typename T>
    RandomIter _partition(RandomIter begin,
        RandomIter end,
        T pivot)
    {
        while (true)
        {
            while (*begin < pivot)
                begin++;
            --end;
            while (*end > pivot)
                end--;
            if (!(begin < end))
                return begin;
            std::iter_swap(begin, end);
            begin++;
        }
    }

    // Find the largest k so that 2^k <= n
    // to find the maximum split depth
    template <class Size>
    inline Size __lg(Size n)
    {
        Size k;
        for (k = 0; n > 1; n >>= 1) ++k;
        return k;
    }

    template <typename RandomIter, class Size>
    void _intro_loop(RandomIter first,
        RandomIter last,
        Size limit)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        while (last - first > _stl_threshold)
        {
            if (limit == 0) {
                heap_sort(first, last, std::less<T>());
                return;
            }
            --limit;
            RandomIter split = _partition(first, last,
                T(median_of_three(*first, *(last - 1), *(first + (last - first) / 2))));
            _intro_loop(split, last, limit);
            last = split; // go back to preparing recurse on left
        }
    }

    template <typename RandomIter>
    void __unguarded_insertion_sort(RandomIter begin, RandomIter end)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        for (RandomIter i = begin; i != end; ++i)
        {
            T value = *i;
            RandomIter cur = i;
            --cur;
            while (value < *cur)
            {
                *(cur + 1) = *cur;
                --cur;
            }
            *(cur + 1) = value;
        }
    }


    template <typename RandomIter>
    void final_insertion_sort(RandomIter begin, RandomIter end)
    {
        if (end - begin > _stl_threshold)
        {
            insertion_sort(begin, begin + _stl_threshold);
            __unguarded_insertion_sort(begin + _stl_threshold, end);
        }
        else
        {
            insertion_sort(begin, end);
        }
    }

    template <typename RandomIter>
    inline void intro_sort(RandomIter begin,
        RandomIter end)
    {
        if (begin != end)
        {
            _intro_loop(begin, end, __lg((end - begin) * 2));
            final_insertion_sort(begin, end);
        }
    }

    void test_intro_sort()
    {
        for (int i = 0; i < 100; i++)
        {
            srand(time(NULL));
            std::vector<int> v;
            for (int i = 0; i < 1000; i++) {
                int ri = rand() % 1000;
                v.push_back(ri);
            }
            std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << "After sorting" << std::endl;
            intro_sort(v.begin(), v.end());
            std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
            for (size_t i = 0; i < v.size() - 2; i++)
                assert(v[i] <= v[i + 1]);
        }
        
    }
}
#endif