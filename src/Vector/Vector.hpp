/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/25 21:43:32 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <vector>

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
    // typedef typename allocator_type::reference          reference;
    // typedef typename allocator_type::const_reference    const_reference;
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

        for (size_type i = 0; i != n; ++i) {
            alloc_.construct(end_, val);
            end_++;
        }
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

        typedef typename iterator_traits<InputIterator>::iterator_category category;
        vec_init(first, last, category());
    }

    //* Copy Constructor
    // vector(const vector& src) {} // TODO

    //* Operator= Constructor
    // vector& operator=(const vector& rhs) {} // TODO

    //* Destructor
    //~vector(){};
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

    reference operator[](size_type pos) { return *(start_ + pos); }
    const_reference operator[](size_type pos) const { return *(start_ + pos); }

    reference front() { return *start_; }
    const_reference front() const { return *start_; }

    reference back() { return *(end_ - 1); }
    const_reference back() const { return *(end_ - 1); }

    //* =============== ITERATORS FUNCTIONS ===============

    iterator begin() { return iterator(start_); }
    const_iterator begin() const { return const_iterator(start_); }
    reverse_iterator rbegin() { return reverse_iterator(end_ - 1); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end_ - 1); }

    iterator end() { return iterator(end_); }
    const_iterator end() const { return iterator(end_); }
    reverse_iterator rend() { return reverse_iterator(start_ - 1); }
    const_reverse_iterator rend() const { return const_reverse_iterator(start_ - 1); }

    //* =============== CAPACITY FUNCTIONS ===============

    /**
     * @return returns TRUE if the container is empty
     */
    bool empty() { return size(); }

    /**
     * @return THROWS if max_size() is equal or bigger than
     * maximum allowed vector size
     */
    void check_size(size_type n) {
        if (n >= max_size())
            throw std::length_error("Vector Max Size Exceeded");
    }

    /**
     *  @param diffmax the maximum elements of type T
     *  @param allocmax the maximum memory allocation
     *  @return The Vector Maximum Size
     */
    size_type max_size() {
        const size_t diffmax = std::numeric_limits<difference_type>::max() / sizeof(T);
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

        if (new_cap < capacity())
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

    /**
     * Erases elements at position pos
     */
    //*iterator erase(iterator pos) {}

    /**
     * Erases elements in range [first, last]
     */
    //*iterator erase(iterator first, iterator last) {}

    /**
     * Erases all elements from the container.
     */
    void clear() { erase(start_, end_); }

    /**
     * Adds an element at the end of the vector.
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

    // iterator insert(iterator position, const T& value) {

    // }

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

    void deallocate_vec() {

        // clear();
        alloc_.deallocate(start_, capacity());
    }

    /*
     *  ==================================================
     *  |               PRIVATE MEMBERS                  |
     *  ==================================================
     */

  private:
    allocator_type alloc_; //* the Allocator type which takes the type to allocate
    pointer start_;        //* start pointer
    pointer end_;          //* end pointer (one after last element)
    pointer capacity_;     //* A pointer to the maximum allowed elements
};                         // class vector

} // namespace ft
