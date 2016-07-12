#pragma once
#ifndef _RADIXSORT_H_
#define _RADIXSORT_H_

#include <cstdint>     // for CHAR_BIT (# of bits in a byte), the size of a type is in bytes
#include <iterator>    // for iterator_traits
#include <vector>
#include <limits>      // for numeric_limits
#include <algorithm>   // for std:copy
#include <iostream>
#include <utility>

namespace algo
{
	template <typename RandomIter>
	void radix_sort(RandomIter begin, RandomIter end)
	{
		typedef typename std::iterator_traits<RandomIter>::value_type T;

		std::vector<T> bits[2];

		// Iterator over all bits, use counting sort to put them in bits
		for (size_t bit = 0; bit < CHAR_BIT * sizeof(T); bit++)
		{
			for (RandomIter iter = begin; iter != end; iter++)
			{
				bits[(*iter & (1l << bit))? 1 : 0].push_back(*iter);
			}

			if (std::numeric_limits<T>::is_signed &&
				bit == CHAR_BIT * sizeof(T) - 1)
			{
				std::swap(bits[0], bits[1]);
			}

			// Copy back the values
			std::copy(bits[0].begin(), bits[0].end(), begin);
			std::copy(bits[1].begin(), bits[1].end(), begin + bits[0].size());
			
			bits[0].clear();
			bits[1].clear();
		}
	}

	void test_radix_sort()
	{
		// Test unsigned values
		std::vector<unsigned int> v1{ 3, 33, 21, 15, 16, 5, 6, 9, 7, 24, 1, 19 };
		radix_sort(v1.begin(), v1.end());
		std::copy(v1.begin(), v1.end(),
			std::ostream_iterator<unsigned int>(std::cout, " "));
		std::cout << "\n";

		// Test signed values
		std::vector<int> v2{ 3, 33, 21, -15, -3, 5, -4, 9, -7, 24, 1, -19 };
		radix_sort(v2.begin(), v2.end());
		std::copy(v2.begin(), v2.end(),
			std::ostream_iterator<int>(std::cout, " "));
		
	}
}

#endif