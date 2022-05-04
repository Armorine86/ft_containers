/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:59:36 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/04 09:15:45 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
/* ================== Enable_if ==================
 *
 *  type   : either T or no such member, depending on the value of B
 *  SFINAE : Substitution Failure Is Not An Error
 */
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

struct true_type {
    static const bool value = true;
    typedef true_type type;
};

struct false_type {
    static const bool value = false;
    typedef false_type type;
};

template <typename T, typename U>
struct is_same : public false_type {};

template <typename T>
struct is_same<T, T> : public true_type {};

template <typename>
struct is_integral : public false_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<short int> : public true_type {};

template <>
struct is_integral<unsigned short int> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<long int> : public true_type {};

template <>
struct is_integral<unsigned long int> : public true_type {};

/*
 *  ==================================================
 *  |           LEXICO_GRAPHICAL COMPARE             |
 *  ==================================================
 */

//clang-format off
template <typename InputIter1, typename InputIter2>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                             InputIter2 last2) {

    for (; first2 != last2; ++first1, (void)++first2) {
        if (first1 == last1 || *first1 < *first2) {
            return true;
        }
        if (*first2 < *first1) {
            return false;
        }
    }
    return false;
}

template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                             Compare comp) {
    for (; first2 != last2; ++first1, (void)++first2) {
        if (first1 == last1 || comp(*first1, *first2)) {
            return true;
        }
        if (comp(*first2, *first1)) {
            return false;
        }
    }
    return false;
}
//clang-format on

} // namespace ft
