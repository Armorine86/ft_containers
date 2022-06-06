/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:38:08 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/06 14:41:57 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "colors.hpp"
#include "node.hpp"
#include "pair.hpp"
#include "tree_iterator.hpp"
#include "tree_utils.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <ios>
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
    typedef typename allocator_type::pointer                    pointer;
    typedef typename allocator_type::const_pointer 				const_pointer;
    typedef Node*                                               node_pointer;

    
    // Rebinds the value Allocator to a Node allocator
    typedef typename allocator_type::template rebind<Node>::other   node_allocator;
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

    RBTree(const value_compare& val, allocator_type alloc_ = allocator_type())
        : node_alloc_(node_allocator()), value_alloc_(alloc_), end_(), begin_(),
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

    RBTree& operator=(const RBTree& rhs) {

        if (this != &rhs) {
            RBTree tmp(rhs);
            swap(tmp);
        }

        return *this;
    }

    ~RBTree() {
        clear_tree(get_root());

        if (end().base()) {
            value_alloc_.destroy(&end().base()->value);
            node_alloc_.deallocate(end().base(), 1);
        }
    }

  public:
    // Returns a copy of the allocator associated with the Set
    allocator_type get_allocator() { return value_alloc_; }

    /**
    **  ==================================================
    **  |             ITERATORS FUNCTIONS                |
    **  ==================================================
    */

    iterator begin() { return iterator(begin_); }
    const_iterator begin() const { return const_iterator(begin_); }
    iterator end() { return iterator(end_); }
    const_iterator end() const { return const_iterator(end_); }

    /**
    **  ==================================================
    **  |             MODIFIERS FUNCTIONS                |
    **  ==================================================
    */

    //* ============== INSERT ==============

    // Returns true if the insertion was successful.
    // Returns false if the key already exists in the tree.
    ft::pair<iterator, bool> insert(const value_type& val) {

        bool key_exists = false;

        if (empty()) {
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
        }

        if (begin_->left)
            begin_ = begin_->left;
        if (right_end_->parent && right_end_->right)
            right_end_ = right_end_->right;

        insert_fix(pos);

        return ft::make_pair(it, key_exists);
    }

    // Will check if inserted node can fit at hint for insertion optimization,
    // otherwise, will start from root and find insert position.
    iterator insert(iterator hint, const value_type& val) {

        if (empty()) {
            init_tree(val);
            get_root()->is_black = true;

            return iterator(begin_);
        }

        iterator root(get_root());
        node_pointer& pos = find_insert_pos(root, hint, val);

        if (!pos) {
            pos = new_node(val);
            pos->parent = root.base();
        }

        if (begin_->left)
            begin_ = begin_->left;
        if (right_end_->parent && right_end_->right)
            right_end_ = right_end_->right;

        insert_fix(pos);

        return pos;
    }

    template <typename InputIter>
    void insert(InputIter first, InputIter last) {

        for (; first != last; ++first) {
            insert(*first);
        }
    }

    //* ============== ERASE ==============

    void erase(iterator node) {

        node_pointer toBeDeleted = node.base();

        BST_remove(toBeDeleted);

        delete_fix(toBeDeleted);

        delete_node(toBeDeleted);
    }

    template <typename InputIter>
    void erase(InputIter first, InputIter last) {

        for (; first != last; ++first) {
            erase(first);
        }
    }

    template <typename Key>
    size_type erase(const Key& key) {

        iterator pos = find(key);

        if (pos == end())
            return 0;

        erase(pos);

        return 1;
    }

    void clear() { clear_tree(get_root()); }

    void swap(RBTree& src) {

        std::swap(end_, src.end_);
        std::swap(begin_, src.begin_);
        std::swap(right_end_, src.right_end_);
        std::swap(size_, src.size_);
        std::swap(comp_, src.comp_);
    }

    /**
    **  ==================================================
    **  |              CAPACITY FUNCTIONS                |
    **  ==================================================
    */

    // Returns true if tree size is zero
    bool empty() { return size_ == 0; }

    size_type size() const { return size_; }

    size_type max_size() const {
        const size_t diffmax = std::numeric_limits<difference_type>::max();
        const size_t allocmax = node_alloc_.max_size();

        return std::min(diffmax, allocmax);
    }

    /**
     **  ==================================================
     **  |               LOOKUP FUNCTIONS                 |
     **  ==================================================
     */

    template <typename Key>
    size_type count(const Key& key) const {
        if (find(key))
            return 1;
        return 0;
    }

    template <typename Key>
    ft::pair<iterator, iterator> equal_range(const Key& key) {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    template <typename Key>
    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    template <typename Key>
    iterator lower_bound(const Key& key) {

        for (iterator first = begin(); first != end(); ++first) {
            if (key_is_less(key, first.base()->value, value_compare()))
                return --first;
        }
        return end();
    }

    template <typename Key>
    const_iterator lower_bound(const Key& key) const {

        for (iterator first = begin(); first != end(); ++first) {
            if (key_is_less(key, first.base()->value, value_compare()))
                return --first;
        }
        return end();
    }

    template <typename Key>
    iterator upper_bound(const Key& key) {

        for (iterator first = begin(); first != end(); ++first) {
            if (key_is_less(key, first.base()->value, value_compare()))
                return first;
        }
        return end();
    }

    template <typename Key>
    const_iterator upper_bound(const Key& key) const {

        for (iterator first = begin(); first != end(); ++first) {
            if (key_is_less(key, first.base()->value, value_compare()))
                return first;
        }
        return end();
    }

    //* ============== Find ==============

    template <typename Key>
    iterator find(const Key& key) {

        if (!empty()) {

            iterator root(get_root());
            iterator current_node;

            if (is_equal(key, root, value_compare()))
                return root;

            if (key_is_less(key, root.base()->value, Compare())) {
                current_node = begin();
            } else
                current_node = iterator(right_end_);

            if (current_node == begin()) {

                for (; current_node != root; ++current_node) {
                    if (!is_equal(key, current_node, Compare())) {
                        continue;
                    }
                    //  Found Key
                    return current_node;
                }

            } else {

                for (; current_node != root; --current_node) {
                    if (!is_equal(key, current_node, Compare())) {
                        continue;
                    }
                    // Found Key
                    return current_node;
                }
            }
        }

        // Key Not Found
        return end();
    }

    template <typename Key>
    const_iterator find(const Key& key) const {

        return find(key);
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
            if (!key_is_less(key, current_node.base()->value, value_compare())) {
                // current_node > key = false --> Right
                if (!current_node.base()->right) {
                    return current_node.base()->right;
                }
                ptr = &current_node.base()->right;
                if (parent.base()->right)
                    parent = parent.base()->right;
                current_node = current_node.base()->right;

            } else if (key_is_less(key, current_node.base()->value, value_compare())) {
                // Key > current_node = false --> Left
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

    template <typename Key>
    node_pointer& find_insert_pos(iterator& root, iterator& hint, const Key& key) {

        iterator hint_parent(hint.base()->parent);

        if (key_is_less(key, hint_parent.base()->value, value_compare())) {
            // key < hint_parent = true --> Check Hint
            if (node_is_left_child(hint.base())) {
                // key fits at hint
                if (key_is_less(key, hint.base()->value, value_compare())) {
                    // key fits --> insert left
                    if (!hint.base()->left) {
                        root = hint;
                        return hint.base()->left;
                    } else
                        // Node has child --> start from root
                        return find_insert_pos(root, key);
                } else {
                    // key fits --> insert right
                    if (!hint.base()->right) {
                        root = hint;
                        return hint.base()->right;
                    } else
                        // Node has child --> start from root
                        return find_insert_pos(root, key);
                }
            } else
                // Key doesn't fit -> start from root
                return find_insert_pos(root, key);

        } else if (!key_is_less(key, hint_parent.base()->value, value_compare())) {
            if (node_is_left_child(hint.base())) {
                // key doesn't fit -> start from root
                return find_insert_pos(root, key);
            } else if (key_is_less(key, hint.base()->value, value_compare())) {
                // key fits at hint -> insert left
                if (!hint.base()->left) {
                    root = hint;
                    return hint.base()->left;
                } else
                    // Node has child --> start from root
                    return find_insert_pos(root, key);
            } else {
                // key fits --> insert right
                if (!hint.base()->right) {
                    root = hint;
                    return hint.base()->right;
                } else
                    // Node has child --> start from root
                    return find_insert_pos(root, key);
            }

        } else {
            return find_insert_pos(root, key);
        }
    }

    // Returns a pointer to the root node (left child of end_ node)
    node_pointer& get_root() const { return end_->left; }
    node_pointer* get_root_ptr() const { return &end_->left; }

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

    // Delete the node from the tree
    void delete_node(node_pointer node) {

        if (node_is_left_child(node))
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
        value_alloc_.destroy(&node->value);
        node_alloc_.deallocate(node, 1);
        size_--;
    }

    void clear_tree(node_pointer node) {

        if (node) {
            clear_tree(node->left);
            clear_tree(node->right);
            value_alloc_.destroy(&node->value);
            node_alloc_.deallocate(node, 1);
        }
    }

    // Init an empty node with no value
    void init_tree(const value_type& val) {

        end_->left = new_node(val);
        begin_ = end_->left;
        begin_->parent = end_;
        right_end_ = begin_;
    }

    // Case 1: Root is always Black
    void insert_case_1() {

        if (get_root()->is_black == false) {
            get_root()->is_black = true;
        }
    }

    // Case 2: new_node's uncle is RED ---> Recolor
    bool insert_case_2(node_pointer& new_node, node_pointer uncle) {

        // If Red Uncle
        if (uncle && !uncle->is_black) {

            // Recolor Red uncle to Black
            uncle->is_black = true;

            // Red Parent --> Recolor Black
            new_node->parent->is_black = true;

            // Black G-P && Not Root --> Recolor RED
            get_grandparent(new_node)->is_black = false;

            new_node = new_node->parent->parent;

            return true;
        }
        return false;
    }

    // CASE 3 -> If new_node parent is a right child, get left uncle and call
    // CASE 2 -> if uncle is RED, recolor Uncle, Parent and Grand-Parent.
    // IF NOT CASE 2 -> Verify that new_node is a left child.
    // If true, new_node becomes his parent and perform a right rotate.
    // THEN, recolor new_node->parent and Grand-Parent and perform left_rotate.
    // Repeat until either new_node is root OR new_node parent color isn't black.
    void insert_case_3(node_pointer& new_node) {

        if (!node_is_left_child(new_node->parent)) {

            // new_node->parent->parent->left
            node_pointer uncle = get_uncle_left(new_node);
            if (!insert_case_2(new_node, uncle)) {

                if (node_is_left_child(new_node)) {
                    new_node = new_node->parent;
                    right_rotate(new_node);
                }

                new_node->parent->is_black = true;
                get_grandparent(new_node)->is_black = false;
                left_rotate(new_node->parent->parent);
            }
        } else {

            // uncle = new_node->parent->parent->right
            node_pointer uncle = get_uncle_right(new_node);
            if (!insert_case_2(new_node, uncle)) {

                if (!node_is_left_child(new_node)) {
                    new_node = new_node->parent;
                    left_rotate(new_node);
                }

                new_node->parent->is_black = true;
                get_grandparent(new_node)->is_black = false;
                right_rotate(new_node->parent->parent);
            }
        }
    }

    // Fixes and Rebalance the tree based on several Cases.
    // Case 1: Root must always be black.
    // Case 2: new_node's uncle is RED (inside case 3)
    // Case 3: Parent is either Left or Right Child
    void insert_fix(node_pointer new_node) {

        node_pointer root = get_root();

        while (new_node != root && new_node->parent->is_black == false) {
            // CASE 3 --> Checks if parent node is either a Left or Right Child
            insert_case_3(new_node);
            insert_case_1();
        }
    }

    void delete_fix(node_pointer current_node) {

        iterator root(get_root());

        while (true) {

            if (current_node == root.base())
                break;
            else if (!current_node->is_black)
                break;

            // CASE 1 -> If Sibling is RED
            else if (get_sibling(current_node) && !get_sibling(current_node)->is_black) {

                current_node->parent->is_black = false;

                get_sibling(current_node)->is_black = true;

                if (node_is_left_child(get_sibling(current_node))) {
                    right_rotate(current_node->parent);

                } else {
                    left_rotate(current_node->parent);
                }

                // CASE 2 -> if Nephew is RED (TERMINAL CASE)
            } else if (get_nephew(current_node) && !get_nephew(current_node)->is_black) {

                get_sibling(current_node)->is_black = current_node->parent->is_black;

                current_node->parent->is_black = true;

                get_nephew(current_node)->is_black = true;

                if (node_is_left_child(get_sibling(current_node))) {
                    right_rotate(current_node->parent);
                } else {
                    left_rotate(current_node->parent);
                }
                current_node = current_node->parent;
                break;

                // CASE 3 -> if Niece is RED
            } else if (get_niece(current_node) && !get_niece(current_node)->is_black) {

                get_niece(current_node)->is_black = true;

                get_sibling(current_node)->is_black = false;

                if (node_is_left_child(get_niece(current_node))) {
                    right_rotate(get_niece(current_node)->parent);

                } else {
                    left_rotate(get_niece(current_node)->parent);
                }

                // CASE 4 -> Current_node, Sibling, Niece and Nephew are all Black
            } else {
                if (get_sibling(current_node))
                    get_sibling(current_node)->is_black = false;
                current_node = current_node->parent;
            }
        }
        current_node->is_black = true;
    }

    void left_rotate(node_pointer current_node) {

        node_pointer tmp = current_node->right;

        current_node->right = tmp->left;
        if (tmp->left)
            tmp->left->parent = current_node;

        tmp->parent = current_node->parent;
        if (current_node->parent == end_)
            end_->left = tmp;
        else if (current_node == current_node->parent->left)
            current_node->parent->left = tmp;
        else
            current_node->parent->right = tmp;

        tmp->left = current_node;
        current_node->parent = tmp;
    }

    void right_rotate(node_pointer current_node) {

        node_pointer tmp = current_node->left;

        current_node->left = tmp->right;
        if (tmp->right)
            tmp->right->parent = current_node;

        tmp->parent = current_node->parent;
        if (current_node->parent == end_)
            end_->left = tmp;
        else if (current_node == current_node->parent->right)
            current_node->parent->right = tmp;
        else
            current_node->parent->left = tmp;

        tmp->right = current_node;
        current_node->parent = tmp;
    }

    void BST_remove(node_pointer toBeDeleted) {
        if (!empty()) {

            // Case 1 -> Node is a leaf
            if (node_is_leaf(toBeDeleted)) {

                if (toBeDeleted->is_black == false) {
                    if (node_is_left_child(toBeDeleted))
                        toBeDeleted->parent->left = NULL;
                    else
                        toBeDeleted->parent->right = NULL;
                } else
                    return;

                // Case 2 -> Node has only one child
            } else if (node_only_child(toBeDeleted)) {

                node_pointer child = (toBeDeleted->left) ? toBeDeleted->left : toBeDeleted->right;

                // Replace toBeDeleted by it's child
                if (node_is_left_child(toBeDeleted)) {
                    toBeDeleted->parent->left = child;
                } else {
                    toBeDeleted->parent->right = child;
                }

                child->parent = toBeDeleted->parent;
                toBeDeleted->parent = child;
                // child->is_black = toBeDeleted->is_black;
                (toBeDeleted->left) ? child->left = toBeDeleted : child->right = toBeDeleted;
                (toBeDeleted->left) ? toBeDeleted->left = NULL : toBeDeleted->right = NULL;

                // Case 3 -> toBeDeleted Node has two child
            } else {

                bool color = toBeDeleted->is_black;

                // Find the largest value in the left Subtree of the toBeDeleted node
                node_pointer successor = find_successor(toBeDeleted->left);

                swap_nodes(toBeDeleted, successor);

                successor->is_black = color;
            }
        }
    }

    // clang-format off
  private:
    node_allocator      node_alloc_;    // used to Allocate nodes
    allocator_type      value_alloc_;   // used to Allocate values in nodes
    node_pointer        end_;           // Node above root that marks the end of the tree
    node_pointer        begin_;         // Left Most node
    node_pointer        right_end_;     // Right Most node
    value_compare       comp_;
    size_type           size_;
    // clang-format on
}; // class RBTree

} // namespace ft
