/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:30:15 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/13 13:20:15 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft {

template <typename T>
class end_node;

template <typename T>
class tree_node;

// clang-format off
template <typename T>
struct node_types {
    typedef end_node<T>     end_node_type;
    typedef end_node_type*  end_node_pointer;
    typedef tree_node<T>    node_type;
    typedef node_type*      node_pointer;
    // clang-format on
}; // struct node_types

// End_node is a node that lives above the root node (standard node)
// that marks the end of the tree. Only contains a pointer to left child.
template <typename T>
class end_node {
  public:
    typedef typename node_types<T>::node_pointer node_pointer;
    node_pointer left;

  public:
    end_node() : left(NULL) {}

}; // class end_node

// clang-format off

// Tree_node is the standard node that will populate your Red Black Tree.
// Inherits from end_node to be able to cast from one to the other.
template <typename T>
class tree_node : public node_types<T>::end_node_type {

  public:
    enum Node_Color {
      Black,
      Red
    };
    
  public:
    typedef typename node_types<T>::end_node 	  end_node_pointer;
    typedef typename node_types<T>::tree_node 	node_pointer;

  public:
    tree_node() : right(), parent(), color() {}
	
	// Unsafe if parent is the actual end node
	node_pointer get_parent() { return static_cast<node_pointer>(parent); }
	
	void set_parent(node_pointer ptr) { parent = static_cast<end_node_pointer>(ptr); }

  public:
    T 					      value;
    bool 			    	  color;
    node_pointer 		  right;
    end_node_pointer 	parent;
    // clang-format on

}; // class tree_node
} // namespace ft
