/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 08:41:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/19 13:45:05 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

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
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
};

//* T& Specialization
template <typename T>
struct iterator_traits<const T*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::ptrdiff_t difference_type;
};
} // namespace ft
