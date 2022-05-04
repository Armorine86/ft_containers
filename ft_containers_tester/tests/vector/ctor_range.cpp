/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_range.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:52:56 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:45:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "prelude.hpp"

void vec_test_ctor_range()
{
    {
        float arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        ft::vector<float, leak_allocator<float> > v(arr, &arr[10]);

        PRINT_ALL(v);

        if (!std::equal(arr, &arr[10], v.begin())) {
            std::cout << "Iterator ctor error";
            PRINT_FILE_LINE();
        }

        ft::vector<int, leak_allocator<int> > v1(arr, arr);

        PRINT_ALL(v1);

        if (!std::equal(v1.begin(), v1.end(), arr)) {
            std::cout << "Iterator ctor error.";
            PRINT_FILE_LINE();
        }

        ft::vector<float, leak_allocator<float> > v2(v.begin(), v.end());

        PRINT_ALL(v2);

        if (!std::equal(v2.begin(), v2.end(), v.begin())) {
            std::cout << "Iterator ctor error..";
            PRINT_FILE_LINE();
        }

        std::string str = "Hello World!";
        ft::vector<char, leak_allocator<char> > v3(str.begin(), str.end());

        PRINT_ALL(v3);

        if (!std::equal(str.begin(), str.end(), v3.begin())) {
            std::cout << "Iterator ctor error...";
            PRINT_FILE_LINE();
        }
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec data(64);
        vec v(data.begin(), data.end());

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(it, end);

        PRINT_VEC(v);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("");
        std::istreambuf_iterator<char> it(str), end;
        vec v(it, end);

        PRINT_VEC(v);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_ctor_range();
    CHECK_LEAKS(int);
    CHECK_LEAKS(char);
    CHECK_LEAKS(float);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
