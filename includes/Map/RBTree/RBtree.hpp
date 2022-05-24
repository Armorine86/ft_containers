/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:38:08 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/20 11:09:13 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node_types.hpp"
#include "pair.hpp"
#include "tree_iterator.hpp"

#include <cassert>
#include <cstddef>
#include <memory>

namespace ft {

//* Red Black Tree
template <typename T, typename Compare, typename Allocator>
class RBTree {
    // clang-format off
  public:
    typedef T 												                                  value_type; // pair<Key, T>
    typedef Compare 										                                value_compare;
    typedef Allocator 										                              allocator_type;
    typedef value_type& 									                              reference;
    typedef size_t 											                                size_type;
    typedef std::ptrdiff_t 									                            difference_type;
    typedef const value_type& 								                          const_reference;
    typedef tree_iterator<value_type, difference_type>                  iterator;
    typedef const_tree_iterator<value_type, difference_type>            const_iterator;
    typedef typename Allocator::pointer 					                      pointer;
    typedef typename Allocator::const_pointer 				                  const_pointer;
    typedef typename node_types<T>::end_node_type                       end_node_type;
    typedef typename node_types<T>::end_node_pointer                    end_node_pointer;
    typedef typename node_types<T>::node_type                           node_type;
    typedef typename node_types<T>::node_pointer                        node_pointer;
    typedef typename allocator_type::template rebind<node_type>::other  node_allocator;
    // clang-format on

    /**
    **  ==================================================
    **  |               MEMBER FUNCTIONS                 |
    **  ==================================================
    */

    //* ============== CTORS / DTOR ==============

  public:
    RBTree(const value_compare& val)
        : node_alloc_(node_allocator()), value_alloc_(allocator_type()), end_(), comp_(val),
          size_(0) {

        begin_ = end_node_pointer();
    }

    RBTree(const RBTree& src)
        : node_alloc_(src.node_alloc_), value_alloc_(src.value_alloc_), end_(), comp_(src.comp_),
          size_(0) {

        begin_ = end_node_pointer();
        insert(src.begin(), src.end());
    }

    RBTree(const value_compare& val, const allocator_type& val_alloc_)
        : node_alloc_(node_allocator()), value_alloc_(val_alloc_), end_(), comp_(val), size_(0) {

        begin_ = end_node_pointer();
    }

    RBTree& operator=(const RBTree& rhs) {

        if (this != &rhs) {
            RBTree tmp(rhs);
            swap(tmp);
        }

        return *this;
    }

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
      
      (void)val;
      bool exists = false;
      return ft::make_pair(val, exists);
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
    end_node_type end_;          // Node above root that marks the end of the tree
    end_node_pointer begin_;
    value_compare comp_;
    size_type size_;
    // clang-format on

}; // class RBTree

} // namespace ft
