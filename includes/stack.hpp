/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:22 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/06 14:45:25 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vector/Iterator.hpp"
#include "vector.hpp"

namespace ft {

template <typename T, typename Container = vector<T> >
class stack {

    //* ========== Member Types ==========

  public:
    typedef Container container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;

    //* ========== Member Variables ==========

  protected:
    container_type c;

    //* ========== Member Functions ==========

  public:
    // ========== Default Constructor ==========
    explicit stack(const Container& cont = Container()) : c(cont) {}

    // ========== Copy Constructor ==========
    stack(const stack& src) : c(src.c) {

        if (src.size() > 0)
            *this = src;
    }

    // ========== Assignement Overload ==========
    stack& operator=(const stack& rhs) {

        c = rhs.c;
        return *this;
    }

    ~stack() {}

    //* ========== Elements Access ==========

    /**
     * @return Returns a reference to the top element in the stack
     */
    reference top() { return c.back(); }

    /**
     * @return Returns a const reference to the top element in the stack
     */
    const_reference top() const { return c.back(); }

    //* ========== Capacity ==========

    /**
     * @return Returns true if the stack is empty
     */
    bool empty() { return c.empty(); }

    /**
     * @return Returns the number of elements in the stack
     */
    size_type size() const { return c.size(); }

    //* ========== Modifiers ==========

    /**
     * Inserts an element at the top of the stack
     */
    void push(const value_type& val) { c.push_back(val); }

    /**
     * Removes the top element
     */
    void pop() { c.pop_back(); }

    template <typename U, typename Cont>
    friend bool operator==(const ft::stack<U, Cont>& left, const ft::stack<U, Cont>& right);

    template <typename U, typename Cont>
    friend bool operator<(const ft::stack<U, Cont>& left, const ft::stack<U, Cont>& right);

}; //* class stack

template <typename T, typename Container>
inline bool operator!=(const ft::stack<T, Container>& left, const stack<T, Container>& right) {

    return !(left == right);
}

template <typename T, typename Container>
inline bool operator==(const ft::stack<T, Container>& left, const stack<T, Container>& right) {
    return left.c == right.c;
}

template <typename T, typename Container>
inline bool operator<(const ft::stack<T, Container>& left, const stack<T, Container>& right) {
    return left.c < right.c;
}

template <typename T, typename Container>
inline bool operator>(const ft::stack<T, Container>& left, const stack<T, Container>& right) {
    return right < left;
}

template <typename T, typename Container>
inline bool operator>=(const ft::stack<T, Container>& left, const stack<T, Container>& right) {
    return !(left < right);
}

template <typename T, typename Container>
inline bool operator<=(const ft::stack<T, Container>& left, const stack<T, Container>& right) {
    return !(right < left);
}

} // namespace ft
