/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_algorithm.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:23 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/16 14:04:12 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node_types.hpp"
#include <cassert>

namespace ft {
/*
 * Returns the left_most node in the sub-tree
 * X is considered the root node
 */
template <typename NodePtr>
inline NodePtr tree_min(NodePtr x) {

    assert(x != NULL);

    while (x->left != NULL)
        x = x->left;

    return x;
}

/*
 * Returns the right-most node in the sub-tree
 * X is considered the root node
 */
template <typename NodePtr>
inline NodePtr tree_max(NodePtr x) {

    assert(x != NULL);

    while (x->right != NULL)
        x = x->right;

    return x;
}

/*
*	Returns true if the current node is a left child
*/
template <typename NodePtr>
inline bool node_is_left_child(NodePtr x) {
	
    assert(x != NULL);
	
	return x == x->parent->left;
}

/*
* Returns a pointer to the next node
*/ 
template <typename EndNodePtr, typename NodePtr>
inline EndNodePtr tree_iter_next(NodePtr x) {

    assert(x != NULL);

    if (x->right != NULL)
        return tree_min(x->right);

    while (node_is_left_child(x)) {
        x = x->get_parent();
    }

    return x->parent;
}

/*
* Returns a pointer to the previous node
*/ 
template <typename EndNodePtr, typename NodePtr>
inline EndNodePtr tree_iter_prev(NodePtr x) {

    assert(x != NULL);

    if (x->left != NULL)
        return tree_max(x->left);

    NodePtr new_x = static_cast<NodePtr>(x);

    while (node_is_left_child(new_x)) {
        new_x = new_x->get_parent();
    }

    return new_x->parent;
}

template <typename NodePtr>
unsigned int valid_sub_tree(NodePtr x) {
	
	if (x == NULL)
		return true;
	
	// Checks if current node left child points to current node
	if (x->left != NULL && x->left->parent != x)
		return false;

	// Checks if current node right child points to current node
	if (x->right != NULL && x->right->parent != x)
		return false;

	// Checks if current node left and right childs points to same node
	if (x->left == x->right && x->left != NULL)
		return false;

	// if node is Red, neither child can be Red
	if (!x->is_black) {
		if (x->left && !x->left->is_black)
			return false;
		
		if (x->right && !x->right->is_black)
			return false;
	}

    unsigned int height = valid_sub_tree(x->left);
    
    if (height == 0)
        return 0;

    if (height != valid_sub_tree(x->right))
        return 0;
    
    return height + x->is_black;
}

} // namespace ft
