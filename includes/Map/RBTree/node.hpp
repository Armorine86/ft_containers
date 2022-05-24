/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:30:15 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/24 13:57:27 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft {

// Tree_node is the standard node that will populate your Red Black Tree.
// A Node with a NULL parent pointer marks the end of the tree.
template <typename T>
class node {

    // clang-format off
  public:
    typedef node<T>* node_pointer;

  public:
    node() : is_black(true), right(NULL), left(NULL), parent(NULL) {}

  public:
  
    T             value; // ft::pair<Key, Value>
    bool          is_black;
    node_pointer  right;
    node_pointer  left;
    node_pointer  parent;
    // clang-format on

}; // class tree_node

} // namespace ft
