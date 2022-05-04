/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_copy.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:44:31 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:45:31 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_ctor_copy()
{
    {
        ft::vector<double, leak_allocator<double> > v(128, -345783);
        ft::vector<double, leak_allocator<double> > v_copy(v);

        PRINT_ALL(v_copy);

        if (v.data() == v_copy.data()) {
            std::cout << "Copy ctor doesn't do a deep copy!";
            PRINT_FILE_LINE();
        }

        if (!std::equal(v.begin(), v.end(), v_copy.begin())) {
            std::cout << "Copy ctor error";
            PRINT_FILE_LINE();
        }

        ft::vector<double, leak_allocator<double> > v1;
        ft::vector<double, leak_allocator<double> > v_copy1(v1);

        PRINT_ALL(v_copy1);

        if (v1.data() != v_copy1.data()) {
            std::cout << "Non-null pointer in vector of size 0";
            PRINT_FILE_LINE();
        }

        if (!std::equal(v1.begin(), v1.end(), v_copy1.begin())) {
            std::cout << "Copy ctor error.";
            PRINT_FILE_LINE();
        }
    }
    {
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v1(512);
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v2(v1);

        PRINT_SIZE_CAP(v1);
        PRINT_SIZE_CAP(v2);

        CHECK_DTOR(int);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_ctor_copy();
    CHECK_LEAKS(double);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
