/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:38:08 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/24 12:33:21 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.hpp"
#include "pair.hpp"
#include "tree_iterator.hpp"

#include <cassert>
#include <cstddef>
#include <memory>

namespace ft {

template <typename T>
class node;

//* Red Black Tree
template <typename T, typename Compare, typename Allocator>
class RBTree {
    // clang-format off
  public:
    typedef T 												            value_type; // ft::pair<Key, T>
    typedef Compare 										            value_compare; // Compares the Keys
    typedef Allocator 										            allocator_type;
    typedef value_type& 									            reference;
    typedef size_t 											            size_type;
    typedef std::ptrdiff_t 									            difference_type;
    typedef const value_type& 								            const_reference;
    typedef tree_iterator<value_type, difference_type>                  iterator;
    typedef const_tree_iterator<value_type, difference_type>            const_iterator;
    typedef typename Allocator::pointer 					            pointer;
    typedef typename Allocator::const_pointer 				            const_pointer;
    typedef typename node<T>::node_pointer                              node_pointer;
    
    // Rebinds the pair Allocator to a Node allocator
    typedef typename allocator_type::template rebind<node<T> >::other   node_allocator;
    // clang-format on

    /**
    **  ==================================================
    **  |               MEMBER FUNCTIONS                 |
    **  ==================================================
    */

    //* ============== CTORS / DTOR ==============

  public:
    RBTree()
        : node_alloc_(node_allocator()), value_alloc_(allocator_type()), end_(), begin_(), comp_(),
          size_(0) {
        begin_ = node_pointer();
    }

    RBTree(const value_compare& val)
        : node_alloc_(node_allocator()), value_alloc_(allocator_type()), end_(), begin_(),
          comp_(val), size_(0) {

        end_ = node_pointer();
        begin_ = end_;
        insert(val);
        //! Should construct / allocate ?
    }

    RBTree(const RBTree& src)
        : node_alloc_(src.node_alloc_), value_alloc_(src.value_alloc_), end_(), begin_(),
          comp_(src.comp_), size_(0) {

        end_ = node_pointer();
        begin_ = end_;
        insert(src.begin(), src.end());
    }

    RBTree(const value_compare& val, const allocator_type& val_alloc_)
        : node_alloc_(node_allocator()), value_alloc_(val_alloc_), end_(), begin_(), comp_(val),
          size_(0) {

        end_ = node_pointer();
        begin_ = end_;
    }

    RBTree& operator=(const RBTree& rhs) {

        if (this != &rhs) {
            RBTree tmp(rhs);
            swap(tmp);
        }

        return *this;
    }

    //! Needs to Destroy / Deallocate all nodes
    ~RBTree() {}

  public:
    // Returns a copy of the allocator associated with the Set
    allocator_type get_allocator() { return value_alloc_; }

    //* ============== Iterators ==============

    iterator begin() { return iterator(begin_); }
    const_iterator begin() const { return const_iterator(begin_); }
    iterator end() { return iterator(end_); }
    const_iterator end() const { return const_iterator(end_); }

    //* ============== Insert ==============

    // Returns true if the insertion was successful.
    // Returns false if the key already exists in the tree.
    ft::pair<iterator, bool> insert(const value_type& val) {

        bool key_exists = false;

        node_pointer root = get_root();
        node_pointer& found_pos = find_insert_pos(root, val);

        iterator insert_pos(found_pos);

        if (!found_pos) {
            insert_pos = insert_at(found_pos, get_root(), val);
            key_exists = true;
        }

        return ft::make_pair(val, key_exists);
    }

    // Returns an iterator on the inserted node
    iterator insert(iterator pos, const value_type& val) {

        (void)pos;
        insert(val);
    }

    template <typename InputIter>
    void insert(InputIter first, InputIter last) {

        for (; first != last; ++first) {
            insert(*first);
        }
    }

    /**
    **  ==================================================
    **  |           PRIVATE MEMBER FUNCTIONS             |
    **  ==================================================
    */

  private:
    // Starting at root, check each key
    template <typename Key>
    node_pointer& find_insert_pos(node_pointer& current_node, const Key& key) {

        if (!current_node)
            return NULL;

        while (true) {

            // value_compare checks if left param is less than right param
            bool is_less_than = value_compare()(current_node.value, key);

            if (is_less_than) {
                if (!current_node.right)
                    return current_node.right;
                current_node = current_node.right;
            } else if (!is_less_than) {
                if (!current_node.left)
                    return current_node.left;
                current_node = current_node.left;
            } else {
                return current_node;
            }
        }
    }

    // Inserts a node at the specified position [pos] and returns an iterator
    iterator insert_at(node_pointer& pos, node_pointer& parent, const value_type& val) {

        pos = new_node(val);

        pos.parent = parent;

        if (begin_.left)
            begin_.left = begin_.left;

        //! fix_node_colors(get_root(), pos)

        return iterator(pos);
    }
    // Returns a pointer to the root node (left child of end_ node)
    node_pointer get_root() const { return end_.left; }

    /*
     * Returns the left most node in the sub-tree.
     * current_node is considered the root node.
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
     * current_node is considered the root node.
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

    // Allocates a new node.
    node_pointer new_node(const value_type& val) {

        node_pointer new_node = node_alloc_.allocate(1);

        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        value_alloc_.construct(&new_node->value, val);

        return new_node;
    }

  protected:
    node_allocator node_alloc_;  // used to Allocate nodes
    allocator_type value_alloc_; // used to Allocate values in nodes
    node<T> end_;                // Node above root that marks the end of the tree
    node<T> begin_;
    value_compare comp_;
    size_type size_;
    // clang-format on

}; // class RBTree

} // namespace ft
