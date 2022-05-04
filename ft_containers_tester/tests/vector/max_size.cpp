/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_size.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:51:17 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/28 21:05:24 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

struct abc {
    int data[1024];
    long num;
};

void vec_test_max_size()
{
    PRINT_LINE("Unsigned Char max size:", ft::vector<unsigned char>().max_size());
    PRINT_LINE("Char max size:", ft::vector<char>().max_size());
    PRINT_LINE("Int max size:", ft::vector<int>().max_size());
    PRINT_LINE("Long max size:", ft::vector<long>().max_size());
    PRINT_LINE("Short max size:", ft::vector<short>().max_size());
    PRINT_LINE("Abc max size:", ft::vector<abc>().max_size());
    PRINT_LINE("Float max size:", ft::vector<float>().max_size());
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_max_size();
}
#endif
