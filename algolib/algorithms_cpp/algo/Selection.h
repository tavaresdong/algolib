#pragma once
#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <iterator>
#include <functional>
#include <utility>
#include <cstdlib>
#include <stdexcept>
#include <ctime>

#include "InsertionSort.h"

namespace algo
{
    template <typename RandomIter, typename Comparator>
    RandomIter __select_winner(RandomIter first, RandomIter last, Comparator comp)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        T cur = *first;
        RandomIter winner = first;
        for (auto iter = std::next(first); iter != last; ++iter)
        {
            if (comp(*iter, cur))
            {
                cur = *iter;
                winner = iter;
            }
        }
        return winner;
    }

    template <typename RandomIter>
    RandomIter min(RandomIter first, RandomIter last)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        return __select_winner(first, last, std::less<T>());
    }

    template <typename RandomIter>
    RandomIter max(RandomIter first, RandomIter last)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        return __select_winner(first, last, std::greater<T>());
    }

    
    // An algorithm to get min and max simultaneously with 3/2*n comparison
    template <typename RandomIter>
    std::pair<RandomIter, RandomIter> minmax(RandomIter first, RandomIter last)
    {
        typedef typename std::iterator_traits<RandomIter>::value_type T;
        RandomIter big, small;
        RandomIter p1, p2;
        auto dist = std::distance(first, last);
        std::less<T> comp;

        if (first == last)
        {
            return std::pair<RandomIter, RandomIter>(first, first);

        }

        if (dist % 2 != 0)
        {
            big = small = first;
            p1 = next(first);
        }
        else
        {
            RandomIter n = next(first);
            if (comp(*first, *n))
            {
                big = n;
                small = first;
            }
            else
            {
                big = first;
                small = n;
            }
            p1 = next(n);
        }

        for (; p1 != last; p1 = next(p2))
        {
            p2 = std::next(p1);
            if (comp(*p1, *p2)) 
            {
                if (comp(*p1, *small))
                {
                    small = p1;
                }
                if (comp(*big, *p2))
                {
                    big = p2;
                }
            }
            else
            {
                if (comp(*p2, *small))
                {
                    small = p2;
                }
                if (comp(*big, *p1))
                {
                    big = p1;
                }
            }
        }
        return std::pair<RandomIter, RandomIter>(small, big);
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

    template <typename RandomIter>
    RandomIter _partition_retain_pivot(RandomIter begin,
        RandomIter end,
        RandomIter piv_pos)
    {
        typedef std::iterator_traits<RandomIter>::value_type T;
        T pivot = *piv_pos;
        std::iter_swap(begin, piv_pos);
        RandomIter old_begin = begin;
        begin++;
        while (true)
        {
            while (*begin < pivot)
                begin++;
            --end;
            while (*end > pivot)
                end--;
            if (!(begin < end))
            {
                // Put pivot value here
                // left <= but begin itself may be bigger than pivot!
                // Right half(including self) : >= pivot
                // Left half : <= pivot
                std::iter_swap(old_begin, std::prev(begin));
                return std::prev(begin);
            }
            std::iter_swap(begin, end);
            begin++;
        }
    }

    template <typename RandomIter>
    RandomIter randomized_partition(RandomIter first, RandomIter last)
    {
        std::srand(std::time(0));
        int pivot = std::rand() % std::distance(first, last);
        return _partition(first, last, *(first + pivot));
    }

    // Find the ith element in this range (i starts from 1 to size())
    template <typename RandomIter>
    RandomIter randomized_select(RandomIter first, RandomIter last, size_t ind)
    {
        while (true)
        {
            if (first == last)
                return first;
            RandomIter q = randomized_partition(first, last);
            size_t k = std::distance(first, q) + 1;
            if (ind == k)
                return q;
            else if (ind > k)
            {
                first = std::next(q);
                ind = ind - k;
            }
            else
            {
                last = q;
            }
        }
    }

    // Insert-sort on this at most 5 element range
    // And return the median
    template <typename RandomIter>
    RandomIter __median(RandomIter first, RandomIter last)
    {
        insertion_sort(first, last);
        return first + (std::distance(first, last) / 2);
    }
    
    // Worst case O(n) to find ith element
    template <typename RandomIter>
    RandomIter select(RandomIter first, RandomIter last, size_t ind)
    {
        if (last <= first)
            return last;
        if (ind > std::distance(first, last))
            throw std::out_of_range("ind: " + ind);

        if (std::distance(first, last) <= 5)
        {
            insertion_sort(first, last);
            return first + (ind - 1);
        }

        RandomIter medians = first;
        RandomIter grp_begin = first, grp_end = first;
        for (; grp_begin != last; grp_begin = grp_end)
        {
            grp_end = (std::distance(grp_begin, last) > 5) ? (grp_begin + 5) : last;
            RandomIter median_of_five = __median(grp_begin, grp_end);
            std::iter_swap(medians, median_of_five);
            medians = std::next(medians);
        }

        // Recurse to find median of medians
        RandomIter median_of_medians = select(first, medians, 
            std::distance(first, medians) / 2);

        // Partition around this median of medians
        RandomIter pos = _partition_retain_pivot(first, last, median_of_medians);

        size_t k = std::distance(first, pos) + 1;
        if (ind == k)
            return pos;
        else if (ind > k)
        {
            return select(std::next(pos), last, ind - k);
        }
        else
        {
            return select(first, pos, ind);
        }
    }
}
#endif