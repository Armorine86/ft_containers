/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/14 14:34:36 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

namespace ft {

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
  public:
    typedef Alloc                                      allocator_type;
    typedef T                                          value_type;
    typedef T&                                         reference;
    typedef T*                                         pointer;
    typedef const T&                                   const_reference;
    typedef const T*                                   const_pointer;
    typedef random_access_iterator<value_type>         iterator;
    typedef random_access_iterator<const value_type>   const_iterator;
    typedef ft::reverse_iterator<iterator>             reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;
    typedef iterator_traits<iterator>::difference_type difference_type;
    typedef
};
} // namespace ft
