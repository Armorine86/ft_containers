/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:34:32 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/10 17:23:42 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node_types.hpp"

#include <iterator>

namespace ft {

template <typename T, typename Diff>
class const_tree_iterator;

template <typename T, typename Diff>
class tree_iterator {
	
    //* ============== Member Types ==============
	typedef T 								value_type;
	typedef Diff 							difference_type;
	typedef value_type& 					reference;
	typedef value_type* 					pointer;
	typedef const_tree_iterator<T, Diff> 	const_iterator;
	typedef std::bidirectional_iterator_tag iterator_category;
	
};// class tree_iterator

}// namespace ft
