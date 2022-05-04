/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_back.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:47:30 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:52:04 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_pop_back()
{
    {
        ft::vector<long> v(64);

        iota(v.begin(), v.end(), 64);

        PRINT_ALL(v);

        v.pop_back();

        PRINT_ALL(v);

        for (int i = 0; i < 10; ++i) {
            v.pop_back();
        }

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<long>, leak_allocator<ctor_dtor_checker<long> > > vec;
        vec v(64);

        for (int i = 0; i < 10; ++i) {
            v.pop_back();
        }

        CHECK_DTOR(long);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_pop_back();
    CHECK_LEAKS(ctor_dtor_checker<long>);
    CHECK_LEAKS(long);
    CHECK_DTOR(long);
}
#endif
