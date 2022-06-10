/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:11:20 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/10 13:54:27 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RBTree/RBtree.hpp"
#include "Iterator/Iterator.hpp"
#include "utilities.hpp"

#include <stdexcept>

namespace ft {

template <typename Key, typename T, typename Compare>
class map_value_type_compare : public std::binary_function<Key, Key, bool> {

  public:
    // Constructors

    map_value_type_compare() : comp() {}
    map_value_type_compare(const Compare& cmp) : comp(cmp) {}

  public:
    // Member Functions

    const Compare& key_comp() const { return comp; }

    bool operator()(const T& x, const T& y) const { return key_comp()(x.first, y.first); }

    bool operator()(const Key& x, const T& y) const { return key_comp()(x, y.first); }

    bool operator()(const T& x, const Key& y) const { return key_comp()(x.first, y); }

    void swap(map_value_type_compare& src) { std::swap(comp, src.comp_); }

  protected:
    Compare comp;

}; // class map_value_type_compare

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

    // clang-format off
  public:
    //* ============== Member Typedefs ==============
    typedef Key 									                key_type; // ft::pair<[KEY_TYPE], T>  ->first
    typedef T 									            	    mapped_type; // ft_pair<key, [VALUE]> ->second
    typedef Compare 								              key_compare;
	  typedef Allocator								              allocator_type;
    typedef size_t 									              size_type;
    typedef std::ptrdiff_t 							          difference_type;
    typedef ft::pair<const Key, T>                value_type;
    typedef value_type& 							            reference;
    typedef const value_type& 						        const_reference;
    typedef typename Allocator::pointer 			    pointer;
    typedef typename Allocator::const_pointer 		const_pointer;

  private:
    typedef map_value_type_compare<key_type, value_type, key_compare> value_type_compare;
    typedef RBTree<value_type, value_type_compare, allocator_type>    base;

  public:
    typedef typename base::iterator 			        iterator;
    typedef typename base::const_iterator         const_iterator;
    typedef ft::reverse_iterator<iterator>        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
    // clang-format on

    //* ============== NESTED CLASS ==============

  public:
    //  Provides a function object that can compare the elements of a map
    //  by comparing the values of their keys to determine their relative order in the map.
    class value_compare : public std::binary_function<value_type, value_type, bool> {

      public:
        friend class map;

      protected:
        key_compare comp_;
        value_compare(const key_compare& comp) : comp_(comp) {}

      public:
        bool operator()(const value_type& x, const value_type& y) const {
            return comp_(x.first, y.first);
        }

    }; // class value_compare

    /**
     **  ==================================================
     **  |               MEMBER FUNCTIONS                 |
     **  ==================================================
     */

    //* ============== CTORS / DTOR ==============

    // Default Constructor
    map() : rbtree(value_type_compare()) {}

    explicit map(const key_compare& comp, const Allocator& alloc_ = Allocator())
        : rbtree(value_type_compare(comp), alloc_) {}

    template <typename InputIter>
    map(InputIter first, InputIter last, const Compare& comp = Compare(),
        const Allocator& alloc_ = Allocator())
        : rbtree(value_type_compare(comp), alloc_) {
        insert(first, last);
    }

    map(const map& src) : rbtree(src.rbtree) {}

    map& operator=(const map& src) {
        rbtree = src.rbtree;
        return *this;
    }

    ~map() {}

    //* =============== ITERATORS FUNCTIONS ===============

