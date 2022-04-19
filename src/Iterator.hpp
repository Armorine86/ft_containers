/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec_Iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/14 19:49:43 by mmondell         ###   ########.fr       */
/*         src********************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft
{

//* Iterator_traits template
template<typename Iter>
struct iterator_traits {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::reference reference;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::difference_type difference_type;
};

//* T* Specialication
template<typename T>
struct iterator_traits<T*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
};

//* T& Specialization
template<typename T>
struct iterator_traits<const T*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::ptrdiff_t difference_type;
};

//* Iterator Template
template<typename Category,
         typename T,
         typename Distance = std::ptrdiff_t,
         typename Pointer = T*,
         typename Reference = T&>
struct iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

//* ====================== normal_iterator Class ======================

template<typename It, typename Container>
class normal_iterator
{
  protected:
    typedef iterator_traits<It> trait_type;
    It elem;

  public:
    typedef It iterator_type;
    typedef typename trait_type::iterator_categrory iterator_categrory;
    typedef typename trait_type::value_type value_type;
    typedef typename trait_type::difference_type difference_type;
    typedef typename trait_type::reference reference;
    typedef typename trait_type::pointer pointer;

    //* ========== Constructors ===========

    normal_iterator() : elem(T()) {}
    explicit normal_iterator(const iterator_type& It) : elem(It) {}

    template<typename Iter>
    normal_iterator(
      const normal_iterator < Iter,
      typename enable_if<is_same<Iter, typename Container::pointer>::value, Container>::type& it) : elem(it.base())
};

template<typename T>
class reverse_iterator : iterator<typename iterator_traits<T>::iterator_category,
                                  typename iterator_traits<T>::value_type,
                                  typename iterator_traits<T>::difference_type,
                                  typename iterator_traits<T>::pointer,
                                  typename iterator_traits<T>::reference>
{
  public:
  
};
} // namespace ft
