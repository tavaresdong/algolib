#pragma once
#ifndef _STRING_MATCHING_H_
#define _STRING_MATCHING_H_

#include <vector>
#include <string>

namespace algo
{

    std::vector<int> getNext(const std::string& pattern)
    {
        std::vector<int> next;
        if (pattern.empty())
            return next;
        next.reserve(pattern.size());
        next.insert(next.end(), pattern.size(), -1);
        int i = 0, j = 0;
        for (; i < pattern.size() - 1; ++i, j = i)
        {   
            while (true)
            {
                j = next[j];
                if (j == -1 || pattern[j] == pattern[i])
                {
                    next[i + 1] = j + 1;
                    break;
                }
            }
        }
        return next;
    }

    int kmp(const std::string& match, const std::string& pattern)
    {
        std::vector<int> next = getNext(pattern);
        int i = 0, j = 0;
        while (j == -1 || i < match.size() && j < pattern.size())
        {
            if (j == -1 || match[i] == pattern[j]) {
                i++;  j++;
            }
            else
            {
                j = next[j];
            }
        }
        if (j == pattern.size())
            return i - pattern.size();
        else
            return -1;
    }
}

#endif