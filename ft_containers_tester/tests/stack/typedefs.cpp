/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:15:13 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/01 22:56:06 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.hpp>

#define CHECK_TYPEDEF(type)                                                                        \
    {                                                                                              \
        ft::stack<int>::type a = ft::stack<int>::type();                                           \
        (void)a;                                                                                   \
    }

void vec_check_typedefs()
{
    CHECK_TYPEDEF(container_type);
    CHECK_TYPEDEF(value_type);
    CHECK_TYPEDEF(size_type);

    {
        ft::stack<int>::value_type a = 10;
        ft::stack<int>::reference b = a;
        ft::stack<int>::const_reference c = a;
        (void)a;
        (void)b;
        (void)c;
    }
}
