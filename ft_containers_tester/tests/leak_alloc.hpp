/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_alloc.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:36:03 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:41:48 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <utility>

template <typename T>
class leak_allocator
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template <typename U>
    struct rebind {
        typedef leak_allocator<U> other;
    };

public:
    leak_allocator(){};
    leak_allocator(const leak_allocator&){};

    leak_allocator& operator=(const leak_allocator&)
    {
        return *this;
    }

    bool operator==(const leak_allocator&)
    {
        return true;
    }

    bool operator!=(const leak_allocator&)
    {
        return false;
    }

public:
    static void check_leaks()
    {
        if (allocations.size() > 0) {
            std::cout << "========================================\n";
            std::cout << allocations.size() << " leak(s) detected" << std::endl;
            std::cout << "========================================\n";
        }
    }

    T* allocate(std::size_t n, const void* hint = 0)
    {
        T* block = std::allocator<T>().allocate(n, hint);
        allocations.insert(std::make_pair((void*)block, n));
        return block;
    }

    void deallocate(T* p, std::size_t n)
    {
        typename std::map<void*, std::size_t>::iterator it = allocations.find(p);
        if (it->second != n) {
            std::cout << "========================================\n";
            std::cout << "Deallocate: Wrong block size: " << it->first << ": received " << n
                      << " but should be " << it->second << "\n";
            std::cout << "========================================\n";
        }
        std::allocator<T>().deallocate(p, n);
        allocations.erase(p);
    }

    size_type max_size() const
    {
        return std::allocator<T>().max_size();
    }

    void construct(pointer p, const_reference val)
    {
        std::allocator<T>().construct(p, val);
    }

    void destroy(pointer p)
    {
        std::allocator<T>().destroy(p);
    }

private:
    static std::map<void*, std::size_t> allocations;
};

template <typename T>
std::map<void*, std::size_t> leak_allocator<T>::allocations = std::map<void*, std::size_t>();

#ifdef LEAK_CHECK
#define CHECK_LEAKS(type)                                                                          \
    {                                                                                              \
        leak_allocator<type>::check_leaks();                                                       \
    }
#else
#define CHECK_LEAKS(type)                                                                          \
    {                                                                                              \
    }
#endif
