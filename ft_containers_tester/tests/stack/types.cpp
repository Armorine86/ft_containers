/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:44:00 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/16 02:45:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack.hpp>
#include <stack>
#include <type_traits.hpp>

#define CHECK_TYPE(T, type)                                                                        \
    {                                                                                              \
        if (!ft::is_same<ft::stack<T>::type, std::stack<T>::type>::value) {                        \
            std::cout << "wrong type for ft::stack<" << #T << ">::" << #type << "\n";              \
        }                                                                                          \
    }

#define CHECK_TYPE_CONST(T, type1, type2)                                                          \
    {                                                                                              \
        if (!ft::is_same<ft::stack<T>::type1, const ft::stack<T>::type2>::value) {                 \
            std::cout << "wrong type for ft::stack<" << #T << ">::" << #type1 << "\n";             \
        }                                                                                          \
    }

void stack_check_types()
{
    CHECK_TYPE(float, value_type);
    CHECK_TYPE(float, size_type);
    CHECK_TYPE(char, reference);
    CHECK_TYPE(char, const_reference);
}

#ifndef SINGLE_BINARY
int main()
{
    stack_check_types();
}
#endif
