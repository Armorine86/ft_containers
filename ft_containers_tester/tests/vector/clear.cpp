/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:20:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:45:01 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_clear()
{
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v;
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        v.clear();
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(1);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        v.clear();
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(512);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        v.clear();
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<int, leak_allocator<int> > vec;

        vec v(1);

        PRINT_ALL(v);

        v.clear();

        PRINT_ALL(v);

        v.clear();

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<int, leak_allocator<int> > vec;

        vec v(512);

        PRINT_ALL(v);

        v.clear();

        PRINT_ALL(v);

        v.clear();

        PRINT_ALL(v);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_clear();
    CHECK_LEAKS(int);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
