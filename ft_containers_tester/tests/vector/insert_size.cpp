/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_size.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:03:54 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:49:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>

#include "prelude.hpp"

void vec_test_insert_size()
{
    {
        typedef ft::vector<std::size_t, leak_allocator<std::size_t> > vec;

        vec v;

        PRINT_ALL(v);

        v.insert(v.begin(), 64, 10);

        PRINT_ALL(v);

        v.insert(v.begin() + 10, 64, 11);

        PRINT_ALL(v);

        v.insert(v.end(), 512, 10);

        PRINT_ALL(v);

        v.insert(v.end(), 23);
        v.insert(v.end() - 2, 10, 21);

        PRINT_ALL(v);

        v.insert(v.end(), 0, 10);

        PRINT_ALL(v);

        v.insert(v.begin(), 0, 10);

        PRINT_ALL(v);

        v.insert(v.begin() + 50, 1, 10);

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<double, leak_allocator<double> > vec;

        vec v;

        PRINT_ALL(v);

        v.insert(v.end(), 0, 23.0);

        PRINT_ALL(v);

        v.insert(v.begin(), 0, 1.0);

        PRINT_ALL(v);

        v.insert(v.begin(), 1, 64.0);

        PRINT_ALL(v);

        v.insert(v.begin(), 24000, 64.0);

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v;

        ctor_dtor_checker<int> c;

        v.insert(v.end(), 40, c);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> c;

        v.push_back(c);
        CHECK_DTOR(int);

        v.insert(v.end(), 2, c);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> c;

        v.push_back(c);
        CHECK_DTOR(int);

        v.insert(v.end(), 222, c);

        CHECK_DTOR(int);
    }
    {
        ft::vector<int> v(5000);

        PRINT_SIZE_CAP(v);

        try {
            v.insert(v.begin() + 115, std::numeric_limits<std::ptrdiff_t>::max(), 5);
        } catch (std::length_error&) {
            PRINT_MSG("Length exception");
        }
        CATCH_UNHANDLED_EX();

        PRINT_SIZE_CAP(v);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_insert_size();
    CHECK_LEAKS(std::size_t);
    CHECK_LEAKS(double);
    CHECK_LEAKS(int);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
