/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:34:08 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:44:41 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_back()
{
    {
        ft::vector<long, leak_allocator<long> > v(1, 9);

        PRINT_LINE("Back:", v.back());

        if (&v.back() != &v[0]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
    {
        ft::vector<long, leak_allocator<long> > v(123, 543);

        PRINT_LINE("Back:", v.back());

        if (&v.back() != &v[122]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
    {
        const ft::vector<long, leak_allocator<long> > v(1, 9);

        PRINT_LINE("Back:", v.back());

        const long& b = v.back();
        if (&b != &v[0]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
    {
        const ft::vector<long, leak_allocator<long> > v(123, 543);

        PRINT_LINE("Back:", v.back());

        const long& b = v.back();
        if (&b != &v[122]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_back();
    CHECK_LEAKS(long);
}
#endif
