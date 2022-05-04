/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_range.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:41:30 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:42:46 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_assign_range()
{
    {
        long arr[12];
        long arr1[24];

        iota(arr, &arr[12], 0);
        iota(arr1, &arr1[24], 64);

        ft::vector<long, leak_allocator<long> > v(arr, &arr[12]);

        PRINT_ALL(v);

        v.assign(arr1, &arr1[24]);

        PRINT_ALL(v);
    }
    {
        short arr[24];
        short arr1[12];

        iota(arr, &arr[24], 1024);
        iota(arr1, &arr1[12], -567);

        ft::vector<short, leak_allocator<short> > v(arr, &arr[24]);

        PRINT_ALL(v);

        v.assign(arr1, &arr1[12]);

        PRINT_ALL(v);
    }
    {
        short arr[24];

        iota(arr, &arr[24], 2048);

        ft::vector<short, leak_allocator<short> > v(48, -1);
        ft::vector<short, leak_allocator<short> > v1(arr, &arr[24]);

        PRINT_ALL(v);

        v.push_back(34);
        v.assign(v1.begin(), v1.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec data(5);

        vec v(data.begin(), data.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> c;
        v.push_back(c);
        CHECK_DTOR(int);

        vec data2(64);
        v.assign(data2.begin(), data2.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec data(64);

        vec v(data.begin(), data.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        vec data2(15);
        CHECK_DTOR(int);
        v.assign(data2.begin(), data2.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v;

        PRINT_VEC(v);

        v.assign(it, end);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(45, 'A');

        PRINT_VEC(v);

        v.assign(it, end);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(3, 'A');

        PRINT_VEC(v);

        v.assign(it, end);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_assign_range();
    CHECK_LEAKS(long);
    CHECK_LEAKS(short);
    CHECK_LEAKS(char);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_LEAKS(int);
    CHECK_DTOR(int);
}
#endif
