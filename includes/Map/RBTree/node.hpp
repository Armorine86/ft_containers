/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:30:15 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/24 16:51:44 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft {

template <typename T>
class node;

template <typename T>
class end_node;

// clang-format off
template <typename T>
struct node_types {
  typedef end_node<T>     end_node_type;
  typedef end_node_type*  end_node_pointer;
  typedef node<T>         node_type;
  typedef node_type*      node_pointer;
};
// clang-format on

template <typename T>
class end_node {

  public:
    typedef typename node_types<T>::node_pointer node_pointer;

  public:
    end_node() : left(NULL) {}

  public:
    node_pointer left;
};

// Tree_node is the standard node that will populate your Red Black Tree.
// A Node with a NULL parent pointer marks the end of the tree.
template <typename T>
class node : public end_node<T> {

    // clang-format off
  public:
    typedef typename node_types<T>::node_pointer      node_pointer;
    typedef typename node_types<T>::end_node_pointer  end_node_pointer;

  public:
    node() : is_black(true), right(NULL), parent(NULL) {}

  public:
  
    T                     value; // ft::pair<Key, Value>
    bool                  is_black;
    node_pointer          right;
    end_node_pointer      parent;
    // clang-format on

}; // class tree_node

} // namespace ft
