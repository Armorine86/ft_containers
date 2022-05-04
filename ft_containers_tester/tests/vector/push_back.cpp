/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:36:49 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:52:33 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_push_swap()
{
    {
        typedef ft::vector<double, leak_allocator<double> > vec;

        vec v;

        PRINT_ALL(v);

        v.push_back(45.0);

        PRINT_ALL(v);

        v.push_back(0.1234);

        PRINT_ALL(v);

        v.push_back(12.2346);

        PRINT_ALL(v);

        v.push_back(3456.0);

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<double>, leak_allocator<ctor_dtor_checker<double> > >
            vec;

        vec v;

        ctor_dtor_checker<double> d;
        v.push_back(d);
        PRINT_SIZE_CAP(v);

        v.push_back(d);
        PRINT_SIZE_CAP(v);

        v.push_back(d);
        PRINT_SIZE_CAP(v);

        v.push_back(d);
        PRINT_SIZE_CAP(v);

        CHECK_DTOR(double);
    }
    {
        ft::vector<int> v;

        for (int i = 0; i < 515; ++i) {
            v.push_back(i);
            PRINT_ALL(v);
        }
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v;
        ctor_dtor_checker<int> c;

        for (int i = 0; i < 2050; ++i) {
            v.push_back(c);
        }
        CHECK_DTOR(int);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_push_swap();
    CHECK_LEAKS(double);
    CHECK_LEAKS(int);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_LEAKS(ctor_dtor_checker<double>);
    CHECK_DTOR(int);
    CHECK_DTOR(double);
}
#endif
