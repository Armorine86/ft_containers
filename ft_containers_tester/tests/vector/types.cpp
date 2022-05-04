/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:47:07 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/16 02:48:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <type_traits.hpp>
#include <vector.hpp>
#include <vector>

#define CHECK_TYPE(T, type)                                                                        \
    {                                                                                              \
        if (!ft::is_same<ft::vector<T>::type, std::vector<T>::type>::value) {                      \
            std::cout << "wrong type for ft::vector<" << #T << ">::" << #type << "\n";             \
        }                                                                                          \
    }

#define CHECK_TYPE_CONST(T, type1, type2)                                                          \
    {                                                                                              \
        if (!ft::is_same<ft::vector<T>::type1, const ft::vector<T>::type2>::value) {               \
            std::cout << "wrong type for ft::vector<" << #T << ">::" << #type1 << "\n";            \
        }                                                                                          \
    }

void vec_check_types()
{
    CHECK_TYPE(float, value_type);
    CHECK_TYPE(float, allocator_type);
    CHECK_TYPE(float, size_type);
    CHECK_TYPE(char, difference_type);
    CHECK_TYPE(char, reference);
    CHECK_TYPE(char, const_reference);
    CHECK_TYPE_CONST(short, const_iterator, iterator);
    CHECK_TYPE_CONST(short, const_reverse_iterator, reverse_iterator);
}

#ifndef SINGLE_BINARY
int main()
{
    vec_check_types();
}
#endif
