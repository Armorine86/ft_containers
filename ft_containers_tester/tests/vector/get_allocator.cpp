/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_allocator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:56:24 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:54:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_allocator()
{
    ft::vector<int, leak_allocator<int> > v;

    leak_allocator<int> alloc = v.get_allocator();

    int* buff = alloc.allocate(2048 * 5);

    std::cout << "a leak is normal here\n";
    CHECK_LEAKS(int);

    alloc.deallocate(buff, 2048 * 5);
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_allocator();
    CHECK_LEAKS(int);
}
#endif
