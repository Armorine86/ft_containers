/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelude.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:49:37 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 14:36:46 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_alloc.hpp"
#include "print.hpp"

#ifdef USE_STD

namespace ft = std;

#include <map>
#include <set>
#include <stack>
#include <vector>

#else

// #include <stack.hpp>
#include <vector.hpp>
// #include <map.hpp>
// #include <set.hpp>

#endif

#ifndef LEAK_CHECK

#define leak_allocator std::allocator

#endif

#include <algorithm>
#include <iostream>
#include <sstream>

template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value = T())
{
    while (first != last) {
        *first++ = value;
        ++value;
    }
}

template <typename T>
class ctor_dtor_checker
{
public:
    static void check_count()
    {
        if (count == 0) {
            std::cout << "====================================\n";
            std::cout << "Every object destroyed\n";
            std::cout << "====================================\n";
        } else {
            std::cout << "====================================\n";
            std::cout << "Number of alive objects: " << count << "\n";
            std::cout << "====================================\n";
        }
    }

public:
    ctor_dtor_checker()
        : value()
    {
        ++count;
    }

    explicit ctor_dtor_checker(const T& v)
        : value(v)
    {
    }

    ctor_dtor_checker(const ctor_dtor_checker& other)
        : value(other.value)
    {
        ++count;
    }

    ~ctor_dtor_checker()
    {
        --count;
    }

public:
    ctor_dtor_checker& operator==(const ctor_dtor_checker& other)
    {
        return value == other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const ctor_dtor_checker& c);

private:
    T value;
    static std::size_t count;
};

template <typename T>
std::size_t ctor_dtor_checker<T>::count = 0;

template <typename T>
std::ostream& operator<<(std::ostream& os, const ctor_dtor_checker<T>& c)
{
    os << c.value;
    return os;
}

#define CHECK_DTOR(type)                                                                           \
    {                                                                                              \
        ctor_dtor_checker<type>::check_count();                                                    \
    }
