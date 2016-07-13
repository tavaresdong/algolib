#pragma once
#ifndef _MERGESORT_H_
#define _MERGESORT_H_
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace algo
{
    // This is bottom-up merge sort
    // Using an auxiliary array, we swap between two arrays so we
    // Only need to copy the values back when the total merge stage count is odd
    template <typename T>
    void merge_sort(std::vector<T>& arr)
    {
        typedef typename std::vector<T>::difference_type diff;
        std::vector<T> aux_arr(arr);
        int merge_count = 0;
        diff totalsize = distance(arr.begin(), arr.end());
        diff len = 1;
        while (len < totalsize)
        {
            // Merge From arr to aux_arr
            auto merge_left = (merge_count == 0) ? arr.begin() : aux_arr.begin();
            auto copy_iter = (merge_count == 0) ? aux_arr.begin() : arr.begin();
            auto merge_end = (merge_count == 0) ? arr.end() : aux_arr.end();
            while (merge_left != merge_end)
            {
                if (std::distance(merge_left, merge_end) < len)
                {
                    std::copy(merge_left, merge_end, copy_iter);
                    merge_left = merge_end;
                }
                else
                {
                    auto merge_right = merge_left + len;
                    if (std::distance(merge_right, merge_end) < len)
                    {
                        std::merge(merge_left, merge_right,
                                   merge_right, merge_end,
                                   copy_iter);
                        merge_left = merge_end;
                    }
                    else
                    {
                        auto past_right = merge_right + len;
                        copy_iter = std::merge(merge_left, merge_right,
                            merge_right, past_right,
                            copy_iter);
                        merge_left = past_right;
                    }
                }
            }
            len *= 2;
            merge_count = 1 - merge_count;
        }
        if (merge_count % 2 != 0)
        {
            std::copy(aux_arr.begin(), aux_arr.end(), arr.begin());
        }
    }

    void test_merge_sort()
    {
        std::vector<int> v = { 4, 1, 6, 3, 19, 10, 2, 7, 11, 18, 5 };
        merge_sort(v);
        std::cout << "sort ok" << std::endl;
        for (int val : v)
            std::cout << val << endl;

        std::vector<int> v2 = { 4, 1, 6, 3, 19, 10, 2, 7, 11, 18, 5, 17 };
        merge_sort(v2);
        std::cout << "sort ok" << std::endl;
        for (int val : v2)
            std::cout << val << endl;
    }
}

#endif