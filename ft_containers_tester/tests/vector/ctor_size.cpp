/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_size.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:49:32 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:46:38 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

struct abc {
    abc()
        : data(4),
          num(1000)
    {
    }

    abc(int d, long n)
        : data(d),
          num(n)
    {
    }

    int data;
    long num;
};

struct big_struct {
    double n;
    long n1;
    long n2;
    long n3;
    std::string str;
    abc a;
    void* p1;
    void* p2;
    void* p3;
    void* p4;
};

void vec_test_ctor_size()
{
    {
        ft::vector<int, leak_allocator<int> > v(64);

        PRINT_ALL(v);

        ft::vector<int, leak_allocator<int> > v1(10, 32);
        int arr[10] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };

        PRINT_ALL(v1);

        if (!std::equal(arr, &arr[10], v1.begin())) {
            std::cout << "Size ctor error";
            PRINT_FILE_LINE();
        }

        ft::vector<int, leak_allocator<int> > v2(0, 1234);

        PRINT_ALL(v2);

        try {
            ft::vector<big_struct, leak_allocator<big_struct> > v3(
                ft::vector<big_struct>().max_size() + 1);
            PRINT_MSG("Bad ctor");
        } catch (std::length_error&) {
            PRINT_MSG("Length exception");
        }
        CATCH_UNHANDLED_EX();
    }
    {
        typedef ft::vector<ctor_dtor_checker<long>, leak_allocator<ctor_dtor_checker<long> > > vec;

        vec v(64);

        PRINT_SIZE_CAP(v);

        vec v1(4);

        PRINT_LINE("Size:", v1.size());
        PRINT_LINE("Capacity:", v1.capacity());

        v1 = v;

        PRINT_LINE("Size:", v1.size());
        PRINT_LINE("Capacity:", v1.capacity());
        CHECK_DTOR(long);
    }
    {
        typedef ft::vector<ctor_dtor_checker<long>, leak_allocator<ctor_dtor_checker<long> > > vec;

        vec v(4);

        PRINT_SIZE_CAP(v);

        vec v1(64);

        PRINT_LINE("Size:", v1.size());
        PRINT_LINE("Capacity:", v1.capacity());

        v1 = v;

        PRINT_LINE("Size:", v1.size());
        PRINT_LINE("Capacity:", v1.capacity());
        CHECK_DTOR(long);
    }
    {
        ft::vector<abc, leak_allocator<abc> > v(100);

        PRINT_LINE("Data:", v[60].data);

        PRINT_LINE("Data:", v[99].num);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_ctor_size();
    CHECK_LEAKS(int);
    CHECK_LEAKS(abc);
    CHECK_LEAKS(big_struct);
    CHECK_LEAKS(ctor_dtor_checker<long>);
    CHECK_DTOR(long);
}
#endif
