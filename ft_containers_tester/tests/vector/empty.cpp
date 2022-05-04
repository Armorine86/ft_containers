/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:47:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_empty()
{
    ft::vector<int, leak_allocator<int> > v(0, 123);

    if (v.empty()) {
        PRINT_MSG("Empty v");
    }

    ft::vector<int, leak_allocator<int> > v1;

    if (v1.empty()) {
        PRINT_MSG("Empty v1");
    }

    ft::vector<int, leak_allocator<int> > v2(64);

    if (v2.empty()) {
        PRINT_MSG("Empty v2 b");
    }
    v2.assign(0, 54);
    if (v2.empty()) {
        PRINT_MSG("Empty v2 a");
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_empty();
    CHECK_LEAKS(int);
}
#endif
