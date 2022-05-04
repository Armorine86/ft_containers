/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:50:52 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:46:57 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_data()
{
    {
        ft::vector<long, leak_allocator<long> > v(123, 543);

        PRINT_LINE("Value at data:", *v.data());

        if (v.data() != &v[0]) {
            PRINT_MSG("Bad data pointer");
        }
    }
    {
        ft::vector<long, leak_allocator<long> > v(1, 543);

        PRINT_LINE("Value at data:", *v.data());

        if (v.data() != &v.front()) {
            PRINT_MSG("Bad data pointer");
        }
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_data();
    CHECK_LEAKS(long);
}
#endif
