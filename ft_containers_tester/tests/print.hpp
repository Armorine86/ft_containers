/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 00:17:50 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 14:38:55 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#define PRINT_FILE_LINE()                                                                          \
    {                                                                                              \
        std::cout << " (file: " << __FILE__ << ", line: " << __LINE__ << ")\n";                    \
    }

#define PRINT_LINE(msg, value)                                                                     \
    {                                                                                              \
        std::cout << msg << " " << value;                                                          \
        PRINT_FILE_LINE();                                                                         \
    }

#define CATCH_UNHANDLED_EX()                                                                       \
    catch (...)                                                                                    \
    {                                                                                              \
        std::cout << "unhandled exception";                                                        \
        PRINT_FILE_LINE();                                                                         \
    }

#define PRINT_MSG(msg)                                                                             \
    {                                                                                              \
        std::cout << msg;                                                                          \
        PRINT_FILE_LINE();                                                                         \
    }

template <typename Iter>
void print_vector(Iter first, Iter last)
{
    for (Iter it = first; it != last; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

#define PRINT_VEC(vec)                                                                             \
    {                                                                                              \
        print_vector(vec.begin(), vec.end());                                                      \
    }

#define PRINT_SIZE_CAP(vec)                                                                        \
    {                                                                                              \
        PRINT_LINE("Size:", vec.size());                                                           \
    }

#define PRINT_ALL(vec)                                                                             \
    {                                                                                              \
        PRINT_SIZE_CAP(vec);                                                                       \
        PRINT_VEC(vec);                                                                            \
    }
