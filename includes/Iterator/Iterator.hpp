/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:30 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/12 11:35:29 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator_traits.hpp"
#include "type_traits.hpp"
#include <cstddef>

namespace ft {

//* ============================================
//* |       normal_iterator Class              |
//* ============================================

template <typename It_Type, typename Container>
class normal_iterator {

  protected:
    typedef iterator_traits<It_Type> trait_type;
    It_Type elem;

    // clang-format off
  public:
    typedef It_Type                                 iterator_type;
    typedef typename trait_type::iterator_category  iterator_category;
    typedef typename trait_type::value_type         value_type;
    typedef typename trait_type::difference_type    difference_type;
    typedef typename trait_type::reference          reference;
    typedef typename trait_type::pointer            pointer;
    // clang-format on

    //* ========== Constructors ===========

    normal_iterator() : elem(It_Type()) {}

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

    // obtains container's value_type
    reference operator*() const { return *elem; }
    pointer operator->()  const { return elem; }

    reference operator[](difference_type n) { return elem[n]; }

    normal_iterator& operator+=(difference_type n)  { elem += n; return *this; }
    normal_iterator operator+(difference_type n) const  { return normal_iterator(elem + n); }
    normal_iterator& operator-=(difference_type n)  { elem -= n; return *this; }
    normal_iterator operator-(difference_type n) const   { return normal_iterator(elem - n); }

    /// Returns the underlying base operator
    const iterator_type& base() const { return elem; }
    // clang-format on
};

//* ============================================
//* |        reverse_iterator Class            |
//* ============================================

template <typename It_Type>
class reverse_iterator : public std::iterator<typename iterator_traits<It_Type>::iterator_category,
                                              typename iterator_traits<It_Type>::value_type,
                                              typename iterator_traits<It_Type>::difference_type,
                                              typename iterator_traits<It_Type>::pointer,
                                              typename iterator_traits<It_Type>::reference> {

  protected:
    typedef iterator_traits<It_Type> trait_type;
    It_Type elem;

    // clang-format off
  public:
    typedef          It_Type                                      iterator_type;
    typedef typename iterator_traits<It_Type>::iterator_category  iterator_category;
    typedef typename iterator_traits<It_Type>::value_type         value_type;
    typedef typename iterator_traits<It_Type>::difference_type    difference_type;
    typedef typename iterator_traits<It_Type>::reference          reference;
    typedef typename iterator_traits<It_Type>::pointer            pointer;
    // clang-format on

    reverse_iterator() : elem() {}

    reverse_iterator(const reverse_iterator& it) : elem(it.elem) {}

    explicit reverse_iterator(iterator_type it) : elem(it) {}

    template <typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& it) : elem(it.base()) {}

    ~reverse_iterator(){};

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

    reference operator*() const { It_Type tmp = elem; return *--tmp; }
    pointer operator->() const  { return &(operator*()); }

    reference operator[](difference_type n) const { return *(*this + n); }

    reverse_iterator& operator+=(difference_type n)     { elem -= n; return *this; }
    reverse_iterator operator+(difference_type n) const { return reverse_iterator(elem - n); }
    
    reverse_iterator& operator-=(difference_type n)     { elem += n; return *this; }
    reverse_iterator operator-(difference_type n) const { return reverse_iterator(elem + n); }

    /// Returns the underlying base iterator
    iterator_type base() const { return elem; }
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

template <typename Iter, typename Container>
inline normal_iterator<Iter, Container>
operator+(typename normal_iterator<Iter, Container>::difference_type n,
          const normal_iterator<Iter, Container>& it) {
    return normal_iterator<Iter, Container>(it.base() + n);
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
inline bool operator==(const reverse_iterator<Iter>& left, const reverse_iterator<Iter>& right) {
    return left.base() == right.base();
}

//* ============ NOT EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator!=(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() != right.base();
}

template <typename Iter>
inline bool operator!=(const reverse_iterator<Iter>& left, const reverse_iterator<Iter>& right) {
    return left.base() != right.base();
}

//* ============ SMALLER THAN ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator<(const reverse_iterator<Left_Iter>& left,
                      const reverse_iterator<Right_Iter>& right) {
    return left.base() > right.base();
}

template <typename Iter>
inline bool operator<(const reverse_iterator<Iter>& left, const reverse_iterator<Iter>& right) {
    return left.base() > right.base();
}

//* ============ GREATER THAN ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator>(const reverse_iterator<Left_Iter>& left,
                      const reverse_iterator<Right_Iter>& right) {
    return left.base() < right.base();
}

template <typename Iter>
inline bool operator>(const reverse_iterator<Iter>& left, const reverse_iterator<Iter>& right) {
    return left.base() < right.base();
}

//* ============ SMALLER OR EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator<=(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() >= right.base();
}

template <typename Iter>
inline bool operator<=(const reverse_iterator<Iter>& left, const reverse_iterator<Iter>& right) {
    return left.base() >= right.base();
}

//* ============ GREATER OR EQUAL ============

template <typename Left_Iter, typename Right_Iter>
inline bool operator>=(const reverse_iterator<Left_Iter>& left,
                       const reverse_iterator<Right_Iter>& right) {
    return left.base() <= right.base();
}

template <typename Iter>
inline bool operator>=(const reverse_iterator<Iter>& left, const reverse_iterator<Iter>& right) {
    return left.base() <= right.base();
}

// clang-format off
template <typename Left_Iter, typename Right_Iter>
inline typename reverse_iterator<Left_Iter>::difference_type operator-( const reverse_iterator<Left_Iter>& left,
                                                                        const reverse_iterator<Right_Iter>& right)
{ return right.base() - left.base(); }

template <typename Iter>
inline typename reverse_iterator<Iter>::difference_type operator-(  const reverse_iterator<Iter>& left,
                                                                    const reverse_iterator<Iter>& right)
{ return right.base() - left.base(); }

template <typename Iter>
inline typename reverse_iterator<Iter>::difference_type operator+(  const reverse_iterator<Iter>& left,
                                                                    const reverse_iterator<Iter>& right)
{ return left.base() + right.base();}

template <typename Iter>
inline reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
                                         const reverse_iterator<Iter>& it)
{ return reverse_iterator<Iter>(it.base() - n); }
// clang-format on

} // namespace ft
