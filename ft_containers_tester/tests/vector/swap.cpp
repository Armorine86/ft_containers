/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:45:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:53:13 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_swap()
{
    {
        ft::vector<long> v1(64);
        ft::vector<long> v2(128);

        PRINT_ALL(v1);
        PRINT_ALL(v2);

        v1.swap(v2);

        PRINT_ALL(v1);
        PRINT_ALL(v2);

        v2.resize(0);
        v2.swap(v1);

        PRINT_ALL(v1);
        PRINT_ALL(v2);

        ft::swap(v1, v2);

        PRINT_ALL(v1);
        PRINT_ALL(v2);
    }
    {
        typedef ft::vector<ctor_dtor_checker<long>, leak_allocator<ctor_dtor_checker<long> > > vec;

        vec v1(64);
        vec v2(128);

        v1.swap(v2);

        v2.resize(0);
        v2.swap(v1);

        v2.resize(52);
        ft::swap(v1, v2);

        CHECK_DTOR(long);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_swap();
    CHECK_LEAKS(long);
    CHECK_LEAKS(ctor_dtor_checker<long>);
    CHECK_DTOR(long);
}
#endif
