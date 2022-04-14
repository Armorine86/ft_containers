/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec_Iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/14 15:54:43 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{

template<typename Iter>
struct iterator_traits {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::reference reference;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::difference_type difference_type;
};

template<typename Iter>
struct iterator_traits<Iter*> {
    typedef Iter::iterator_category iterator_category;
    typedef Iter::reference reference;
    typedef Iter::pointer pointer;
    typedef Iter::value_type value_type;
    typedef Iter::difference_type difference_type;
};

template<typename Iter>
struct iterator_traits<const Iter*> {
    typedef Iter::iterator_category iterator_category;
    typedef Iter::reference reference;
    typedef Iter::pointer pointer;
    typedef Iter::value_type value_type;
    typedef Iter::difference_type difference_type;
};

} // namespace ft
