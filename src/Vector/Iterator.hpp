/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/20 14:38:22 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>

#include "Iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {

/**
 *  Common iterator class.
 *
 *  This class does nothing but define nested typedefs.  %Iterator classes
 *  can inherit from this class to save some work.  The typedefs are then
 *  used in specializations and overloading.
 **/
template <typename T, typename Category, typename Distance = std::ptrdiff_t, typename Pointer = T*,
          typename Reference = T&>
struct iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

//* ============================================
//* |       normal_iterator Class              |
//* ============================================

template <typename It, typename Container>
class normal_iterator : public ft::iterator {
  protected:
    typedef iterator_traits<It> trait_type;
    It elem;

    // clang-format off
  public:
    typedef It iterator_type;
    typedef typename trait_type::iterator_categrory iterator_categrory;
    typedef typename trait_type::value_type         value_type;
    typedef typename trait_type::difference_type    difference_type;
    typedef typename trait_type::reference          reference;
    typedef typename trait_type::pointer            pointer;
    // clang-format on

    //* ========== Constructors ===========

    normal_iterator() : elem(It()) {}
    explicit normal_iterator(const iterator_type& iter) : elem(iter) {}

    template <typename Iter>
    normal_iterator(const normal_iterator<
                    Iter, typename enable_if<is_same<Iter, typename Container::pointer>::value,
                                             Container>::type>& it)
        : elem(it.base()) {}
    ~normal_iterator() {}

    normal_iterator& operator=(const normal_iterator& src) {
        elem = src.elem;
        return *this;
    }

    // clang-format off
  //* ========== Operators ==========
  public:
    normal_iterator& operator++()   { ++elem; return *this; }
    normal_iterator operator++(int) { return normal_iterator(elem++); }
    normal_iterator& operator--()   { --elem; return *this; }
    normal_iterator operator--(int) { return normal_iterator(elem--); }

    reference operator*() { return *elem; } const
    pointer operator->()  { return elem; } const

    reference operator[](difference_type n) { return elem[n]; }

    normal_iterator& operator+=(difference_type n)  { elem += n; return *this; }
    normal_iterator operator+(difference_type n)    { return normal_iterator(elem + n); }
    normal_iterator& operator-=(difference_type n)  { elem -= n; return *this; }
    normal_iterator operator-(difference_type n)    { return normal_iterator(elem - n); }

    const It& base() { return elem; } const
    // clang-format on
};

//* ============================================
//* |        reverse_iterator Class            |
//* ============================================

template <typename It>
class reverse_iterator
    : public std::iterator<
          typename iterator_traits<T>::iterator_category, typename iterator_traits<T>::value_type,
          typename iterator_traits<T>::difference_type, typename iterator_traits<T>::pointer,
          typename iterator_traits<T>::reference> {
  protected:
    typedef iterator_traits<It> trait_type;
    It elem;

    // clang-format off
  public:
    typedef It iterator_type;
    typedef typename trait_type::iterator_categrory iterator_categrory;
    typedef typename trait_type::value_type         value_type;
    typedef typename trait_type::difference_type    difference_type;
    typedef typename trait_type::reference          reference;
    typedef typename trait_type::pointer            pointer;
    // clang-format on
    
    reverse_iterator() : elem(It()) {}
    explicit reverse_iterator(const iterator_type& iter) : elem(iter) {}

    template <typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& it) : elem(it.base()) {}
    ~reverse_iterator() {}

    reverse_iterator& operator=(const reverse_iterator& src) {
        elem = src.elem;
        return *this;
    }

    // clang-format off
  public:
    reverse_iterator& operator++()    { --elem; return *this; }
    reverse_iterator operator++(int)  { reverse_iterator tmp = *this; --elem; return tmp; }
    reverse_iterator& operator--()    { ++elem; return *this; }
    reverse_iterator operator--(int)  { reverse_iterator tmp = *this; ++elem; return tmp; }

    reference operator*() const { return *elem; }
    pointer operator->() const  { return &(operator*()); } 

    reference operator[](difference_type n) const { return *(*this + n); }

    reverse_iterator& operator+=(difference_type n)     { elem -= n; return *this; }
    reverse_iterator operator+(difference_type n) const { return reverse_iterator(elem - n); }
    reverse_iterator& operator-=(difference_type n)     { elem += n; return *this; }
    reverse_iterator operator-(difference_type n) const { return reverse_iterator(elem + n); }

    const It& base() { return elem; } const
    // clang-format on
};

//* ============================================
//* |             BOOL OPERATORS               |
//* ============================================

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator!=(const normal_iterator<Left_Iter, Container>& left,
                       const normal_iterator<Right_Iter, Container>& right) {
    return left.base() == right.base()
}

template <typename Iter, typename Container>
inline bool operator!=(const normal_iterator<Iter, Container>& left,
                       const normal_iterator<Iter, Container>& right) {
    return left.base() == left.base()
}

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator!=(const normal_iterator<Left_Iter, Container>& left,
                       const normal_iterator<Right_Iter, Container>& right) {
    return left.base() != right.base()
}

} // namespace ft