    iterator begin() { return rbtree.begin(); }
    const_iterator begin() const { return rbtree.begin(); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    iterator end() { return rbtree.end(); }
    const_iterator end() const { return rbtree.end(); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    //* =============== ELEMENT ACCESS FUNCTIONS ===============

    T& at(const Key& key) {

        iterator it = find(key);

        if (it == end())
            throw std::out_of_range("Key does not exist");

        return it->second;
    }

    const T& at(const Key& key) const {

        const_iterator it = find(key);

        if (it == end())
            throw std::out_of_range("Key does not exist");

        return it->second;
    }

    T& operator[](const Key& key) {

        return insert(ft::make_pair(key, mapped_type())).first->second;
    }

    // Returns a copy of the allocator associated with the Set
    allocator_type get_allocator() const { return rbtree.get_allocator(); }

    //* =============== CAPACITY FUNCTIONS ===============

    bool empty() { return rbtree.empty(); }

    size_type size() const { return rbtree.size(); }

    size_type max_size() const { return rbtree.max_size(); }

    //* =============== MODIFIERS FUNCTIONS ===============

    // Removes all the elements from the container.
    // Size will be reduced to 0.
    void clear() { rbtree.clear(); }

    // Inserts a single value in the map.
    ft::pair<iterator, bool> insert(const value_type& val) { return rbtree.insert(val); }

    // Inserts an element [in front] of the marked position.
    iterator insert(iterator pos, const value_type& val) { return rbtree.insert(pos, val); }

    // Inserts a range of element into the set starting with [first] up to [last].
    // Excluding the element pointed by [last].
    template <typename InputIter>
    void insert(InputIter first, InputIter last) {
        rbtree.insert(first, last);
    }

    // Removes a single element marked by pos
    void erase(iterator pos) { rbtree.erase(pos); }

    // Removes all elements between [first] and [last].
    // Excluding the element pointed by [last].
    void erase(iterator first, iterator last) { rbtree.erase(first, last); }

    // Removes the element with the key equivalent to key
    size_type erase(const Key& key) { return rbtree.erase(key); }

    // Swap current container for src container.
    void swap(map& src) { rbtree.swap(src.rbtree); }

    //* =============== LOOKUP FUNCTIONS ===============

    // Returns the number of element matching key.
    // Either 1 or 0 since no duplicates are allowed.
    size_type count(const Key& key) const { return rbtree.count(key); }

    // Returns an iterator on the matching key.
    // If no element is found, returns an iterator on end().
    iterator find(const key_type& key) { return rbtree.find(key); }

    // Returns a const_iterator on the matching key.
    // If no element is found, returns an iterator on end().
    const_iterator find(const key_type& key) const { return rbtree.find(key); }

    // Returns a range containing all elements matching with the given key.
    ft::pair<iterator, iterator> equal_range(const Key& key) { return rbtree.equal_range(key); }

    // Returns a range containing all elements matching with the given key.
    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
        return rbtree.equal_range(key);
    }

    // Returns an iterator on the first element that is not less (Greater or equal) than given key.
    iterator lower_bound(const Key& key) { return rbtree.lower_bound(key); }

    // Returns an iterator on the first element that is not less (Greater or equal) than given key.
    const_iterator lower_bound(const Key& key) const { return rbtree.lower_bound(key); }

    // Returns an iterator on the first element that is greater than given key.
    iterator upper_bound(const Key& key) { return rbtree.upper_bound(key); }

    // Returns an iterator on the first element that is greater than given key.
    const_iterator upper_bound(const Key& key) const { return rbtree.upper_bound(key); }

    //* =============== OBSERVER FUNCTIONS ===============

    key_compare key_comp() const { return key_compare(); }

    map::value_compare value_comp() const {
        return value_compare(key_comp());
    }

    //* =============== UTIL FUNCTIONS ===============

    // Prints the tree layout
    void printTree() { rbtree.printTree(); }

    /**
     **  ==================================================
     **  |           PRIVATE MEMBER VARIABLES             |
     **  ==================================================
     */

  private:
    base rbtree;

}; // class map

template <typename Key, typename T, typename Compare, typename Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& x, ft::map<Key, T, Compare, Alloc>& y) {
    x.swap(y);
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator==(const ft::map<Key, T, Compare, Alloc>& left,
                       const ft::map<Key, T, Compare, Alloc>& right) {
    return left.size() == right.size() && std::equal(left.begin(), left.end(), right.begin());
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator!=(const ft::map<Key, T, Compare, Alloc>& left,
                       const ft::map<Key, T, Compare, Alloc>& right) {
    return !(left == right);
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator<(const ft::map<Key, T, Compare, Alloc>& left,
                      const ft::map<Key, T, Compare, Alloc>& right) {
    return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator<=(const ft::map<Key, T, Compare, Alloc>& left,
                       const ft::map<Key, T, Compare, Alloc>& right) {
    return !(right < left);
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator>(const ft::map<Key, T, Compare, Alloc>& left,
                      const ft::map<Key, T, Compare, Alloc>& right) {

    return right < left;
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator>=(const ft::map<Key, T, Compare, Alloc>& left,
                       const ft::map<Key, T, Compare, Alloc>& right) {
    return !(left < right);
}
} // namespace ft
