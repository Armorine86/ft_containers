/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:16:22 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/04 10:44:25 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator.hpp"
#include "Vector.hpp"
#include <stack>

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

}; //* class stack

} // namespace ft
