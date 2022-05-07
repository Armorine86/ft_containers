/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:33 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/07 10:38:19 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include "type_traits.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <vector>

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector {
    // clang-format off
  public:
    //* ========== Member Types ==========
    typedef T                                           value_type;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef Allocator                                   allocator_type;
    typedef size_t                                      size_type;
    typedef ptrdiff_t                                   difference_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef normal_iterator<pointer, vector>            iterator; // ft::vector<T>::iterator
    typedef normal_iterator<const_pointer, vector>      const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator; // ft::vector<T>::reverse_iterator
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
    // clang-format on

    /**
     **  ==================================================
     **  |               MEMBER FUNCTIONS                 |
     **  ==================================================
     */

    //* default constructor
    explicit vector() : alloc_(allocator_type()), start_(NULL), end_(NULL), capacity_(NULL) {}

    //* Default Constructor: empty container with no elements
    explicit vector(const allocator_type& alloc)
        : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {}

    /**
     *  Fill Constructor:
     *  Container with n elements. Each element is a copy of val
     *
     *  n Number of Elements
     *  val Type of Element
     *  alloc Allocator_type
     */
    explicit vector(size_type n, const value_type& val = value_type(),
                    const Allocator& alloc = allocator_type())
        : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {

        if (n == 0)
            return;

        check_size(n);

        fill_construct(val, n);
    }

    /**
     * Container with as many elements as the range [first, last]
     * with each elements constructed from its corresponding element in that range
     * in the same order
     *
     * InputIterator
     * first start of range
     * last end of range
     */
    template <typename InputIterator>
    vector(InputIterator first,
           typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
           const allocator_type& alloc = allocator_type())
        : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {

        typedef typename iterator_traits<InputIterator>::iterator_category category;
        fill_construct(first, last, category());
    }

    //* Copy Constructor
    vector(const vector& src) : alloc_(src.alloc_), start_(NULL), end_(NULL), capacity_(NULL) {

        typedef typename iterator_traits<vector::iterator>::iterator_category category;
        fill_construct(src.start_, src.end_, category());
    }

    //* Operator= Constructor
    vector& operator=(const vector& rhs) {

        if (this == &rhs)
            return *this;

        size_type n = rhs.size();

        if (n > capacity()) {
            copy_construct(rhs.begin(), rhs.end(), n);
        } else if (size() > n) {
            iterator new_end = std::copy(rhs.begin(), rhs.end(), begin());
            range_destroy(new_end.base(), end_);
        } else {
            std::copy(rhs.start_, rhs.start_ + size(), start_);
            fill_construct(end_, rhs.start_ + size(), rhs.end_);
        }

        end_ = start_ + n;
        return *this;
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
     * Returns a reference at specified location pos
     */
    reference at(size_type pos) {
        if (pos >= size())
            throw std::out_of_range("Accessed Index is Out Of Range");

        return (*this)[pos];
    }

    /**
     * Returns a const reference at specified location pos
     */
    const_reference at(size_type pos) const {
        if (pos >= size())
            throw std::out_of_range("Accessed Index is Out Of Range");

        return (*this)[pos];
    }

    /**
     * Returns a reference to the the element at index pos
     */
    reference operator[](size_type pos) { return *(start_ + pos); }

    /**
     * Returns a const reference to the the element at index pos
     */
    const_reference operator[](size_type pos) const { return *(start_ + pos); }

    /**
     * Returns a reference to the first element of the vector
     */
    reference front() { return *start_; }

    /**
     * Returns a const reference to the first element of the vector
     */
    const_reference front() const { return *start_; }

    /**
     * Returns a reference to the last element of the vector
     */
    reference back() { return *(end_ - 1); }

    /**
     * Returns a const reference to the last element of the vector
     */
    const_reference back() const { return *(end_ - 1); }

    /**
     * Returns a pointer to the underling array serving as element storage
     */
    value_type* data() { return start_; }

    /**
     * Returns a const pointer to the underling array serving as element storage
     */
    const value_type* data() const { return start_; }

    //* =============== ITERATORS FUNCTIONS ===============

    iterator begin() { return iterator(start_); }
    const_iterator begin() const { return const_iterator(start_); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    iterator end() { return iterator(end_); }
    const_iterator end() const { return const_iterator(end_); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    //* =============== CAPACITY FUNCTIONS ===============

    /**
     * returns TRUE if the container is empty
     */
    bool empty() const { return (size() == 0) ? true : false; }

    /**
     *  diffmax the maximum elements of type T
     *  allocmax the maximum memory allocation
     *  The Vector Maximum Size
     */
    size_type max_size() const {
        const size_t diffmax = std::numeric_limits<difference_type>::max();
        const size_t allocmax = alloc_.max_size();

        return std::min(diffmax, allocmax);
    }

    /**
     * The number of elements in the Vector
     */
    size_type size() const { return static_cast<size_type>(end_ - start_); }

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
        pointer new_end = range_construct(new_start, start_, end_);

        deallocate_vec();

        start_ = new_start;
        end_ = new_end;
        capacity_ = start_ + new_cap;
    }

    /**
     * Returns the number of elements that the container has currently allocated space for.
     */
    size_type capacity() const { return static_cast<size_type>(capacity_ - start_); }

    //* =============== MODIFIERS FUNCTIONS ===============

    template <typename InputIterator>
    void assign(InputIterator first,
                typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last) {

        typedef typename iterator_traits<InputIterator>::iterator_category category;
        clear();

        range_assign(first, last, category());
    }

    /**
     * Assigns new contents to the vector, replacing its current contents, and modifying its size
     * accordingly. Any elements held in the container before the call are destroyed and replaced by
     * newly constructed elements (no assignments of elements take place). This causes an automatic
     * reallocation of the allocated storage space if -and only if- the new vector size surpasses
     * the current vector capacity.j
     */
    void assign(size_type n, const value_type& val) {

        clear();
        alloc_.deallocate(start_, capacity());
        fill_construct(val, n);
    }

    /**
     * Erase element at position pos.
     */
    iterator erase(iterator pos) {

        if (pos == end() - 1) {
            --end_;
            alloc_.destroy(pos.base());
            return end();
        }

        return erase(pos, pos + 1);
    }

    /**
     * Erases all elements in range [first, last].
     * Shifts all elements to the left.
     *
     * Returns a pointer on the element first + 1.
     * If last == end(), returns an Iterator to end_
     */
    iterator erase(iterator first, iterator last) {

        if (first == end())
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
    void clear() { erase(begin(), end()); }

    /**
     * Destroys the last element of the vector, reducing size by one.
     */
    void pop_back() {
        --end_;
        alloc_.destroy(end_);
    }

    /**
     * Adds a single element at the end of the vector.
     * If Capacity is reached, reallocate size() * 2,
     * If Vector is empty, allocate 1
     */
    void push_back(const value_type& value) {

        if (end_ == capacity_) {
            size_type new_cap = (!empty()) ? get_newcap(size() + 1) : 1;
            reserve(new_cap);
        }
        alloc_.construct(end_, value);
        ++end_;
    }

    /**
     * Insert a single element before pos.
     * Reallocates the vector if size() surpasses capacity()
     * An Iterator that points to the first of the newly inserted elements
     */
    iterator insert(iterator pos, const T& val) {

        size_type diff = std::distance(begin(), pos); // if realloc happens

        insert(pos, 1, val);

        return iterator(start_ + diff);
    }

    /**
     * Inserts N elements of value val at position pos.
     * Capacity will be the highest of either size() + n or capacity * 2
     * if a reallocation is needed
     */
    void insert(iterator pos, size_type n, const T& val) {

        if (n <= 0)
            return;

        bool need_realloc = (capacity() - size() < n) ? true : false;

        if (need_realloc) {
            size_type new_cap = (!empty()) ? get_newcap(size() + n) : capacity() + n;
            pointer new_start = alloc_.allocate(new_cap);

            pointer new_end = range_construct(new_start, start_, pos.base());
            new_end = range_construct(new_end, new_end + n, val);
            new_end = range_construct(new_end, pos.base(), end_);

            deallocate_vec();

            start_ = new_start;
            end_ = new_end;
            capacity_ = start_ + new_cap;

        } else { // no realloc needed
            iterator cpy_end = shift_right(pos, n);
            for (; pos != cpy_end; ++pos) {
                if (pos.base() < end_) {
                    alloc_.destroy(pos.base());
                    *pos = val;
                } else
                    alloc_.construct(pos.base(), val);
            }

            end_ += n;
        }
    }

    /**
     * Insert a range of element at position pos from [first, last].
     * Capacity will be the highest of either size() + n or capacity * 2
     * if a reallocation is needed
     */
    template <typename InputIter>
    void insert(iterator pos, InputIter first,
                typename enable_if<!is_integral<InputIter>::value, InputIter>::type last) {

        typedef typename iterator_traits<InputIter>::iterator_category category;
        range_insert(pos, first, last, category());
    }

    template <typename InputIter>
    void range_insert(iterator pos, InputIter first, InputIter last, std::input_iterator_tag) {

        if (pos == end()) {
            for (; first != last; ++first)
                push_back(*first);
        }
    }

    template <typename InputIter>
    void range_insert(iterator pos, InputIter first, InputIter last, std::forward_iterator_tag) {

        if (first == last)
            return;

        size_type n = std::distance(first, last);
        bool need_realloc = (capacity() - size() < n) ? true : false;

        if (need_realloc) {
            size_type new_cap = (!empty()) ? get_newcap(size() + n) : capacity() + n;
            pointer new_start = alloc_.allocate(new_cap);

            pointer new_end = range_construct(new_start, start_, pos.base());
            new_end = range_construct(new_end, first, last);
            new_end = range_construct(new_end, pos.base(), end_);

            deallocate_vec();

            start_ = new_start;
            end_ = new_end;
            capacity_ = start_ + new_cap;

        } else { // no realloc needed
            iterator cpy_end = shift_right(pos, n);
            for (; first != last; ++first, ++pos) {
                if (pos < end()) {
                    *pos = *first;
                } else
                    alloc_.construct(pos.base(), *first);
            }
            end_ += n;
        }
    }

    /**
     * Resizes the container so that it contains n elements.
     *
     * if n < size(), the container is reduced to its first n elements.
     *
     * if size() > n, the container is expanded to contains a total of n elements
     * The elements are added to the end
     */
    void resize(size_type n, value_type val = value_type()) {

        if (size() > n) {
            for (; size() > n;)
                pop_back();
        } else if (n > size()) {
            check_size(n);
            for (; size() < n;)
                push_back(val);
        }
    }

    void swap(vector& vec) {

        pointer tmp_start = vec.start_;
        pointer tmp_end = vec.end_;
        pointer tmp_cap = vec.capacity_;

        vec.start_ = this->start_;
        vec.end_ = this->end_;
        vec.capacity_ = this->capacity_;

        this->start_ = tmp_start;
        this->end_ = tmp_end;
        this->capacity_ = tmp_cap;
    }

    /*
     *  ==================================================
     *  |          PRIVATE MEMBERS FUNCTIONS             |
     *  ==================================================
     */

    template <typename InputIterator>
    void range_assign(InputIterator first, InputIterator last, std::input_iterator_tag) {
        clear();
        for (; first != last; ++first) {
            push_back(*first);
        }
    }

    /**
     * THROWS if max_size() is equal or bigger than
     * maximum allowed vector size
     */
    void check_size(size_type n) {

        size_type max = max_size();
        if (n >= max)
            throw std::length_error("Vector Max Size Exceeded");
    }

    /**
     * Shifts all elements at n position to the right as long as it is inside capacity.
     */
    iterator shift_right(iterator& pos, size_type& n) {

        iterator cpy = end() - 1;
        iterator dest = cpy + n;

        if (start_ != end_) {
            if (end_ == capacity_)
                cpy = end();

            for (; dest != pos && cpy >= pos; --cpy, --dest) {
                if (dest < end())
                    *dest = *cpy;
                else
                    alloc_.construct(dest.base(), *cpy);
            }
        }

        return ++dest;
    }

    /**
     * Shifts all elements to the left inside the vector
     * Increments first iterator
     */
    void shift_left(iterator& first, iterator& last) {

        for (iterator it = last; it != end(); ++it) {
            *first = *it;
            ++first;
        }
    }

    /**
     *   Allocates a new vector and constructs it, then deallocates the old vector
     */
    template <typename Iter>
    void copy_construct(Iter srcFirst, Iter srcLast, size_type size) {

        pointer old_start = start_;
        size_type old_cap = capacity(); //* old vector

        start_ = alloc_.allocate(size); //* new vector pointer
        end_ = start_;
        capacity_ = start_ + size;

        for (; srcFirst != srcLast; ++srcFirst) {
            alloc_.construct(end_, *srcFirst);
            ++end_;
        }

        range_deallocate(old_start, old_cap);
    }

    void fill_construct(const value_type& val, size_type n) {

        start_ = alloc_.allocate(n);
        end_ = start_;
        capacity_ = start_ + n;

        for (size_type i = 0; i != n; ++i) {
            alloc_.construct(end_, val);
            ++end_;
        }
    }

    template <typename InputIter>
    void fill_construct(InputIter first, InputIter last, std::input_iterator_tag) {
        for (; first != last; ++first)
            push_back(*first);
    }

    template <typename ForwardIterator>
    void fill_construct(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {

        difference_type n = std::distance(first, last);

        if (n > 0) {
            start_ = alloc_.allocate(n);
            end_ = start_;
            capacity_ = start_ + n;

            for (; first != last; ++first) {
                alloc_.construct(end_, *first);
                ++end_;
            }
        }
    }

    template <typename ForwardIterator>
    void fill_construct(pointer pos, ForwardIterator first, ForwardIterator last) {

        for (; first != last; ++first, (void)++pos) {
            alloc_.construct(pos, *first);
            ++end_;
        }
    }

    template <typename Iter>
    pointer range_construct(pointer dest, Iter start, Iter end) {

        for (; start != end; ++dest, (void)++start)
            alloc_.construct(dest, *start);

        return dest;
    }

    pointer range_construct(pointer dest, const_pointer end, const_reference value) {
        for (; dest != end; ++dest) {
            alloc_.construct(dest, value);
        }
        return dest;
    }

    /**
     * Deallocate elements beginning at start pointer up to capacity()
     */
    void deallocate_vec() {

        if (start_) {
            clear();
            alloc_.deallocate(start_, capacity());
        }
    }

    /**
     * Calls Allocator::destroy() on each elements from [first] to [last]
     */
    void range_destroy(pointer first, pointer last) {

        for (; first != last; first++) {
            alloc_.destroy(first);
        }
    }

    void range_destroy(pointer first, size_type end) {
        for (size_type i = 0; i < end; ++i, ++first) {
            alloc_.destroy(first);
        }
    }

    /**
     * Deallocates vector from [first] to [last]
     */
    void range_deallocate(pointer old_start, size_type old_cap) {

        range_destroy(old_start, old_cap);
        alloc_.deallocate(old_start, old_cap);
    }

    /**
     * Total_elems size() + N new elements
     * Returns new capacity based on final total elements of the vector
     */
    size_type get_newcap(const size_type& total_elems) {

        size_type new_cap = capacity();

        if (new_cap >= max_size() / 2)
            return max_size();

        return std::max(total_elems, new_cap * 2);
    }

    /*
     *  ==================================================
     *  |               PRIVATE MEMBERS                  |
     *  ==================================================
     */

  private:
    allocator_type alloc_; //* the Allocator type which takes generic type T to allocate the vector
    pointer start_;        //* start pointer to first element
    pointer end_;          //* end pointer (one after last element)
    pointer capacity_;     //* A pointer to the maximum allowed elements
};                         // class vector

/*
 *  ==================================================
 *  |             NON-MEMBER FUNCTIONS               |
 *  ==================================================
 */

template <typename T, typename Alloc>
inline void swap(vector<T, Alloc>& left, vector<T, Alloc>& right) {

    left.swap(right);
}

template <typename T, typename Alloc>
inline bool operator==(const vector<T, Alloc>& left, const vector<T, Alloc>& right) {

    return (left.size() == right.size()) && std::equal(left.begin(), left.end(), right.begin());
}

template <typename T, typename Alloc>
inline bool operator!=(const vector<T, Alloc>& left, const vector<T, Alloc>& right) {

    return !(left == right);
}

template <typename T, typename Alloc>
inline bool operator>(const vector<T, Alloc>& left, const vector<T, Alloc>& right) {

    return right < left;
}

template <typename T, typename Alloc>
inline bool operator>=(const vector<T, Alloc>& left, const vector<T, Alloc>& right) {

    return !(left < right);
}

template <typename T, typename Alloc>
inline bool operator<(const vector<T, Alloc>& left, const vector<T, Alloc>& right) {

    return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

template <typename T, typename Alloc>
inline bool operator<=(const vector<T, Alloc>& left, const vector<T, Alloc>& right) {

    return !(right < left);
}

} // namespace ft
