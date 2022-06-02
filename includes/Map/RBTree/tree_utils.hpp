/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:23 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/02 12:12:39 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cassert>
#include <cstddef>

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

// Return TRUE if the node left and right child are NULL
template <typename NodePtr>
bool node_is_leaf(NodePtr node) {

    return !node->left && !node->right;
}

// Returns a NodePtr to the only valid child.
// returns NULL otherwise.
template <typename NodePtr>
NodePtr node_only_child(NodePtr node) {

    if (node->left && !node->right)
        return node->left;
    else if (node->right && !node->left)
        return node->right;
    else
        return NULL;
}

// Finds the largest value in the left subtree of the pointed Node
template <typename NodePtr>
NodePtr find_successor(NodePtr node) {

    while (node->right)
        node = node->right;
    return node;
}

// Swaps the target Node with it's successor
template <typename NodePtr>
void swap_nodes(NodePtr target, NodePtr successor) {

    // Step 1 -> Successor parent becomes leaf, so corresponding child must be NULL
    if (node_is_left_child(successor)) {
        successor->parent->left = NULL;
    } else
        successor->parent->right = NULL;

    // Step 2 -> Swap successor's parent with target's parent
    successor->parent = target->parent;

    //  Step 3 -> If one of the Target's child is the successor
    //  corresponding successor's child must be NULL
    //  Otherwise, you'll have infinite Loop
    if (target->left == successor)
        successor->left = NULL;
    else
        successor->left = target->left;

    if (target->right == successor)
        successor->right = NULL;
    else
        successor->right = target->right;

    //* Step 4 -> If target is parent's left or right child, it must point to successor
    if (node_is_left_child(target)) {
        target->parent->left = successor;
    } else
        target->parent->right = successor;
}

} // namespace ft
