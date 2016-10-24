#pragma once
#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <functional>
#include <iostream>

// Define heapsort algorithm based on STL heap manipulation
namespace algo
{
    template <typename RandomIter, typename Comparator>
    void max_heapify(RandomIter first,
        RandomIter last,
        size_t heapify_pos,
        Comparator comp)
    {
        typename std::iterator_traits<RandomIter>::difference_type max_dist
            = std::distance(first, last);
        // Attention: you can only swap with one branch,
        // Otherwise both subtrees' heap property are destroyed
        while (true)
        {
            auto cur = first + heapify_pos;
            auto lpos = heapify_pos * 2 + 1;
            auto rpos = lpos + 1;
            auto swappos = heapify_pos;
            auto compval = *cur;
            if (lpos < max_dist && comp(compval, *(first + lpos)))
            {
                compval = *(first + lpos);
                swappos = lpos;
            }
            if (rpos < max_dist && comp(compval, *(first + rpos)))
            {
                swappos = rpos;
            }
            if (swappos == heapify_pos)
                break;
            else
            {
                std::swap(*cur, *(first + swappos));
                heapify_pos = swappos;
            }
        }
    }

    // Build a max-heap, comp should return true if 
    // The first element is smaller than the second one
    // Build heap is O(n) complexity
    template <typename RandomIter, typename Comparator>
    void build_max_heap(RandomIter first, RandomIter last, Comparator comp)
    {
        // Build a max heap based on comp
        std::iterator_traits<RandomIter>::difference_type length
            = std::distance(first, last);
        auto heapify_pos = length / 2 - 1;
        for (; heapify_pos >= 0; heapify_pos--)
        {
            max_heapify(first, last, heapify_pos, comp);
        }
    }

    template <typename RandomIter, typename Comparator>
    void heap_sort(RandomIter first, RandomIter last, Comparator comp)
    {
        build_max_heap(first, last, comp);
        while (distance(first, last) > 1)
        {
            std::swap(*first, *(last - 1));
            last -= 1;
            max_heapify(first, last, 0, comp);
        }
    }

    void test_build_max_heap()
    {
        std::vector<int> v{ 3, 1, 4, 2, 7, 11, 2, 5, 9 };

        std::cout << "initially, v: ";
        for (auto i : v) std::cout << i << ' ';
        std::cout << '\n';

        build_max_heap(v.begin(), v.end(), [](int v1, int v2) { return v1 < v2; });

        std::cout << "after make_heap, v: ";
        for (auto i : v) std::cout << i << ' ';
        std::cout << '\n';

        std::vector<int> v2{ 3, 1, 4, 2, 7, 11, 2, 5, 9 };
        heap_sort(v2.begin(), v2.end(), std::less<int>());
        std::cout << "after heap_sort" << std::endl;
        for (auto i : v2) std::cout << i << ' ';
        std::cout << '\n';
        /*

        std::pop_heap(v.begin(), v.end());
        auto largest = v.back();
        v.pop_back();
        std::cout << "largest element: " << largest << '\n';

        std::cout << "after removing the largest element, v: ";
        for (auto i : v) std::cout << i << ' ';
        std::cout << '\n';
        */
    }
}

#endif