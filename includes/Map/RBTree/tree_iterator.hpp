/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:34:32 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/03 09:31:30 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.hpp"
#include "tree_utils.hpp"

#include <iterator>

namespace ft {

template <typename T, typename Diff>
class const_tree_iterator;

template <typename T, typename Diff>
class tree_iterator {

  public:
    typedef node<T>* node_pointer;

    //* ============== Member Types ==============
    // clang-format off
  public:
    typedef T                                 value_type;
    typedef Diff                              difference_type;
    typedef value_type&                       reference;
    typedef value_type*                       pointer;
    typedef const_tree_iterator<T, Diff>      const_iterator;
    typedef std::bidirectional_iterator_tag   iterator_category;
    // clang-format on

    //* ============== CTOR / DTOR ==============

    tree_iterator() : ptr() {}

    tree_iterator(node_pointer p) : ptr(p) {}

    //* ============== Member Functions ==============

    node_pointer base() { return ptr; }

    node_pointer base() const { return ptr; }

    reference operator*() const { base()->value; }

    reference& operator->() const { return &(operator*()); }

    tree_iterator& operator++() {

        ptr = tree_iter_next<node_pointer>(ptr);
        return *this;
    }

    tree_iterator operator++(int) {

        tree_iterator it = *this;
        ++(*this);
        return it;
    }

    tree_iterator& operator--() {

        ptr = tree_iter_prev<node_pointer>(ptr);
        return *this;
    }

    tree_iterator operator--(int) {

        tree_iterator it = *this;
        --(*this);
        return it;
    }

    //* ============== Bool Operators ==============

    bool operator==(const tree_iterator& rhs) const { return ptr == rhs.ptr; }
    bool operator==(const const_iterator& rhs) const { return ptr == rhs.base(); }

    bool operator!=(const tree_iterator& rhs) const { return !(*this == rhs); }
    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

  private:
    node_pointer ptr;

}; // class tree_iterator

template <typename T, typename Diff>
class const_tree_iterator {

  private:
    typedef typename node<T>::node_pointer node_pointer;

    //* ============== Member Types ==============

  public:
    typedef T value_type;
    typedef Diff difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    typedef tree_iterator<T, Diff> non_const_iterator;
    typedef std::bidirectional_iterator_tag iterator_category;

    //* ============== CTOR / DTOR ==============

    const_tree_iterator() : ptr() {}

    const_tree_iterator(node_pointer p) : ptr(p) {}

    const_tree_iterator(non_const_iterator it) : ptr(it.base()) {}

    //* ============== Member Functions ==============

    node_pointer base() { return ptr; }

    const node_pointer base() const { return ptr; }

    reference operator*() const { base()->value; }

    reference& operator->() const { return &(operator*()); }

    const_tree_iterator operator++() {

        ptr = tree_iter_next<node_pointer>(ptr);
        return *this;
    }

    const_tree_iterator& operator++(int) {

        const_tree_iterator it(*this);
        ++(*this);
        return it;
    }

    const_tree_iterator operator--() {

        ptr = tree_iter_prev<node_pointer>(ptr);
        return *this;
    }

    const_tree_iterator& operator--(int) {

        const_tree_iterator it(*this);
        --(*this);
        return it;
    }

    //* ============== Bool Operators ==============

    bool operator==(const_tree_iterator& rhs) const { return ptr == rhs.ptr; }
    bool operator==(non_const_iterator& rhs) const { return ptr == rhs.base(); }

    bool operator!=(const_tree_iterator& rhs) const { return !(*this == rhs); }
    bool operator!=(non_const_iterator& rhs) const { return !(*this == rhs); }

  private:
    node_pointer ptr;

}; // class const_tree_iterator

} // namespace ft
