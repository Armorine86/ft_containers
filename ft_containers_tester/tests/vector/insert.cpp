/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:30:01 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/06 11:20:31 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"
#include <iostream>

void vec_test_insert()
{
    {
        typedef ft::vector<int, leak_allocator<int> >::iterator iter;

        ft::vector<int, leak_allocator<int> > v;

        iter it = v.insert(v.begin(), 64);

        PRINT_LINE("It:", *it);
        PRINT_SIZE_CAP(v);

        v.insert(v.begin(), 34);
        v.insert(v.begin(), 21);
        v.insert(v.begin(), 6);
        it = v.insert(v.begin(), 45);

        PRINT_LINE("It:", *it);
        PRINT_SIZE_CAP(v);
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::iterator iter;

        ft::vector<int, leak_allocator<int> > v;

        iter it = v.insert(v.end(), 64);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);

        it = v.insert(v.end(), 63);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);

        it = v.insert(v.end(), 62);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);
    }
    
    {
        typedef ft::vector<long, leak_allocator<long> >::iterator iter;

        ft::vector<long, leak_allocator<long> > v(128, -5);

        PRINT_SIZE_CAP(v);

        iter it = v.insert(v.end(), 64);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);

        it = v.insert(v.end(), -64);

        PRINT_LINE("It:", *it);
        PRINT_ALL(v);
    }
    
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v;

        ctor_dtor_checker<int> c;

        v.insert(v.begin(), c);
        std::cout << "===== STEP 1 =====" << std::endl;
        CHECK_DTOR(int);
    }
    
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v;

        ctor_dtor_checker<int> c;

        v.insert(v.end(), c);
        std::cout << "===== STEP 2 =====" << std::endl;
        CHECK_DTOR(int);
    }
    
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        std::cout << "===== STEP 3 =====" << std::endl;
        CHECK_DTOR(int);

        ctor_dtor_checker<int> c;

        PRINT_SIZE_CAP(v);

        v.push_back(c);
        std::cout << "===== STEP 4 =====" << std::endl;
        CHECK_DTOR(int);

        v.insert(v.end(), c);
        std::cout << "===== STEP 5 =====" << std::endl;
        CHECK_DTOR(int);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_insert();
    CHECK_LEAKS(int);
    CHECK_LEAKS(long);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    std::cout << "===== STEP 6 =====" << std::endl;
    CHECK_DTOR(int);
}
#endif
