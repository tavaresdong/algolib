#pragma once
#ifndef YCALLOC_H_
#define YCALLOC_H_

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace algolib
{
    template <typename T>
    inline T* _allocate(ptrdiff_t size, T*)
    {
        std::set_new_handler([]() 
            { std::cerr << "Failed Allocating Memory" << std::endl;
              std::exit(1); 
            });
        T* tmp = static_cast<T*>(::operator new((size_t)(size * sizeof(T)));
        if (tmp == nullptr)
        {
            std::cerr << "No memory Left" << std::endl;
            std::exit(1);
        }
        return tmp;
    }

    template <typename T>
    inline void _deallocate(T* buffer)
    {
        ::operator delete(buffer);
    }

    template <typename T1£¬ typename T2>
    inline void _construct(T1* p, const T2& val)
    {
        new (p) T1(val);
    }

    template <typename T>
    inline void _destroy(T* ptr)
    {
        ptr->~T();
    }

    template <typename T>
    class ycallocator
    {
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        template <typename U>
        struct rebind
        {
            typedef ycallocator<U> other;
        };

        pointer allocate(size_type n, const void* hint = 0)
        {
            return _allocate(static_cast<difference_type>(n), static_cast<pointer>(0));
        }

        void deallocate(pointer p, size_type n)
        {
            _deallocate(p);
        }

        void construct(pointer p, const T& value)
        {
            _construct(p, value);
        }

        void destroy(pointer p)
        {
            _destroy(p);
        }

        pointer address(reference x)
        {
            return static_cast<pointer>(&x);
        }

        const_pointer const_address(const_reference x)
        {
            return static_cast<const_pointer>(&x);
        }

        size_type max_size() const
        {
            return size_type(UINT_MAX / sizeof(T));
        }
    };
}

#endif