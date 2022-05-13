/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:34:32 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/13 13:07:52 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node_types.hpp"
#include "algorithm.hpp"

#include <iterator>

namespace ft {

template <typename T, typename Diff>
class const_tree_iterator;

template <typename T, typename Diff>
class tree_iterator {

  private:
    typedef typename node_types<T>::end_node_pointer end_node_pointer;
    typedef typename node_types<T>::node_pointer node_pointer;

    //* ============== Member Types ==============

  public:
    typedef T value_type;
    typedef Diff difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    typedef const_tree_iterator<T, Diff> const_iterator;
    typedef std::bidirectional_iterator_tag iterator_category;

    //* ============== CTOR / DTOR ==============

    tree_iterator() : ptr() {}

    tree_iterator(node_pointer p) : ptr(p) { static_cast<end_node_pointer>(p); }

    tree_iterator(end_node_pointer p) : ptr(p) {}

    //* ============== Member Functions ==============
	
	end_node_pointer base() { return ptr; }

	const end_node_pointer base() const { return ptr; }
	
	node_pointer get_node_ptr() const { return static_cast<node_pointer>(ptr); }

	reference operator*() const { get_node_ptr()->value ; }

	reference& operator->() const { return &(operator*()); }

	tree_iterator operator++() {
		
		//? Implement tree_iter_next
		//ptr = tree_iter_next<end_node_pointer>(static_cast<node_pointer>(ptr));
		return *this;
	}

	tree_iterator& operator++(int) {
		
		tree_iterator it(*this);
		++(*this);
		return it;
	}

	tree_iterator operator--() {
		
		//? Implement tree_iter_next
		//ptr = tree_iter_prev<node_pointer>(ptr));
		return *this;
	}

	tree_iterator& operator--(int) {
		
		tree_iterator it(*this);
		--(*this);
		return it;
	}

    //* ============== Bool Operators ==============


	bool operator==(tree_iterator& rhs) const { return ptr == rhs.ptr; }
	bool operator==(const_iterator& rhs) const { return ptr == rhs.base(); }
	
	bool operator!=(tree_iterator& rhs) const { return !(*this == rhs); }
	bool operator!=(const_iterator& rhs) const { return !(*this == rhs); }
	
  private:
    end_node_pointer ptr;

}; // class tree_iterator

template <typename T, typename Diff>
class const_tree_iterator {

  private:
    typedef typename node_types<T>::end_node_pointer end_node_pointer;
    typedef typename node_types<T>::node_pointer node_pointer;

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

    const_tree_iterator(node_pointer p) : ptr(p) { static_cast<end_node_pointer>(p); }

    const_tree_iterator(end_node_pointer p) : ptr(p) {}

	const_tree_iterator(non_const_iterator it) : ptr(it.base()) {}

    //* ============== Member Functions ==============
	
	end_node_pointer base() { return ptr; }

	const end_node_pointer base() const { return ptr; }
	
	node_pointer get_node_ptr() const { return static_cast<node_pointer>(ptr); }

	reference operator*() const { get_node_ptr()->value ; }

	reference& operator->() const { return &(operator*()); }

	const_tree_iterator operator++() {
		
		//? Implement tree_iter_next
		//ptr = tree_iter_next<end_node_pointer>(static_cast<node_pointer>(ptr));
		return *this;
	}

	const_tree_iterator& operator++(int) {
		
		const_tree_iterator it(*this);
		++(*this);
		return it;
	}

	const_tree_iterator operator--() {
		
		//? Implement tree_iter_next
		//ptr = tree_iter_prev<node_pointer>(ptr));
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
    end_node_pointer ptr;

}; // class const_tree_iterator

} // namespace ft
