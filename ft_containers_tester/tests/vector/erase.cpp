/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:21:37 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:48:02 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_erase()
{
    {
        typedef ft::vector<int, leak_allocator<int> > vec;

        vec v(64);

        vec::iterator it = v.erase(v.begin() + 25);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);

        it = v.erase(v.begin());

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);

        it = v.erase(v.end() - 1);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);

        vec::iterator it = v.erase(v.begin() + 25);
        (void)it;

        PRINT_SIZE_CAP(v);

        it = v.erase(v.begin());
        (void)it;

        PRINT_SIZE_CAP(v);

        it = v.erase(v.end() - 1);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_erase();
    CHECK_LEAKS(int);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
