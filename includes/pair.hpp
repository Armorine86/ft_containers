/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:14:45 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/10 12:31:46 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Iterator/type_traits.hpp"

namespace ft {

template <typename T1, typename T2>
class pair {
    /*
     *  ==================================================
     *  |              MEMBER VARIABLES                  |
     *  ==================================================
     */

  public:
    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;
    second_type second;

    /*
     *  ==================================================
     *  |          PUBLIC MEMBER FUNCTIONS               |
     *  ==================================================
     */

  public:
    pair() : first(first_type()), second(second_type()) {}

    pair(const first_type& x, const second_type& y) : first(x), second(y) {}

    template <typename U1, typename U2>
    pair(const pair<U1, U2>& pr) : first(pr.first), second(pr.second) {}

    pair(const pair& rhs) : first(rhs.first), second(rhs.second) {}

    pair& operator=(const pair& rhs) {
        if (this != &rhs) {
            first = rhs.first;
            second = rhs.second;
        }
        return *this;
    }
}; // pair

/*
 *  ==================================================
 *  |            NON-MEMBER FUNCTIONS                |
 *  ==================================================
 */

template <typename T1, typename T2>
inline ft::pair<T1, T2> make_pair(T1 x, T2 y) {
    return ft::pair<T1, T2>(x, y);
}

template <typename T1, typename T2>
inline bool operator==(const pair<T1, T2>& left, const ft::pair<T1, T2>& right) {

    return (left.first == right.first) && (left.second == right.second);
}

template <typename T1, typename T2>
inline bool operator!=(const pair<T1, T2>& left, const ft::pair<T1, T2>& right) {

    return !(left == right);
}

// clang-format off
template <typename T1, typename T2>
inline bool operator<(const pair<T1, T2>& left, const ft::pair<T1, T2>& right) {
    return 	left.first < right.first ||
			(!(right.first < left.first) && left.second < right.second);
}
// clang-format off

template <typename T1, typename T2>
inline bool operator<=(const pair<T1, T2>& left, const ft::pair<T1, T2>& right) {
    return !(right < left);
}

template <typename T1, typename T2>
inline bool operator>(const pair<T1, T2>& left, const ft::pair<T1, T2>& right) {

    return right < left;
}

template <typename T1, typename T2>
inline bool operator>=(const pair<T1, T2>& left, const ft::pair<T1, T2>& right) {

    return !(left < right);
}
} // namespace ft
