/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 08:41:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/02 20:24:36 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>

namespace ft {

//* Iterator_traits template

template <typename T>
struct iterator_traits {
    typedef typename T::iterator_category iterator_category;
    typedef typename T::reference reference;
    typedef typename T::pointer pointer;
    typedef typename T::value_type value_type;
    typedef typename T::difference_type difference_type;
};

//* T* Specialication

template <typename T>
struct iterator_traits<T*> {
    typedef T* pointer;
    typedef T& reference;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
};

//* T& Specialization
template <typename T>
struct iterator_traits<const T*> {
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
};
} // namespace ft
