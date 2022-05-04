/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:36:47 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:46:49 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_ctor()
{
    // Default
    {
        ft::vector<int, leak_allocator<int> > v;

        PRINT_ALL(v);
    }
    // Allocator ctor
    {
        std::allocator<double> alloc;
        ft::vector<double> v(alloc);

        PRINT_ALL(v);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_ctor();
    CHECK_LEAKS(double);
    CHECK_LEAKS(int);
}
#endif
