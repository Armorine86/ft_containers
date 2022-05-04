/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:38:59 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:52:47 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

struct abc {
    abc()
        : data(4),
          num(1000)
    {
    }

    abc(int d, long n)
        : data(d),
          num(n)
    {
    }

    int data;
    long num;
};

void vec_test_reserve()
{
    {
        ft::vector<abc> v;

        PRINT_LINE("Size:", v.size());
        PRINT_LINE("Cap:", v.capacity());

        v.reserve(64);
        PRINT_LINE("Size:", v.size());
        PRINT_LINE("Cap:", v.capacity());

        v.reserve(64);
        PRINT_LINE("Size:", v.size());
        PRINT_LINE("Cap:", v.capacity());

        v.reserve(24);
        PRINT_LINE("Size:", v.size());
        PRINT_LINE("Cap:", v.capacity());

        v.reserve(65);
        PRINT_LINE("Size:", v.size());
        PRINT_LINE("Cap:", v.capacity());

        try {
            v.reserve(v.max_size() + 1);
            PRINT_MSG("Bad reserve");
        } catch (std::length_error&) {
            PRINT_MSG("Length exception");
        }
        CATCH_UNHANDLED_EX();
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_reserve();
    CHECK_LEAKS(abc);
}
#endif
