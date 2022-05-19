/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:39:17 by mmondell          #+#    #+#             */
/*   Updated: 2022/05/17 17:29:34 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RBtree.hpp"

#include <cstddef>
#include <memory>

namespace ft {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class set : public RBTree<Key, Compare, Allocator> {

  private:
    typedef RBTree<Key, Compare, Allocator> base;
 
  public:
    typedef Key key_type;
    typedef Compare key_compare;
    typedef typename base::value_type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename base::value_compare value_compare;
    typedef typename base::allocator_type allocator_type;
    typedef typename base::size_type size_type;
    typedef typename base::difference_type difference_type;
    typedef typename base::pointer pointer;
    typedef typename base::const_pointer const_pointer;
    typedef typename base::iterator iterator;
    typedef typename base::const_iterator const_iterator;
    typedef typename base::reverse_iterator reverse_iterator;
    typedef typename base::const_reverse_iterator const_reverse_iterator;

}; // class Set
} // namespace ft
