#pragma once
#ifndef _SELECTION_H_
#define _SELECTION_H_
#include <iterator>
#include <functional>

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
}
#endif