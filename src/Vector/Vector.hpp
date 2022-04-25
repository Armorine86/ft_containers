/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/25 12:29:20 by mmondell         ###   ########.fr       */
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
    vector() : alloc_(), start(), end(), capacity() {}

    //* Default Constructor: empty container with no elements
    explicit vector(const allocator_type& alloc) : alloc_(alloc), start(), end(), capacity() {}

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

        start = alloc_.allocate(n);
        end = start;
        capacity = start + n;

        for (size_type i = 0; i != n; ++i) {
            alloc_.construct(end, val);
            end++;
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
        : alloc_(alloc), start(), end(), capacity() {

        typedef typename iterator_traits<InputIterator>::iterator_category category;
        range_construct(first, last, category());
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
    const_reference at(size_type pos) const {
        if (pos > size())
            throw std::out_of_range("Accessed Index is Out Of Range");

        return (*this)[pos];
    }

    reference operator[](size_type pos) { return *(start + pos); }
    const_reference operator[](size_type pos) const { return *(start + pos); }
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
    size_type size() { return static_cast<size_type>(end - start); }

    /*
     *  ==================================================
     *  |          PRIVATE MEMBERS FUNCTIONS             |
     *  ==================================================
     */

    template <typename InputIterator>
    void range_construct(InputIterator first, InputIterator last, std::input_iterator_tag) {

        for (; first != last; ++first)
            push_back(*first);
    }

    /*
     *  ==================================================
     *  |               PRIVATE MEMBERS                  |
     *  ==================================================
     */

  private:
    allocator_type alloc_; //* the Allocator type which takes the type to allocate
    pointer start;         //* start pointer
    pointer end;           //* end pointer (one after last element)
    pointer capacity;      //* the total amount of allocated memory
};

} // namespace ft
