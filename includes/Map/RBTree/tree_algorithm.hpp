/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_algorithm.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:23 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/17 15:10:50 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node_types.hpp"
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

    assert(current_node != NULL);

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

    while (node_is_left_child(current_node)) {
        current_node = current_node->get_parent();
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
        new_current_node = new_current_node->get_parent();
    }

    return new_current_node->parent;
}

/*
 *   Returns the height of the tree black nodes
 */
template <typename NodePtr>
unsigned int valid_sub_trees(NodePtr current_node) {

    if (current_node == NULL)
        return true;

    // Checks if current node left child points to current node
    if (current_node->left != NULL && current_node->left->parent != current_node)
        return false;

    // Checks if current node right child points to current node
    if (current_node->right != NULL && current_node->right->parent != current_node)
        return false;

    // Checks if current node left and right childs points to same node
    if (current_node->left == current_node->right && current_node->left != NULL)
        return false;

    // if node is Red, neither child can be Red
    if (!current_node->is_black) {
        if (current_node->left && !current_node->left->is_black)
            return false;

        if (current_node->right && !current_node->right->is_black)
            return false;
    }

    // Recursively checks each left child
    unsigned int height = valid_sub_tree(current_node->left);

    if (height == 0)
        return 0;

    // Recursively checks each right child
    if (height != valid_sub_tree(current_node->right))
        return 0;

    return height + current_node->is_black; // Returns the height of the Tree
}

/*
 *   Returns true if the tree is a valid Red-Black Tree
 */
template <typename NodePtr>
inline bool valid_RBtree(NodePtr root) {

    // If there is no tree, returns true
    if (root == NULL)
        return true;

    // if Root node has no parent (end_node), Tree is invalid
    if (root->parent == NULL)
        return false;

    // if Root is not the left child of the end_node, Tree is invalid
    if (!node_is_left_child(root))
        return false;

    // Root node is always Black, otherwise Tree if invalid
    if (!root->is_black)
        return false;

    // Returns false if each sub nodes (Sub Trees) are valid
    return valid_sub_trees(root) != 0;
}

/*
 *   A leaf is a node which both left and right childs are NULL.
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
