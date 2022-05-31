/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:38:08 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/30 20:24:48 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.hpp"
#include "pair.hpp"
#include "tree_algorithm.hpp"
#include "tree_iterator.hpp"

#include "colors.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

namespace ft {

template <typename T>
class node;

//* Red Black Tree
template <typename T, typename Compare, typename Allocator, typename Node = ft::node<T> >
class RBTree {
    // clang-format off
  public:
    typedef T 												    value_type; // ft::pair<Key, T>
    typedef Compare 										    value_compare; // Compares the Keys
    typedef Allocator 										    allocator_type;
    typedef value_type& 									    reference;
    typedef size_t 											    size_type;
    typedef std::ptrdiff_t 									    difference_type;
    typedef const value_type& 								    const_reference;
    typedef tree_iterator<value_type, difference_type>          iterator;
    typedef const_tree_iterator<value_type, difference_type>    const_iterator;
    typedef typename Allocator::pointer                         pointer;
    typedef typename Allocator::const_pointer 				    const_pointer;
    typedef Node*                                               node_pointer;

    
    // Rebinds the value Allocator to a Node allocator
    typedef typename allocator_type::template rebind<Node >::other   node_allocator;

    // clang-format on
    /**
    **  ==================================================
    **  |               MEMBER FUNCTIONS                 |
    **  ==================================================
    */

    //* ============== CTORS / DTOR ==============

  public:
    // RBTree()
    //     : node_alloc_(node_allocator()), value_alloc_(allocator_type()), end_(), begin_(),
    //       right_end_(), comp_(), size_(0) {
    //       }

    RBTree(const value_compare& val)
        : node_alloc_(node_allocator()), value_alloc_(allocator_type()), end_(), begin_(),
          right_end_(), comp_(val), size_(0) {
        (void)val;
        end_ = new_node();
        begin_ = end_;
        right_end_ = end_;
    }

    RBTree(const RBTree& src)
        : node_alloc_(src.node_alloc_), value_alloc_(src.value_alloc_), end_(), comp_(src.comp_),
          size_(0) {

        insert(src.begin(), src.end());
    }

    // RBTree(const value_compare& val, const allocator_type& val_alloc_)
    //     : node_alloc_(node_allocator()), value_alloc_(val_alloc_), end_(), comp_(val), size_(0)
    //     {}

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

        if (size_ == 0) {
            init_tree(val);
            get_root()->is_black = true;
            iterator it(begin_);
            key_exists = true;
            return ft::make_pair(it, key_exists);
        }

        iterator parent(get_root());
        node_pointer& pos = find_insert_pos(parent, val);

        iterator it(pos);

        if (!pos) {
            pos = new_node(val);
            pos->parent = parent.base();
            it = iterator(pos);
            key_exists = true;
            insert_fix(pos);
        }

        if (begin_->left)
            begin_ = begin_->left;
        if (right_end_->parent && right_end_->right)
            right_end_ = right_end_->right;

        return ft::make_pair(it, key_exists);
    }

    // Returns an iterator on the inserted node
    iterator insert(iterator pos, const value_type& val) {

        (void)pos;
        return insert(val).first;
        // insert(val);
    }

    template <typename InputIter>
    void insert(InputIter first, InputIter last) {

        for (; first != last; ++first) {
            insert(*first);
        }
    }

    // Prints the tree layout
    void printTree() {
        if (get_root()) {
            printHelper(get_root(), "", false);
        }
    }

    void printHelper(node_pointer root, std::string indent, bool last) {
        if (root != NULL) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "   ";
            } else {
                std::cout << "L----";
                indent += "|  ";
            }

            if (root->is_black)
                std::cout << D_GREY;
            else
                std::cout << BRED;

            std::cout << root->value.first << END << std::endl;
            printHelper(root->right, indent, true);
            printHelper(root->left, indent, false);
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
    node_pointer& find_insert_pos(iterator& parent, const Key& key) const {

        iterator current_node = get_root();
        node_pointer* ptr = get_root_ptr();

        while (true) {

            // value_compare checks if left parameter is less than right parameter
            if (value_compare()(current_node.base()->value, key)) {
                if (!current_node.base()->right) {
                    return current_node.base()->right;
                }
                ptr = &current_node.base()->right;
                if (parent.base()->right)
                    parent = parent.base()->right;
                current_node = current_node.base()->right;

            } else if (value_compare()(key, current_node.base()->value)) {
                if (!current_node.base()->left) {
                    return current_node.base()->left;
                }
                ptr = &current_node.base()->left;
                if (parent.base()->left)
                    parent = parent.base()->left;
                current_node = current_node.base()->left;

            } else {
                return *ptr;
            }
        }
    }

