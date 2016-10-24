#include "../Leetcode.h"
#include <list>
#include <utility>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(int capacity) : cur_capacity_(0), max_capacity_(capacity) 
    { }

    int get(int key) 
    {
        auto iter = lookup_.find(key);
        if (iter == lookup_.end())
            return -1;
        else 
        {
            int val = iter->second->second;
            cache_.erase(iter->second);
            cache_.push_back(std::make_pair(key, val));
            lookup_[key] = --(cache_.end());
            return iter->second->second;
        }
    }

    void set(int key, int value) 
    {
        auto iter = lookup_.find(key);
        if (iter != lookup_.end()) 
        {
            cache_.erase(iter->second);
        } 
        else
        {
            if (cur_capacity_ == max_capacity_)
            {
                lookup_.erase(cache_.front().first);
                cache_.pop_front();
                cur_capacity_--;
            }
            cur_capacity_++;
        }
        cache_.push_back(std::make_pair(key, value));
        lookup_[key] = --(cache_.end());
    }

private:
    typedef std::list<std::pair<int, int>>::iterator position;
    int cur_capacity_;
    int max_capacity_;
    std::list<std::pair<int, int>> cache_;
    std::unordered_map<int, position> lookup_;
};