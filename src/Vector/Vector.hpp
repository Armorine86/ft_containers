/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/04/22 16:49:45 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include <cstddef>
#include <memory>
#include <limits>

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector {
    // clang-format off
  public:
    //* ========== Member Types ==========
    typedef T                                           value_type; //* Common types (int, long, etc)
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

    //* ========== CONSTRUCTORS ==========
    //! C++98 ? https://www.cplusplus.com/reference/vector/vector/vector/
    // default constructor
    // vector() : alloc_(), start(), end(), capacity() {}

    // Default Constructor: empty container with no elements
    explicit vector(const allocator_type& alloc = allocator_type())
        : alloc_(alloc), start(), end(), capacity() {}

    // fill constructor: Container with n elements. Each elem is a cpy of val
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type())
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

    // range constructor: Container with as many elements as the range [first, last]
    // with each elements constructed from its corresponding element in that range
    // in the same order
    // template <typename InputIterator>
    // vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
    //     : alloc_(alloc), start(), end(), capacity() { //TODO Check why enable_if(!is_integral) needed
          
    //     }
    void check_size(size_type n) {
      if (n >= max_size())
        throw std::length_error("Vector Max Size Exceeded");
    }

    /** @param diffmax the maximum elements of type T
     *  @param allocmax the maximum memory allocation
     *  @return The smallest of the two parameters
     */
    size_type max_size() {
      const size_t diffmax = std::numeric_limits<difference_type>::max() / sizeof(T);
      const size_t allocmax = alloc_.max_size();
      
      return (std::min)(diffmax, allocmax);
    }
  private:
    allocator_type alloc_; // the Allocator type which takes the type to allocate
    pointer start;         // start pointer
    pointer end;           // end pointer (one after last element)
    pointer capacity;      // the total amount of allocated memory
};

} // namespace ft
