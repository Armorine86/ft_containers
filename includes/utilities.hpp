/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:36:17 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/10 09:37:03 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
/*
 *  ==================================================
 *  |           LEXICO_GRAPHICAL COMPARE             |
 *  ==================================================
 */

// clang-format off
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

	///   Returns true if the range [first1,last1) compares lexicographically less than the range
	///   [first2,last2).
	///
	///   A lexicographical comparison involves comparing sequentially the elements
	///   that have the same position in both ranges against each other until one element is not
	///   equivalent to the other.
	///
	///   The result of comparing these first non-matching elements is the result of the lexicographical
	///   comparison.
	///
	///   If both sequences compare equal until one of them ends, the shorter sequence is
	///   lexicographically less than the longer one.
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
// clang-format on
} // namespace ft
