/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:39:17 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/13 09:47:43 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include "RBtree.hpp"
#include "pair.hpp"
#include "utilities.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>

namespace ft {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class set {

    // clang-format off

  //* ============== Member Typedefs ==============
  private:
    typedef RBTree<Key, Compare, Allocator> base;
 
  public:
    typedef Key                                       key_type; 
    typedef Key                                       value_type;
    typedef Compare                                   key_compare; // std::less<key_type>
    typedef Compare                                   value_compare; // std::less<key_value>
    typedef size_t                                    size_type;
    typedef Allocator                                 allocator_type;
    typedef ptrdiff_t                                 difference_type;
    typedef value_type&                               reference;
    typedef const value_type&                         const_reference;
    typedef typename Allocator::pointer               pointer;
    typedef typename Allocator::const_pointer         const_pointer;
    typedef typename base::iterator                   iterator;
    typedef typename base::const_iterator             const_iterator;
    typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;
    typedef ft::reverse_iterator<iterator>            reverse_iterator;
    // clang-format on

    //* ============== CTORS / DTOR ==============

  public:
    set() : rbtree(value_compare()) {}

    explicit set(const key_compare& comp,
                 const allocator_type& alloc = allocator_type())
        : rbtree(comp, alloc) {}

    template <typename InputIter>
    set(InputIter first, InputIter last, const key_compare& comp = key_compare(),
        const Allocator& alloc = allocator_type())
        : rbtree(comp, alloc) {

        insert(first, last);
    }

    set(const set& src) : rbtree(src.rbtree) {}

    set& operator=(const set& rhs) {
        rbtree = rhs.rbtree;

        return *this;
    }

    ~set() {}

    /**
     **  ==================================================
     **  |               MEMBER FUNCTIONS                 |
     **  ==================================================
     */

  public:
    // Returns a copy of the allocator associated with the Set
    allocator_type get_allocator() { return rbtree.get_allocator(); }

    //* ============== Iterators ==============
    iterator begin() { return rbtree.begin(); }
    const_iterator begin() const { return rbtree.begin(); }
    iterator end() { return rbtree.end(); }
    const_iterator end() const { return rbtree.end(); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    //* ============== Capacity ==============

    bool empty() const { return rbtree.empty(); }

    size_type size() const { return rbtree.size(); }

    size_type max_size() const { return rbtree.max_size(); }

    //* ============== Modifiers ==============

    // Inserts a single value in the set.
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

    // Removes the element with the key equivalent to key
    size_type erase(const Key& key) { return rbtree.erase(key); }

    // Removes all elements between [first] and [last].
    // Excluding the element pointed by [last].
    void erase(iterator first, iterator last) { return rbtree.erase(first, last); }

    // Removes all the elements from the container.
    // Size will be reduced to 0.
    void clear() { rbtree.clear(); }

    // Swap current container for src container.
    void swap(set& src) { rbtree.swap(src.rbtree); }

    void printTree() { rbtree.printTree(); }

    //* ============== Lookup ==============

    // Returns the number of element matching key.
    // Either 1 or 0 since no duplicates are allowed.
    size_type count(const Key& key) const { return rbtree.count(key); }

    // Returns an iterator on the matching key.
    // If no element is found, returns an iterator on end().
    iterator find(const Key& key) { return rbtree.find(key); }

    // Returns a const_iterator on the matching key.
    // If no element is found, returns an iterator on end().
    const_iterator find(const Key& key) const { return rbtree.find(key); }

    // Returns a range containing all elements matching with the given key.
    pair<iterator, iterator> equal_range(const Key& key) { return rbtree.equal_range(key); }

    // Returns a range containing all elements matching with the given key.
    pair<const_iterator, const_iterator> equal_range(const Key& key) const {
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

    //* ============== Observers ==============
    key_compare key_comp() const { return rbtree.value_comp(); }

    value_compare value_comp() const { return rbtree.value_comp(); }

    /**
     **  ==================================================
     **  |           PRIVATE MEMBER VARIABLES             |
     **  ==================================================
     */

  private:
    base rbtree;

}; // class Set

/**
**  ==================================================
**  |              NON-MEMBER FUNCTIONS              |
**  ==================================================
*/

template <typename Key, typename Compare, typename Alloc>
void swap(ft::set<Key, Compare, Alloc>& x, ft::set<Key, Compare, Alloc>& y) {

    x.swap(y);
}

template <typename Key, typename Compare, typename Alloc>
bool operator==(const ft::set<Key, Compare, Alloc>& left,
                const ft::set<Key, Compare, Alloc>& right) {

    return (left.size() == right.size()) && std::equal(left.begin(), left.end(), right.begin());
}

template <typename Key, typename Compare, typename Alloc>
bool operator!=(const ft::set<Key, Compare, Alloc>& left,
                const ft::set<Key, Compare, Alloc>& right) {

    return !(left == right);
}

template <typename Key, typename Compare, typename Alloc>
bool operator<(const ft::set<Key, Compare, Alloc>& left,
               const ft::set<Key, Compare, Alloc>& right) {

    return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

template <typename Key, typename Compare, typename Alloc>
bool operator>(const ft::set<Key, Compare, Alloc>& left,
               const ft::set<Key, Compare, Alloc>& right) {

    return right < left;
}

template <typename Key, typename Compare, typename Alloc>
bool operator<=(const ft::set<Key, Compare, Alloc>& left,
                const ft::set<Key, Compare, Alloc>& right) {

    return !(right < left);
}

template <typename Key, typename Compare, typename Alloc>
bool operator>=(const ft::set<Key, Compare, Alloc>& left,
                const ft::set<Key, Compare, Alloc>& right) {

    return !(left < right);
}

} // namespace ft
