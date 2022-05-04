/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_range.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:14:16 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:47:42 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_erase_range()
{
    {
        typedef ft::vector<long, leak_allocator<long> > vec;

        vec v;

        PRINT_ALL(v);

        v.erase(v.begin(), v.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<long>, leak_allocator<ctor_dtor_checker<long> > > vec;

        vec v;

        PRINT_SIZE_CAP(v);

        v.erase(v.begin(), v.end());

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(long);
    }
    {
        typedef ft::vector<long, leak_allocator<long> > vec;

        vec v(512);

        iota(v.begin(), v.end(), 42);

        PRINT_ALL(v);

        v.erase(v.begin() + 57, v.begin() + 245);

        PRINT_ALL(v);

        v.erase(v.begin() + 57, v.begin() + 57);

        PRINT_ALL(v);

        PRINT_ALL(v);
        v.erase(v.end(), v.end());
    }
    {
        typedef ft::vector<ctor_dtor_checker<long>, leak_allocator<ctor_dtor_checker<long> > > vec;

        vec v(512);
        CHECK_DTOR(long);

        PRINT_SIZE_CAP(v);

        v.erase(v.begin() + 57, v.begin() + 245);
        CHECK_DTOR(long);

        PRINT_SIZE_CAP(v);

        v.erase(v.begin() + 57, v.begin() + 57);
        CHECK_DTOR(long);

        PRINT_SIZE_CAP(v);

        v.erase(v.end(), v.end());
        CHECK_DTOR(long);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(long);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_erase_range();
    CHECK_LEAKS(long);
    CHECK_LEAKS(ctor_dtor_checker<long>);
    CHECK_DTOR(long);
}
#endif
