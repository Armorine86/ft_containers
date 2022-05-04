/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:24:45 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:44:29 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_at()
{
    {
        ft::vector<char> v(64, 'a');

        try {
            char& c = v.at(38);

            PRINT_LINE("At:", c);

        } catch (std::out_of_range& e) {
            std::cout << "Wrong out of range exception " << 38;
            PRINT_FILE_LINE();
        }
        CATCH_UNHANDLED_EX();
    }
    {
        std::size_t arr[10240];
        iota(arr, &arr[10240], 12345);
        ft::vector<std::size_t> v(arr, &arr[10240]);

        try {
            std::size_t& c = v.at(10240);

            PRINT_LINE("At:", c);
        } catch (std::out_of_range& e) {
            std::cout << "out of range exception " << 10240;
            PRINT_FILE_LINE();
        } catch (...) {
            std::cout << "unhandled exception";
            PRINT_FILE_LINE();
        }
    }
    {
        ft::vector<std::size_t> v;

        try {
            std::size_t& c = v.at(0);

            PRINT_LINE("At:", c);
        } catch (std::out_of_range& e) {
            std::cout << "out of range exception " << 0;
            PRINT_FILE_LINE();
        }
        CATCH_UNHANDLED_EX();
    }
    {
        const ft::vector<char> v(64, 'a');

        try {
            const char& c = v.at(38);

            PRINT_LINE("At:", c);

        } catch (std::out_of_range& e) {
            std::cout << "Wrong out of range exception " << 38;
            PRINT_FILE_LINE();
        }
        CATCH_UNHANDLED_EX();
    }
    {
        std::size_t arr[10240];
        iota(arr, &arr[10240], 12345);
        const ft::vector<std::size_t> v(arr, &arr[10240]);

        try {
            const std::size_t& c = v.at(10240);

            PRINT_LINE("At:", c);
        } catch (std::out_of_range& e) {
            std::cout << "out of range exception " << 10240;
            PRINT_FILE_LINE();
        }
        CATCH_UNHANDLED_EX();
    }
    {
        const ft::vector<std::size_t> v;

        try {
            const std::size_t& c = v.at(0);

            PRINT_LINE("At:", c);
        } catch (std::out_of_range& e) {
            std::cout << "out of range exception " << 0;
            PRINT_FILE_LINE();
        }
        CATCH_UNHANDLED_EX();
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_at();
    CHECK_LEAKS(std::size_t);
    CHECK_LEAKS(char);
}
#endif
