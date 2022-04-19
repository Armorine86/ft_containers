/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/19 14:21:26 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>

#include "Iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft
{

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
    typedef typename iterator_traits<It>::iterator_categrory iterator_categrory;
    typedef typename iterator_traits<It>::value_type value_type;
    typedef typename iterator_traits<It>::difference_type difference_type;
    typedef typename iterator_traits<It>::reference reference;
    typedef typename iterator_traits<It>::pointer pointer;

  //* ========== Constructors ===========

    normal_iterator() : elem(It()) {}
    explicit normal_iterator(const iterator_type& iter) : elem(iter) {}

    template<typename Iter>
    normal_iterator(
      const normal_iterator<Iter,
      typename enable_if<is_same<Iter, typename Container::pointer>::value,
                                      Container>::type>& it) :
      elem(it.base()) {}
      ~normal_iterator() {}

      normal_iterator& operator=(const normal_iterator& src)
      {
        elem = src.elem;
        return *this;
      }

  //* ========== Operators ==========
  public:
    normal_iterator& operator++() { ++elem; return *this; }
    normal_iterator operator++(int) { return normal_iterator(elem++); }
    normal_iterator& operator--() { --elem; return *this; }
    normal_iterator operator--(int) { return normal_iterator(elem--); }

    reference operator*() { return *elem; } const
    pointer operator->() { return elem; } const

    reference operator[](difference_type n) { return elem[n]; }

    normal_iterator& operator+=(difference_type n) { elem += n; return *this; }
    normal_iterator operator+(difference_type n) { return normal_iterator(elem + n); }
    normal_iterator& operator-=(difference_type n) { elem -= n; return *this; }
    normal_iterator operator-(difference_type n) { return normal_iterator(elem - n); }

    const It& base() { return elem; } const
};

template<typename T>
class reverse_iterator : public std::iterator<typename iterator_traits<T>::iterator_category,
                                  typename iterator_traits<T>::value_type,
                                  typename iterator_traits<T>::difference_type,
                                  typename iterator_traits<T>::pointer,
                                  typename iterator_traits<T>::reference>
{
  public:
    
};

} // namespace ft