    // Returns a pointer to the root node (left child of end_ node)
    Node* get_root() const { return end_->left; }

    Node** get_root_ptr() const { return &end_->left; }

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

    // Allocates a new node and construct the passed value.
    Node* new_node(const value_type& val) {

        Node* new_node = node_alloc_.allocate(1);

        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        new_node->is_black = false;
        value_alloc_.construct(&new_node->value, val);
        size_++;

        return new_node;
    }

    // allocates an empty new node
    Node* new_node() {

        Node* new_node = node_alloc_.allocate(1);

        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;

        return new_node;
    }

    // Init an empty node with no value
    void init_tree(const value_type& val) {
        end_->left = new_node(val);
        begin_ = end_->left;
        begin_->parent = end_;
        right_end_ = begin_;
    }

    // Returns a pointer to the current_node grand parent node
    //
    //                   (B) <--- grand-parent
    //                  /   \
    //                (D)     (A) <--- parent
    //                       /
    //                     (Z) <--- current-node
    node_pointer get_grandparent(node_pointer& current_node) {
        return current_node->parent->parent;
    }

    // Returns a pointer to the left child of the current_node grand parent node
    //
    //                   (B)
    //                  /   \
    //    uncle ---> (D)     (A)
    //                       /
    //                     (Z) <--- current-node
    node_pointer get_uncle(node_pointer& current_node) {

        return get_grandparent(current_node)->left;
    }

    // Case 1: if new_node is root and is RED
    void case_1(node_pointer& new_node) {

        if (get_root() == new_node && !new_node->is_black) {
            new_node->is_black = true;
        }
    }

    // Case 2: new_node's uncle is RED ---> Recolor
    void case_2(node_pointer& new_node) {

        node_pointer uncle = get_uncle(new_node);

        if (!uncle || uncle->is_black) {

            // Red Uncle --> Recolor Black
            if (uncle)
                uncle->is_black = true;

            // Black G-P && Not Root --> Recolor RED
            get_grandparent(new_node)->is_black = get_grandparent(new_node) == get_root();

            // Red Parent --> Recolor Black
            new_node->parent->is_black = true;
        }
        std::cout << "\n\n----------INSIDE CASE 2------------" << std::endl;
        printTree();
    }

    // Case 3.1 -> New_node, parent and Grand parent forms a triangle AND uncle is black or NULL
    // Case 3.2 -> New_node, Parent and Grand parent forms a line (all left or right childs)
    void case_3(node_pointer& new_node) {

        node_pointer uncle = get_uncle(new_node);

        // If uncle is either NULL or Black
        if (!uncle || uncle->is_black) {

            // New_node, Parent and Grand-Parent forms a <triangle>
            if (node_is_left_child(new_node) && !node_is_left_child(new_node->parent)) {
                right_rotate(new_node->parent);

            } else if (!node_is_left_child(new_node) && node_is_left_child(new_node->parent)) {
                left_rotate(new_node->parent);
            }
            
        } else {

            if (node_is_left_child(new_node) && node_is_left_child(new_node->parent)) {
            
            } else if (!node_is_left_child(new_node) && !node_is_left_child(new_node->parent)) {
            
            } 
        }
    }

    // Fixes and Rebalance the tree based on several Cases.
    // Case 1: Root must always be black.
    // Case 2: new_node's uncle is RED
    // Case 3: Parent of the inserted node is also RED
    void insert_fix(node_pointer& new_node) {

        if (size_ > 1) {
            // CASE 1 --> Root must always be black
            case_1(new_node);

            // CASE 2 --> new_node's uncle is RED -> Recolor
            case_2(new_node);
            
            // CASE 3 --> new_node's Uncle is Black
            while (new_node->parent->is_black == false)
                case_3(new_node);
        }
    }

    void left_rotate(node_pointer& current_node) {

        current_node->right->parent = current_node->parent;
        current_node->right->left = current_node;
        current_node->parent->left = current_node->right;
        current_node->parent = current_node->right;
        current_node->right = NULL;
    }

    void right_rotate(node_pointer& current_node) {

        current_node->left->parent = current_node->parent;
        current_node->left->right = current_node;
        current_node->parent->right = current_node->left;
        current_node->parent = current_node->left;
        current_node->left = NULL;
    }

    // clang-format off
  private:
    node_allocator      node_alloc_;    // used to Allocate nodes
    allocator_type      value_alloc_;   // used to Allocate values in nodes
    node_pointer        end_;           // Node above root that marks the end of the tree
    node_pointer        begin_;
    node_pointer        right_end_;
    value_compare       comp_;
    size_type           size_;
    // clang-format on
}; // class RBTree

} // namespace ft
