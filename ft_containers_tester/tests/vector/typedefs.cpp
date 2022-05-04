/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:42:46 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/16 02:48:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.hpp>

#define CHECK_TYPEDEF(type)                                                                        \
    {                                                                                              \
        ft::vector<int>::type a = ft::vector<int>::type();                                         \
        (void)a;                                                                                   \
    }

void vec_check_typedefs()
{
    CHECK_TYPEDEF(value_type);
    CHECK_TYPEDEF(allocator_type);
    CHECK_TYPEDEF(size_type);
    CHECK_TYPEDEF(difference_type);
    CHECK_TYPEDEF(pointer);
    CHECK_TYPEDEF(const_pointer);
    CHECK_TYPEDEF(iterator);
    CHECK_TYPEDEF(const_iterator);
    CHECK_TYPEDEF(reverse_iterator);
    CHECK_TYPEDEF(const_reverse_iterator);

    {
        ft::vector<int>::value_type a = 10;
        ft::vector<int>::reference b = a;
        ft::vector<int>::const_reference c = a;
        (void)a;
        (void)b;
        (void)c;
    }
}
