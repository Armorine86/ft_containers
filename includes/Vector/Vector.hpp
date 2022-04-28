/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/28 15:04:00 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <iostream>
//#include <vector>

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector {
    // clang-format off
  public:
    //* ========== Member Types ==========
    typedef T                                           value_type; // Common types (int, long, etc)
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef Allocator                                   allocator_type;
    typedef size_t                                      size_type;
    typedef ptrdiff_t                                   difference_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef ft::normal_iterator<pointer, vector>        iterator; //* normal_iterator<T, Container>
    typedef ft::normal_iterator<const_pointer, vector>  const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
    // clang-format on

    /**
     **  ==================================================
     **  |               MEMBER FUNCTIONS                 |
     **  ==================================================
     */

    //* default constructor
    vector() : alloc_(), start_(), end_(), capacity_() {}

    //* Default Constructor: empty container with no elements
    explicit vector(const allocator_type& alloc) : alloc_(alloc), start_(), end_(), capacity_() {}

    /**
     ** Fill Constructor:
     *  Container with n elements. Each element is a copy of val
     *
     *  @param n Number of Elements
     *  @param val Type of Element
     *  @param alloc Allocator_type
     */
    explicit vector(size_type n, const value_type& val = value_type(),
                    const Allocator& alloc = allocator_type())
        : alloc_(alloc) {

        if (n == 0)
            return;

        check_size(n);

        start_ = alloc_.allocate(n);
        end_ = start_;
        capacity_ = start_ + n;

        fill_construct(val, n);
    }

    /**
    ** Range Constructor:
    * Container with as many elements as the range [first, last]
    * with each elements constructed from its corresponding element in that range
    * in the same order
    *
    * @tparam InputIterator
    * @param first start of range
    * @param last end of range
    */
    template <typename InputIterator>
    vector(InputIterator first,
           typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
           const allocator_type& alloc = allocator_type())
        : alloc_(alloc), start_(), end_(), capacity_() {

        typedef typename iterator_traits<vector::iterator>::iterator_category category;
        vec_init(first, last, category());
    }

    //* Copy Constructor
    vector(const vector& src) : alloc_(src.alloc_), start_(), end_(), capacity_() {

        typedef typename iterator_traits<vector::iterator>::iterator_category category;
        vec_init(src.first, src.last, category());
    }

    //* Operator= Constructor
    vector& operator=(const vector& rhs) {
        if (this == &rhs)
            return *this;
        assign(rhs.begin(), rhs.end());
    }

    //* Destructor
    ~vector() { deallocate_vec(); };

    allocator_type get_allocator() const { return allocator_type(); }
    /*
     *  ==================================================
     *  |           PUBLIC MEMBER FUNCTIONS              |
     *  ==================================================
     */

    //* =============== ELEMENT ACCESS FUNCTIONS ===============

    /**
     * @return Returns a reference at specified location pos
     */
    reference at(size_type pos) {
        if (pos > size())
            throw std::out_of_range("Accessed Index is Out Of Range");

        return (*this)[pos];
    }

    /**
     * @return Returns a const reference at specified location pos
     */
    const_reference at(size_type pos) const {
        if (pos > size())
            throw std::out_of_range("Accessed Index is Out Of Range");

        return (*this)[pos];
    }

    /**
     * @return Returns a reference to the the element at index pos
     */ 
    reference operator[](size_type pos) { return *(start_ + pos); }

    /**
     * @return Returns a const reference to the the element at index pos
     */ 
    const_reference operator[](size_type pos) const { return *(start_ + pos); }

    /**
     * @return Returns a reference to the first element of the vector
     */ 
    reference front() { return *start_; }

    /**
     * @return Returns a const reference to the first element of the vector
     */ 
    const_reference front() const { return *start_; }

    /**
     * @return Returns a reference to the last element of the vector
     */
    reference back() { return *(end_ - 1); }

    /**
     * @return Returns a const reference to the last element of the vector
     */
    const_reference back() const { return *(end_ - 1); }

    /**
     * @return Returns a pointer to the underling array serving as element storage
     */
    value_type* data() { return start_; }

    /**
     * @return Returns a const pointer to the underling array serving as element storage
     */
    const value_type* data() const { return start_; }

    //* =============== ITERATORS FUNCTIONS ===============

    iterator begin() { return iterator(start_); }
    const_iterator begin() const { return const_iterator(start_); }
    reverse_iterator rbegin() { return reverse_iterator(end_ - 1); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end_ - 1); }

    iterator end() { return iterator(end_); }
    const_iterator end() const { return iterator(end_); }
    reverse_iterator rend() { return reverse_iterator(start_); }
    const_reverse_iterator rend() const { return const_reverse_iterator(start_); }

    //* =============== CAPACITY FUNCTIONS ===============

    /**
     * @return returns TRUE if the container is empty
     */
    bool empty() { return size(); }

    /**
     *  @param diffmax the maximum elements of type T
     *  @param allocmax the maximum memory allocation
     *  @return The Vector Maximum Size
     */
    size_type max_size() {
        const size_t diffmax = std::numeric_limits<difference_type>::max() / sizeof(value_type);
        const size_t allocmax = alloc_.max_size();

        return std::min(diffmax, allocmax);
    }

    /**
     * @return The number of elements in the Vector
     */
    size_type size() { return static_cast<size_type>(end_ - start_); }

    /**
     * Increase the capacity to a value that's greater or equal to new_cap.
     * If new_cap is smaller than current capacity the function does nothing.
     */
    void reserve(size_type new_cap) {

        if (new_cap <= capacity())
            return;
        if (new_cap > capacity())
            check_size(new_cap); // if Realloc needed, check if smaller than Max Size

        pointer new_start = alloc_.allocate(new_cap);
        pointer new_end = construct_vec(new_start, start_, end_);

        deallocate_vec();

        start_ = new_start;
        end_ = new_end;
        capacity_ = start_ + new_cap;
    }

    /**
     * @return Returns the number of elements that the container has currently allocated space for.
     */
    size_type capacity() const { return static_cast<size_type>(capacity_ - start_); }

    //* =============== MODIFIERS FUNCTIONS ===============

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) {

        typedef typename iterator_traits<InputIterator>::iterator_category category;
        clear();
        vec_init(first, last, category());
    }

    void assign(size_type n, const value_type& val) {

        clear();
        fill_construct(val, n);
    }
    /**
     * Erase element at position pos.
     */
    iterator erase(iterator pos) {

        if (pos == end() - 1) {
            --end_;
            alloc_.destroy(end_);
            return end();
        }

        return erase(pos, pos + 1);
    }

    /**
     * Erases all elements in range [first, last].
     * Shifts all elements to the left.
     * @return Returns a pointer on the element first + 1.
     * If last == end(), returns an Iterator to end_
     */
    iterator erase(iterator first, iterator last) {

        if (last == end())
            return end();

        difference_type diff = std::distance(first, last);
        pointer old_end = end_;

        if (diff > 0) {
            shift_left(first, last);
            end_ -= diff;
            range_destroy(end_, old_end);
        }

        return last - diff;
    }

    /**
     * Erases all elements from the container.
     */
    void clear() { erase(iterator(start_), iterator(end_)); }

    /**
     * Adds a single element at the end of the vector.
     * If Capacity is reached, reallocate size() * 2,
     * If Vector is empty, allocate 1
     */
    void push_back(const value_type& value) {

        if (end_ == capacity_) {
            size_type new_cap = (empty()) ? size() * 2 : 1;
            reserve(new_cap);
        }
        alloc_.construct(end_, value);
        ++end_;
    }

    /**
     * Insert a single element before pos.
     * Reallocates the vector if size() surpasses capacity()
     * @return An Iterator that points to the first of the newly inserted elements
     */
    iterator insert(iterator pos, const T& val) {
        
        size_type n = 1; //Single Element
        if (end_ == capacity_) {
            size_type new_cap = (empty()) ? size() * 2 : 1;
            reserve(new_cap);
        }
        
        end_ += n;
        
        shift_right(pos, n);

        alloc_.destroy(pos.base());
        alloc_.construct(pos.base(), val);

        return pos;
    }

    // void insert(iterator pos, size_type n, const T& value) {

    // }

    // template <typename InputIterator>
    // void insert(iterator pos, InputIterator first, InputIterator last) {

    // }

    /*
     *  ==================================================
     *  |          PRIVATE MEMBERS FUNCTIONS             |
     *  ==================================================
     */

    /**
     * @return THROWS if max_size() is equal or bigger than
     * maximum allowed vector size
     */
    void check_size(size_type n) {
        if (n >= max_size())
            throw std::length_error("Vector Max Size Exceeded");
    }

    /**
     * Shifts all elements at n position to the right as long as it is inside capacity.
     */
    void shift_right(iterator& pos, size_type n) {
        
        for (iterator it = end() - 1; it >= pos; --it) {
            *(it + n) = *it;
            //alloc_.destroy(it.base());
        }
    }
    /**
     * Shifts all elements to the left inside the vector
     * Increments first iterator
     */
    void shift_left(iterator& first, iterator& last) {

        for (iterator it = last; it != end(); ++it) {
            alloc_.destroy(first.base());
            *first = *it;
            ++first;
        }
    }

    /**
     * Fills Vector with N elements of type val
     * @param val Type of Element
     * @param n Number of elements
     */
    void fill_construct(const value_type& val, size_type n) {

        for (size_type i = 0; i != n; ++i) {
            alloc_.construct(end_, val);
            end_++;
        }
    }
    template <typename InputIterator>
    void vec_init(InputIterator first, InputIterator last, std::input_iterator_tag) {

        for (; first != last; ++first)
            push_back(*first);
    }

    template <typename Iter>
    pointer construct_vec(pointer new_start, Iter start, Iter end) {

        for (; start != end; ++new_start, (void)++start)
            alloc_.construct(new_start, *start);

        return new_start;
    }

    /**
     * Deallocate elements beginning at start pointer up to capacity()
     */
    void deallocate_vec() {

        clear();
        alloc_.deallocate(start_, capacity());
    }

    void print_vec() {

        for (pointer first = start_; first != end_; ++first)
            std::cout << " " << *first;
    }

    /**
     * Calls Allocator::destroy() on each elements from first to last
     */
    void range_destroy(pointer first, pointer last) {

        for (; first != last; ++first)
            alloc_.destroy(first);
    }

    /*
     *  ==================================================
     *  |               PRIVATE MEMBERS                  |
     *  ==================================================
     */

  private:
    allocator_type alloc_; //* the Allocator type which takes the type to allocate
    pointer start_;        //* start pointer to first element
    pointer end_;          //* end pointer (one after last element)
    pointer capacity_;     //* A pointer to the maximum allowed elements
};                         // class vector


} // namespace ft
