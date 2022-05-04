/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:29:00 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:48:14 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_front()
{
    {
        ft::vector<long, leak_allocator<long> > v(1, 9);

        PRINT_LINE("Front:", v.front());

        if (&v.front() != &v[0]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
    {
        ft::vector<long, leak_allocator<long> > v(123, 543);

        PRINT_LINE("Front:", v.front());

        if (&v.front() != &v[0]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
    {
        const ft::vector<long, leak_allocator<long> > v(1, 9);

        PRINT_LINE("Front:", v.front());

        const long& f = v.front();
        if (&f != &v[0]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
    {
        const ft::vector<long, leak_allocator<long> > v(123, 543);

        PRINT_LINE("Front:", v.front());

        const long& f = v.front();
        if (&f != &v[0]) {
            std::cout << "Wrong reference";
            PRINT_FILE_LINE();
        }
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_front();
    CHECK_LEAKS(long);
}
#endif
