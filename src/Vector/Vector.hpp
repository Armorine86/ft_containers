/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/22 09:28:56 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "Iterator.hpp"

namespace ft {

template <typename T, typename Alloc = std::allocator<T> >
class vector {
  public:
    // *** Member Types ***
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef allocator_type::pointer pointer;
    typedef const allocator_type::const_reference const_reference:
    typedef const allocator_type::const_pointer const_pointer:

    // *** Member Functions ***
};
} // namespace ft
