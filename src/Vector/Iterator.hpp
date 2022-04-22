/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/21 15:36:06 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

#include "Iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {

/**
 *  Common iterator class.
 *
 *  This class does nothing but define nested typedefs.  %Iterator classes
 *  can inherit from this class to save some work.  The typedefs are THAN
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
class normal_iterator {
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

    reference operator*() const { return *elem; }
    pointer operator->()  const { return elem; }

    reference operator[](difference_type n) { return elem[n]; }

    normal_iterator& operator+=(difference_type n)  { elem += n; return *this; }
    normal_iterator operator+(difference_type n)    { return normal_iterator(elem + n); }
    normal_iterator& operator-=(difference_type n)  { elem -= n; return *this; }
    normal_iterator operator-(difference_type n)    { return normal_iterator(elem - n); }

    const iterator_type& base() const { return elem; }
    // clang-format on
};

//* ============================================
//* |        reverse_iterator Class            |
//* ============================================

template <typename It>
class reverse_iterator
    : public ft::iterator<
          typename iterator_traits<It>::iterator_category, typename iterator_traits<It>::value_type,
          typename iterator_traits<It>::difference_type, typename iterator_traits<It>::pointer,
          typename iterator_traits<It>::reference> {
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
    
    ~reverse_iterator() {};

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

    reference operator*() const { It tmp = elem; return *--tmp; }
    pointer operator->() const  { return &(operator*()); }

    reference operator[](difference_type n) const { return *(*this + n); }

    reverse_iterator& operator+=(difference_type n)     { elem -= n; return *this; }
    reverse_iterator operator+(difference_type n) const { return reverse_iterator(elem - n); }
    reverse_iterator& operator-=(difference_type n)     { elem += n; return *this; }
    reverse_iterator operator-(difference_type n) const { return reverse_iterator(elem + n); }

    const iterator_type& base() const { return elem; }
    // clang-format on
};

//* ============================================
//* |     NORMAL ITERATORS BOOL OPERATORS      |
//* ============================================

//* ============ EQUAL ============

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator==(const normal_iterator<Left_Iter, Container>& left,
                       const normal_iterator<Right_Iter, Container>& right) {
    return left.base() == right.base();
}

template <typename Iter, typename Container>
inline bool operator==(const normal_iterator<Iter, Container>& left,
                       const normal_iterator<Iter, Container>& right) {
    return left.base() == right.base();
}

//* ============ NOT EQUAL ============

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator!=(const normal_iterator<Left_Iter, Container>& left,
                       const normal_iterator<Right_Iter, Container>& right) {
    return left.base() != right.base();
}

template <typename Iter, typename Container>
inline bool operator!=(const normal_iterator<Iter, Container>& left,
                       const normal_iterator<Iter, Container>& right) {
    return left.base() != right.base();
}

//* ============ SMALLER THAN ============

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator<(const normal_iterator<Left_Iter, Container>& left,
                      const normal_iterator<Right_Iter, Container>& right) {
    return left.base() < right.base();
}

template <typename Iter, typename Container>
inline bool operator<(const normal_iterator<Iter, Container>& left,
                      const normal_iterator<Iter, Container>& right) {
    return left.base() < right.base();
}

//* ============ GREATER THAN ============
template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator>(const normal_iterator<Left_Iter, Container>& left,
                      const normal_iterator<Right_Iter, Container>& right) {
    return left.base() > right.base();
}

template <typename Iter, typename Container>
inline bool operator>(const normal_iterator<Iter, Container>& left,
                      const normal_iterator<Iter, Container>& right) {
    return left.base() > right.base();
}

//* ============ SMALLER OR EQUAL ============

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator<=(const normal_iterator<Left_Iter, Container>& left,
                       const normal_iterator<Right_Iter, Container>& right) {
    return left.base() <= right.base();
}

template <typename Iter, typename Container>
inline bool operator<=(const normal_iterator<Iter, Container>& left,
                       const normal_iterator<Iter, Container>& right) {
    return left.base() <= right.base();
}

//* ============ GREATER OR EQUAL ============

template <typename Left_Iter, typename Right_Iter, typename Container>
inline bool operator>=(const normal_iterator<Left_Iter, Container>& left,
                       const normal_iterator<Right_Iter, Container>& right) {
    return left.base() >= right.base();
}

template <typename Iter, typename Container>
inline bool operator>=(const normal_iterator<Iter, Container>& left,
                       const normal_iterator<Iter, Container>& right) {
    return left.base() >= right.base();
}

template <typename Left_Iter, typename Right_Iter, typename Container>
inline typename normal_iterator<Left_Iter, Container>::difference_type
operator-(const normal_iterator<Left_Iter, Container>& left,
          const normal_iterator<Right_Iter, Container>& right) {
    return left.base() - right.base();
}

template <typename Iter, typename Container>
inline typename normal_iterator<Iter, Container>::difference_type
operator-(const normal_iterator<Iter, Container>& left,
          const normal_iterator<Iter, Container>& right) {
    return left.base() - right.base();
}

template <typename Iter, typename Container>
inline typename normal_iterator<Iter, Container>::difference_type
operator+(const normal_iterator<Iter, Container>& left,
          const normal_iterator<Iter, Container>& right) {
    return left.base() + right.base();
}

//* ============================================
//* |     REVERSE ITERATORS BOOL OPERATORS     |
//* ============================================

//* ============ EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator==(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() == right.base();
}

template <typename Iter>
inline bool operator==(const reverse_iterator<Iter>& left,
                       const reverse_iterator<Iter>& right) {
    return left.base() == right.base();
}

//* ============ NOT EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator!=(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() != right.base();
}

template <typename Iter>
inline bool operator!=(const reverse_iterator<Iter>& left,
                       const reverse_iterator<Iter>& right) {
    return left.base() != right.base();
}

//* ============ SMALLER THAN ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator<(const reverse_iterator<Left_Iter>& left,
                      const reverse_iterator<Right_Iter>& right) {
    return left.base() < right.base();
}

template <typename Iter>
inline bool operator<(const reverse_iterator<Iter>& left,
                      const reverse_iterator<Iter>& right) {
    return left.base() < right.base();
}

//* ============ GREATER THAN ============
template <typename Left_Iter, typename Right_Iter>
inline bool operator>(const reverse_iterator<Left_Iter>& left,
                      const reverse_iterator<Right_Iter>& right) {
    return left.base() > right.base();
}

template <typename Iter>
inline bool operator>(const reverse_iterator<Iter>& left,
                      const reverse_iterator<Iter>& right) {
    return left.base() > right.base();
}

//* ============ SMALLER OR EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator<=(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() <= right.base();
}

template <typename Iter>
inline bool operator<=(const reverse_iterator<Iter>& left,
                       const reverse_iterator<Iter>& right) {
    return left.base() <= right.base();
}

//* ============ GREATER OR EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator>=(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() >= right.base();
}

template <typename Iter>
inline bool operator>=(const reverse_iterator<Iter>& left,
                       const reverse_iterator<Iter>& right) {
    return left.base() >= right.base();
}

template <typename Left_Iter, typename Right_Iter>
inline typename reverse_iterator<Left_Iter>::difference_type
operator-(const reverse_iterator<Left_Iter>& left,
          const reverse_iterator<Right_Iter>& right) {
    return left.base() - right.base();
}

template <typename Iter>
inline typename reverse_iterator<Iter>::difference_type
operator-(const reverse_iterator<Iter>& left,
          const reverse_iterator<Iter>& right) {
    return left.base() - right.base();
}

template <typename Iter>
inline typename reverse_iterator<Iter>::difference_type
operator+(const reverse_iterator<Iter>& left,
          const reverse_iterator<Iter>& right) {
    return left.base() + right.base();
}

} // namespace ft
