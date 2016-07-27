#pragma once
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace algo
{
    // We predefined 28 prime numbers to be used on our
    // Hashtable, and we provide a function to
    // find the smallest prime which is larger than given number
    static const int __algo_num_primes = 28;
    static const unsigned long __algo_prime_list[__algo_num_primes] = 
    {
        53, 97, 193, 389, 769,
        1543, 3079, 6151, 12289, 24593,
        49157, 98317, 196613, 393241, 786433,
        1572869, 3145739, 6291469, 12582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457,
        1610612741, 3221225473ul, 4294967291ul
    };

    inline unsigned long __algo_next_prime(unsigned long n)
    {
        auto beg = __algo_prime_list;
        auto end = __algo_prime_list + __algo_num_primes;
        auto pos = std::lower_bound(beg, end, n);
        return (pos == end) ? *(end - 1) : *pos;
    }

    // We use linked hash to define a hashtable
    // __HashNode is the smallest element that stores the payload and link
    template <typename T>
    class __HashNode
    {
    public:
        __HashNode(const T& v) : val(v), next(nullptr) { }
        T val;
        __HashNode* next;
    };

    template <typename Value, typename Key, typename HashFunc,
              typename ExtractKey, typename EqualKey, 
              class Alloc = std::allocator<__HashNode<Value>> >
    class HashTable
    {
    public:
        // These are all function objects
        typedef HashFunc hasher;
        typedef EqualKey key_equal;
        typedef size_t size_type;

        typedef Value value_type;
        typedef __HashNode<Value> node;

    private:
        hasher hash;

        // Test if two keys are equal
        key_equal equals;

        // The method to extract key(hash key) from value
        ExtractKey get_key;

        // Allocator for the node
        Alloc alloc;

        // Num of elements already inserted to our hashtable
        size_type num_elements;

        // buckets storing lists of values with the same hashed position
        std::vector<node*, Alloc> buckets;

    private:
        // Allocate a new node
        // If allocation failed, return a nullptr
        node* new_node(const value_type& val)
        {
            try {
                node* p = alloc.allocate(1);
                alloc.construct(p, val);
                return p;
            }
            catch (const std::bad_alloc& b)
            {
                b.what();
                return nullptr;
            }
        }

        // Delete the node allocated by alloc
        void delete_node(node* p)
        {
            alloc.destroy(p);
            alloc.deallocate(p, 1);
        }

        unsigned long next_size(unsigned long n)
        {
            return __algo_next_prime(n);
        }

        void init_buckets(size_type n)
        {
            const size_type n_bucks = next_size(n);
            buckets.reserve(n_bucks);
            buckets.insert(buckets.end(), n_bucks, (node*) 0);
            num_elements = 0;
        }

        // Decide the position a value is hashed to, just
        // call hash(get_key(val)) % n
        size_type bkt_num(const value_type& val, size_type n) const
        {
            return hash(get_key(val)) % n;
        }


        // Test if given potential elements, should we expand the
        // Table
        void resize(size_type potential)
        {
            const size_type old_n = buckets.size();
            if (potential > old_n)
            {
                const size_type n = next_size(potential);
                std::vector<node*, Alloc> tmp(n, (node*) 0);
                for (size_type bucket = 0; bucket < old_n; bucket++)
                {
                    node* first = buckets[bucket];
                    while (first)
                    {
                        // Find the position this value should be 
                        // in the new buckets(with new M value)
                        size_type new_bucket = bkt_num(first->val, n);

                        // Remove the element from original table
                        // And insert to the new table
                        buckets[bucket] = first->next;
                        first->next = tmp[new_bucket];
                        tmp[new_bucket] = first;
                        first = buckets[bucket];
                    }
                }
                buckets.swap(tmp);
            }
        }

        bool insert_unique_noresize(const value_type& val)
        {
            const size_type n = bkt_num(val, buckets.size());
            node* first = buckets[n];
            for (node* cur = first; cur; cur = cur->next)
            {
                // The key already exists
                if (equals(get_key(cur->val), get_key(val)))
                    return false;
            }

            node* tmp = new_node(val);
            tmp->next = buckets[n];
            buckets[n] = tmp;
            ++num_elements;
            return true;
        }

    public:

        size_type bucket_count() const
        {
            return buckets.size();
        }

        size_type size() const
        {
            return num_elements;
        }

        // Maximum number of buckets available in this system
        size_type max_bucket_count()
        {
            return __algo_prime_list[__algo_num_primes - 1];
        }

        HashTable(size_type n,
            const HashFunc& hf,
            const EqualKey& eq)
            : hash(hf), equals(eq), get_key(ExtractKey()), num_elements(0)
        {
            init_buckets(n);
        }

        // A simplified version with no iterator
        // The inserted values should all be unique, 
        // We don't allow duplicate values to be inserted
        bool insert_unique(const value_type& val)
        {
            // test if we need to expand the table
            resize(num_elements + 1);
            return insert_unique_noresize(val);
        }

        size_type elems_in_bucket(size_type i) const
        {
            if (i < 0 || i >= buckets.size())
                throw std::out_of_range("index invalid");
            size_type cnt = 0;
            for (node* first = buckets[i]; first; first = first->next)
            {
                cnt += 1;
            }
            return cnt;
        }

        void clear()
        {
            for (size_type i = 0; i != buckets.size(); ++i)
            {
                node* first = buckets[i];
                while (first)
                {
                    buckets[i] = first->next;
                    delete_node(first);
                    first = buckets[i];
                }
                buckets[i] = (node*)0;
            }
            num_elements = 0;
        }

        // Use copy-and-swap idiom to guarantee exception safety
        void copy_from(const HashTable& ht)
        {
            std::vector<node*, Alloc> tmp;
            tmp.reserve(ht.buckets.size());
            tmp.insert(tmp.end(), ht.bucket.size(), (node*)0);
            try {
                for (size_type i = 0; i != ht.bucket.size(); ++i)
                {
                    node* first = ht.bucket[i];
                    if (first)
                    {
                        node* copy = new_node(first->val);
                        buckets[i] = copy;
                        for (node* cur = first->next; cur; cur = cur->next)
                        {
                            copy->next = new_node(cur->val);
                            copy = copy->next;
                        }
                    }
                }
                tmp.swap(buckets);

                // Clear tmp for memory cleaness
                tmp.clear();
                num_elements = ht.num_elements;
            }
            catch (const std::bad_alloc& e)
            {
            }
        }

    };

    

}

#endif