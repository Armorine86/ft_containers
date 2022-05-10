/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:30:15 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/10 15:37:42 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft {

template <typename T>
class end_node;

template <typename T>
class tree_node;

template <typename T>
struct node_types {
    typedef end_node<T> end_node_type;
    typedef end_node_type* end_node_pointer;
    typedef tree_node<T> tree_node_type;
    typedef tree_node_type* tree_pointer;
};

// End_node is a node that lives above the root node (standard node)
// that marks the end of the tree. Only contains a pointer to left child.
template <typename T>
class end_node {
  public:
    typedef typename node_types<T>::tree_pointer tree_pointer;
    tree_pointer left;

  public:
    end_node() : left(NULL) {}
};

// clang-format off

// Tree_node is the standard node that will populator your Red Black Tree.
// Inherits from end_node to be able to cast from one to the other.
// (Unsafe according to LLVM but they did it anyway!)
template <typename T>
class tree_node {
  public:
    typedef typename node_types<T>::end_node 	end_node_pointer;
    typedef typename node_types<T>::tree_node 	tree_pointer;

  public:
    tree_node() : right(), parent(), color() {}
	
	tree_pointer get_parent() { return static_cast<tree_pointer>(parent); }
	void set_parent(tree_pointer ptr) { parent = static_cast<end_node_pointer>(ptr); }

  public:
    T 					value;
    bool 				color;
    tree_pointer 		right;
    end_node_pointer 	parent;
    // clang-format on
};
} // namespace ft
