/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:11:20 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/17 12:01:46 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include "RBtree.hpp"
#include "pair.hpp"
#include <__functional/binary_function.h>
#include <cstddef>
#include <memory>

namespace ft {

template <typename Key, typename T, typename Compare>
class map_value_type_compare : public std::binary_function<Key, Key, bool> {

  public:
    // Constructors

    map_value_type_compare() : comp_() {}
    map_value_type_compare(const Compare& cmp) : comp_(cmp) {}

  public:
    // Member Functions

    const Compare& key_comp() const { return comp_; }

    bool operator()(const T& x, const T& y) const { return key_comp()(x.first, y.first); }

    bool operator()(const Key& x, const T& y) const { return key_comp()(x, y.first); }

    bool operator()(const T& x, const Key& y) const { return key_comp()(x.first, y); }

    void swap(map_value_type_compare& src) { std::swap(comp_, src.comp_); }

  private:
    Compare comp_;

}; // class map_value_type_compare

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

    // clang-format off
  public:
    //* ============== Member Types ==============
    typedef Key 									                key_type;
    typedef T 									            	    mapped_type;
    typedef Compare 								              key_compare;
	  typedef Allocator								              allocator_type;
    typedef size_t 									              size_type;
    typedef std::ptrdiff_t 							          difference_type;
    typedef ft::pair<const Key, T> 					      value_type;
    typedef value_type& 							            reference;
    typedef const value_type& 						        const_reference;
    typedef typename Allocator::pointer 			    pointer;
    typedef typename Allocator::const_pointer 		const_pointer;

    private:
      

    typedef tree_iterator<pointer, map> 			    iterator;
    typedef tree_iterator<const_pointer, map> 	  const_iterator;
    typedef ft::reverse_iterator<iterator>        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
    // clang-format on

    //* ============== NESTED CLASS ==============

  public:
    //  Provides a function object that can compare the elements of a map
    //  by comparing the values of their keys to determine their relative order in the map.
    class value_compare : public std::binary_function<value_type, value_type, bool> {

      public:
        friend class map<Key, T, Compare, Allocator>;

        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

      protected:
        key_compare comp_;
        value_compare(const key_compare& comp) : comp_(comp) {}

      public:
        bool operator()(const value_type& x, const value_type& y) const {
            return comp_(x.first, y.first);
        }

    }; // class value_compare

    /**
     **  ==================================================
     **  |               MEMBER FUNCTIONS                 |
     **  ==================================================
     */

    // Default Constructor
    map() {}

    //~ explicit map(const key_compare& comp,
    //~ const Allocator& alloc_ = Allocator()) : alloc_() {}

    //~ template <typename InputIter>
    //~ map(InputIter first, InputIter last,
    //~ const Compare& comp = Compare(),
    //~ const Allocator& alloc_ = Allocator()) {}

    //~ map(const map& src) {}

    //~ map& operator=(const map& src) { *this = src; return *this; }

    // ~map() {}

    //* =============== ITERATORS FUNCTIONS ===============

    //~ iterator begin() {}
    //~ const_iterator begin() const {}
    //~ reverse_iterator rbegin() {}
    //~ const_reverse_iterator rbegin() const {}

    //~ iterator end() {}
    //~ const_iterator end() const {}
    //~ reverse_iterator rend() {}
    //~ const_reverse_iterator rend() const {}

    //* =============== ELEMENT ACCESS FUNCTIONS ===============

    //~ T& at(const Key& key) {}
    //~ const T& at(const Key& key) const {}

    //~ T& operator[](const Key& key) {}

    allocator_type get_allocator() const { return allocator_type(); }

    //* =============== CAPACITY FUNCTIONS ===============

    bool empty() { return size() > 0; }

    size_type size() {}

    size_type max_size() {}

    //* =============== MODIFIERS FUNCTIONS ===============

    //~ void clear();

    //~ ft::pair<iterator, bool> insert(const value_type& value) {}
    //~ iterator insert(iterator hint, const value_type& value) {}

    //~ void erase(iterator pos) {}
    //~ void erase(iterator first, iterator last)
    //~ size_type erase(const Key& key) {}

    //~ void swap(map& src) {}

    //* =============== LOOKUP FUNCTIONS ===============

    //~ size_type count(const Key& key) const {}

    //~ iterator find(const Key& key) {}
    //~ const_iterator find(const Key& key) const {}

    //~ ft::pair<iterator, iterator> equal_range(const Key& key) {}
    //~ ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {}

    //~ iterator lower_bound(const Key& key) {}
    //~ const_iterator lower_bound(const Key& key) const {}

    //~ iterator upper_bound(const Key& key) {}
    //~ const_iterator upper_bound(const Key& key) const {}

    //* =============== OBSERVER FUNCTIONS ===============

    //~ key_compare key_comp() const {}
    //~ map::value_compare value_comp() const {}

    /**
     **  ==================================================
     **  |           PRIVATE MEMBER FUNCTIONS             |
     **  ==================================================
     */

  private:
    RBTree<T, Compare, Allocator> rbtree_;

}; // class map
} // namespace ft
