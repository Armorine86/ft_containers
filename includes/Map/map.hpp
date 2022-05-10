/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:11:20 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/10 17:23:10 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RBtree.hpp"
#include "pair.hpp"
#include "tree_iterator.hpp"
#include <cstddef>
#include <memory>

namespace ft {

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
	// typedef typename Allocator::reference			  reference;
	// typedef typename Allocator::const_reference	const_reference;
    typedef typename Allocator::pointer 			    pointer;
    typedef typename Allocator::const_pointer 		const_pointer;

    //! Change to tree_iterator
    // typedef tree_iterator<pointer, map> 			  iterator;
    // typedef tree_iterator<const_pointer, map> 	const_iterator;
    // typedef ft::tree_reverse_iterator<iterator> 			  reverse_iterator;
    // typedef ft::tree_reverse_iterator<const_iterator> 	const_reverse_iterator;
    // clang-format on

  public:
    //* ============== NESTED MAP ==============
    class value_compare : public std::binary_function<value_type, value_type, bool> {
        friend class map<Key, T, Compare, Allocator>;

      protected:
        key_compare comp;
        value_compare(key_compare c);

      public:
        typedef bool result_type;
        typedef value_type first_arg_type;
        typedef value_type second_arg_type;
        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
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
    //~ 	const Compare& comp = Compare(),
    //~ 	const Allocator& alloc_ = Allocator()) {}

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
    RBTree<T, Compare, Allocator> rbt_;

}; // class map
} // namespace ft
