/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:38:08 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/10 15:11:08 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <memory>

namespace ft {

//* Red Black Tree
template <typename T, typename Compare, typename Allocator>
class RBTree {
    // clang-format off
  public:
    typedef T 												value_type;
    typedef Compare 										value_compare;
    typedef Allocator 										allocator_type;
    typedef value_type& 									reference;
    typedef size_t 											size_type;
    typedef std::ptrdiff_t 									difference_type;
    typedef const value_type& 								const_reference;
    typedef typename Allocator::pointer 					pointer;
    typedef typename Allocator::const_pointer 				const_pointer;
	typedef tree_iterator<size_type, difference_type> 		iterator;
	typedef const_tree_iterator<size_type, difference_type> const_iterator;
    // clang-format on

  private:
    node_allocator alloc_;      // used to Allocate nodes
    allocator_type node_alloc_; // used to Allocate values in nodes
    end_node_type end_;         // Node above root that marks the end of the tree
    end_node_pointer begin_iter_;
    value_compare comp_;
    size_type size_;

}; // RBTree

} // namespace ft
