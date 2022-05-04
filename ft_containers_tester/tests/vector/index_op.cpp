/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_op.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:26:08 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:48:39 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_index_op()
{
    {
        ft::vector<int, leak_allocator<int> > v(1);

        PRINT_LINE("Value [0]:", v[0]);

        try {
            int& value = v[0];
            int& value2 = v.at(0);
            int& value3 = v.front();

            if (&value != &value2 || &value != &value3) {
                std::cout << "Index reference error";
                PRINT_FILE_LINE();
            }
        }
        CATCH_UNHANDLED_EX();
    }
    {
        ft::vector<int, leak_allocator<int> > v(10000);

        iota(&v[0], &v[10000], 9876);

        PRINT_LINE("Value v[9999]:", v[9999]);

        try {
            int& value = v[9999];
            int& value2 = v.at(9999);

            if (&value != &value2) {
                std::cout << "Index reference error";
                PRINT_FILE_LINE();
            }
        }
        CATCH_UNHANDLED_EX();
    }
    {
        const ft::vector<int, leak_allocator<int> > v(1);

        PRINT_LINE("Value [0]:", v[0]);

        try {
            const int& value = v[0];
            const int& value2 = v.at(0);
            const int& value3 = v.front();

            if (&value != &value2 || &value != &value3) {
                std::cout << "Index reference error";
                PRINT_FILE_LINE();
            }
        }
        CATCH_UNHANDLED_EX();
    }
    {
        ft::vector<int, leak_allocator<int> > v(10000);

        iota(&v[0], &v[10000], 9876);

        const ft::vector<int, leak_allocator<int> > v1(&v[0], &v[10000]);

        PRINT_LINE("Value v[9999]:", v1[9999]);

        try {
            const int& value = v1[9999];
            const int& value2 = v1.at(9999);

            if (&value != &value2) {
                std::cout << "Index reference error";
                PRINT_FILE_LINE();
            }
        }
        CATCH_UNHANDLED_EX();
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_index_op();
    CHECK_LEAKS(int);
}
#endif
