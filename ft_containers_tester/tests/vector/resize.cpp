/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:42:10 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:52:58 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_resize()
{
    {
        ft::vector<int> v;

        PRINT_ALL(v);

        v.resize(64, 5);

        PRINT_ALL(v);

        v.resize(126, 1);

        PRINT_ALL(v);

        v.resize(24, -1);

        PRINT_ALL(v);

        v.resize(24, 0);

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;
        vec v;

        v.resize(64);

        v.resize(126);

        v.resize(24);

        v.resize(24);

        CHECK_DTOR(int);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_resize();
    CHECK_LEAKS(int);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
