/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_algorithm.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:23 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/31 12:33:09 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cassert>

namespace ft {

/*
 * Returns the left most node in the sub-tree.
 * current_node is considered the root node
 */
template <typename NodePtr>
inline NodePtr tree_min(NodePtr current_node) {

    assert(current_node != NULL);

    while (current_node->left != NULL)
        current_node = current_node->left;

    return current_node;
}

/*
 * Returns the right most node in the sub-tree
 * current_node is considered the root node
 */
template <typename NodePtr>
inline NodePtr tree_max(NodePtr current_node) {

    assert(current_node != NULL);

    while (current_node->right != NULL)
        current_node = current_node->right;

    return current_node;
}

/*
 *	Returns true if the current node is a left child
 */
template <typename NodePtr>
inline bool node_is_left_child(NodePtr current_node) {

    return current_node == current_node->parent->left;
}

/*
 * Returns a pointer to the necurrent_nodet node
 */
template <typename EndNodePtr, typename NodePtr>
inline EndNodePtr tree_iter_next(NodePtr current_node) {

    assert(current_node != NULL);

    if (current_node->right != NULL)
        return tree_min(current_node->right);

    while (!node_is_left_child(current_node)) {
        current_node = current_node->parent;
    }

    return current_node->parent;
}

/*
 *   Returns a pointer to the previous node
 */
template <typename EndNodePtr, typename NodePtr>
inline EndNodePtr tree_iter_prev(NodePtr current_node) {

    assert(current_node != NULL);

    if (current_node->left != NULL)
        return tree_max(current_node->left);

    NodePtr new_current_node = static_cast<NodePtr>(current_node);

    while (node_is_left_child(new_current_node)) {
        new_current_node = new_current_node->parent;
    }

    return new_current_node->parent;
}

/*
 *   A leaf is a node which either left or right childs are NULL.
 *   They are the extremities of the tree
 */
template <typename NodePtr>
NodePtr tree_leaf(NodePtr x) {

    while (x->right != NULL || x->left != NULL) {

        if (x->left != NULL) {
            x = x->left;
            continue;
        }

        if (x->right != NULL) {
            x = x->right;
            continue;
        }
    }
    return x;
}

} // namespace ft
