/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:56:31 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:44:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_assignment()
{
    {
        ft::vector<double, leak_allocator<double> > v(128, -345783);
        ft::vector<double, leak_allocator<double> > v_copy;

        PRINT_ALL(v_copy);

        v_copy = v;

        PRINT_ALL(v_copy);

        if (v.data() == v_copy.data()) {
            std::cout << "Copy ctor doesn't do a deep copy!.";
            PRINT_FILE_LINE();
        }

        if (!std::equal(v.begin(), v.end(), v_copy.begin())) {
            std::cout << "Copy ctor error..";
            PRINT_FILE_LINE();
        }

        ft::vector<double, leak_allocator<double> > v1;
        ft::vector<double, leak_allocator<double> > v_copy1;

        PRINT_ALL(v_copy1);

        v_copy1 = v1;

        PRINT_ALL(v_copy1);

        if (v1.data() != v_copy1.data()) {
            std::cout << "Non-null pointer in vector of size 0.";
            PRINT_FILE_LINE();
        }

        if (!std::equal(v1.begin(), v1.end(), v_copy1.begin())) {
            std::cout << "Copy ctor error...";
            PRINT_FILE_LINE();
        }

        ft::vector<double, leak_allocator<double> > v2(256, -1);
        ft::vector<double, leak_allocator<double> > v_copy2(255, 56);

        PRINT_ALL(v_copy2);

        v_copy2.push_back(1);
        v_copy2 = v2;

        PRINT_ALL(v_copy2);

        if (!std::equal(v2.begin(), v2.end(), v_copy2.begin())) {
            std::cout << "Copy ctor error....";
            PRINT_FILE_LINE();
        }

        ft::vector<double, leak_allocator<double> > v3(64);
        ft::vector<double, leak_allocator<double> > v_copy3(128, -1234);

        PRINT_ALL(v_copy3);

        v_copy3 = v3;
        ft::vector<double, leak_allocator<double> >& x = v_copy3;

        PRINT_ALL(v_copy3);

        if (!std::equal(v3.begin(), v3.end(), v_copy3.begin())) {
            std::cout << "Copy ctor error.....";
            PRINT_FILE_LINE();
        }

        v_copy3 = x;

        PRINT_ALL(v_copy3);

        if (!std::equal(v3.begin(), v3.end(), v_copy3.begin())) {
            std::cout << "Copy ctor error.....";
            PRINT_FILE_LINE();
        }
    }
    {
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v1(64);
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v2(5);

        PRINT_SIZE_CAP(v1);
        PRINT_SIZE_CAP(v2);
        CHECK_DTOR(int);

        v2 = v1;

        PRINT_SIZE_CAP(v1);
        PRINT_SIZE_CAP(v2);
        CHECK_DTOR(int);
    }
    {
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v1(64);
        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > v2(5);

        PRINT_SIZE_CAP(v1);
        PRINT_SIZE_CAP(v2);
        CHECK_DTOR(int);

        v1 = v2;

        ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > >& x = v1;

        PRINT_SIZE_CAP(v1);
        PRINT_SIZE_CAP(v2);
        CHECK_DTOR(int);

        v1 = x;

        PRINT_SIZE_CAP(v1);
        PRINT_SIZE_CAP(v2);
        CHECK_DTOR(int);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_assignment();
    CHECK_LEAKS(double);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_LEAKS(int);
    CHECK_DTOR(int);
}
#endif
