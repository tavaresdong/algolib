#pragma once
#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <iterator>
#include <functional>
#include <utility>
#include <cstdlib>
#include <ctime>


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
}
#endif