/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:23 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/06 15:23:02 by mmondell         ###   ########.fr       */
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

    // Step 1 -> Keep a pointer to target's parent;
    NodePtr T_parent = target->parent;

    if (node_is_left_child(target)) {
        T_parent->left = successor;
    } else {
        T_parent->right = successor;
    }

    target->parent = successor->parent;
    successor->parent = T_parent;

    if (target->left == successor) {
        successor->left = target;
        target->left = NULL;
    } else
        successor->left = target->left;

    if (target->right == successor) {
        successor->right = target;
        target->right = NULL;
    } else
        successor->right = target->right;

    if (successor->left)
        successor->left->parent = successor;
    if (successor->right)
        successor->right->parent = successor;

    if (node_is_left_child(target))
        target->parent->left = target;
    else
        target->parent->right = target;

    target->left = NULL;
    target->right = NULL;

    target->is_black = successor->is_black;

    // // Step 2 -> Switch Both target's and successor's parents
    // target->parent = successor->parent;
    // successor->parent = T_parent;

    // // Step 3 -> Check if successor is a left or right child.
    // // Make it's parent corresponding children point to him
    // if (node_is_left_child(successor)) {
    //     T_parent->left = successor;
    // } else
    //     T_parent->right = successor;

    // // Step 4 -> Check if the Target is the Successor's parent.
    // if (target->left == successor)
    //     successor->left = NULL;
    // else
    //     successor->left = target->left;

    // if (target->right == successor)
    //     successor->right = NULL;
    // else
    //     successor->right = target->right;

    // // Step 5 -> check if Target is a left or right child.
    // // Make it's parent point to him
    // if (node_is_left_child(target)) {
    //     target->parent->left = target;
    // } else
    //     target->parent->right = target;

    // // Step 6 -> target is now the new leaf, both child are NULL
    // target->left = NULL;
    // target->right = NULL;

    // // Step 7 -> Reconnect successor child's parent to the node
    // if (successor->left)
    //     successor->left->parent = successor;
    // if (successor->right)
    //     successor->right->parent = successor;
}

// Returns True if the key is equal to the node's key
template <typename Key, typename Value, typename Compare>
bool is_equal(const Key& key, Value& value, Compare) {

    if (Compare()(key, value) && Compare()(value, key)) {
        return true;
    }
    return false;
    //return Compare()(key, value) && Compare()(value, key);
}

// Returns True if the key is less than the value's key
template <typename Key, typename Value, typename Compare>
bool key_is_less(const Key& key, Value& value, Compare) {

    return (Compare()(key, value));
}

// Returns a pointer to the current_node grand parent node
//
//    (GP) <--- grand-parent.
//   /    \
// (U)    (P) <--- parent.
//        /
//     (X) <--- current-node.
template <typename NodePtr>
NodePtr& get_grandparent(NodePtr& current_node) {
    return current_node->parent->parent;
}

// Returns a pointer to the left child of the current_node grand parent node.
//
//                (GP)
//               /    \
// uncle ---> (U)     (P)
//                    /
//                 (X) <--- current-node.
template <typename NodePtr>
NodePtr& get_uncle_left(NodePtr& current_node) {

    return get_grandparent(current_node)->left;
}

// Returns a pointer to the left child of the current_node grand parent node
//
//           (GP)
//          /    \
//        (P)     (U)<--- uncle
//          \
//           (X) <--- current-node
template <typename NodePtr>
NodePtr& get_uncle_right(NodePtr& current_node) {

    return get_grandparent(current_node)->right;
}

// Returns a pointer to the sibling of the current node
//
//                      (P) <-- Parent
//                     /   \
// current_node --->(X)    (S) <-- Sibling
//                        /   \
//             niece -->(N)   (NE) <-- Nephew
template <typename NodePtr>
NodePtr& get_sibling(NodePtr& current_node) {

    // If current_node is a left chilf, his sibling is his parent's right child
    if (node_is_left_child(current_node))
        return current_node->parent->right;
    else
        return current_node->parent->left;
}

// Returns a pointer to the sibling of the current node
//
//                      (P) <-- Parent
//                     /   \
// current_node --->(X)    (S) <-- Sibling
//                        /   \
//             niece -->(N)   (NE) <-- Nephew
template <typename NodePtr>
NodePtr get_niece(NodePtr& current_node) {

    // If current_node is a left child, the Niece is the left child of
    // current_node's sibling
    if (get_sibling(current_node)) {
        if (node_is_left_child(current_node))
            return get_sibling(current_node)->left;
        else
            return get_sibling(current_node)->right;
    }
    return NULL;
}

// Returns a pointer to the sibling of the current node
//
//                      (P) <-- Parent
//                     /   \
// current_node --->(X)    (S) <-- Sibling
//                        /   \
//             niece -->(N)   (NE) <-- Nephew
template <typename NodePtr>
NodePtr get_nephew(NodePtr& current_node) {

    // If current_node is a left child, the Nephew is the right child of
    // current_node's sibling

    if (get_sibling(current_node)) {
        if (node_is_left_child(current_node))
            return get_sibling(current_node)->right;
        else
            return get_sibling(current_node)->left;
    }
    return NULL;
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
    unsigned int height = valid_sub_trees(current_node->left);

    if (height == 0)
        return 0;

    // Recursively checks each right child
    if (height != valid_sub_trees(current_node->right))
        return 0;

    return height + current_node->is_black; // Returns the height of the Tree (black nodes)
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
} // namespace ft
