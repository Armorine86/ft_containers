/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:35:56 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:43:25 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_assign()
{
    {
        ft::vector<int, leak_allocator<int> > v(1);

        PRINT_ALL(v);

        v.assign(64, 10);

        PRINT_ALL(v);
    }
    {
        ft::vector<int, leak_allocator<int> > v(128);

        PRINT_ALL(v);

        v.assign(32, -1);

        PRINT_ALL(v);
    }
    {
        ft::vector<int, leak_allocator<int> > v(512);

        PRINT_ALL(v);

        v.push_back(7);

        PRINT_ALL(v);

        v.assign(564, 101010);

        PRINT_ALL(v);
    }
    {
        ft::vector<int, leak_allocator<int> > v(512, 123);

        PRINT_LINE("Size:", v.size());

        v.assign(0, 1);

        PRINT_LINE("Size2:", v.size());
    }
    {
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v(512);

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> c;
        v.push_back(c);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        v.assign(564, c);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v(5);

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> c;
        v.push_back(c);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        v.assign(8, c);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v(65);

        PRINT_SIZE_CAP(v);

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> c;
        v.assign(8, c);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        ft::vector<int, leak_allocator<int> > v;

        PRINT_ALL(v);

        v.assign(0, 101010);

        PRINT_ALL(v);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_assign();
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_LEAKS(int);
    CHECK_DTOR(int);
}
#endif
