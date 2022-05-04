/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisons.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:46:34 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:42:12 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

template <typename C>
void add_values(C& s, typename C::value_type value, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i, ++value) {
        s.push(value);
    }
}

template <typename C>
void add_value(C& s, typename C::value_type value, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i) {
        s.push(value);
    }
}

void stack_test_comparisons()
{
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        if (v1 == v2) {
            PRINT_MSG("Equal");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 5);

        if (v1 == v2) {
            PRINT_MSG("Equal.");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 8);
        add_values(v2, 0, 9);

        if (v1 == v2) {
            PRINT_MSG("Equal..");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 1, 64);
        add_values(v2, 1, 64);

        if (v1 == v2) {
            PRINT_MSG("Equal...");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        if (v1 != v2) {
            PRINT_MSG("Not Equal");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 5);

        if (v1 != v2) {
            PRINT_MSG("Not Equal.");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 1);
        add_values(v2, 0, 9);

        if (v1 != v2) {
            PRINT_MSG("Not Equal..");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 64);
        add_values(v2, 0, 64);

        if (v1 != v2) {
            PRINT_MSG("Not Equal...");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        if (v1 < v2) {
            PRINT_MSG("Less");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v2, 0, 64);

        if (v1 < v2) {
            PRINT_MSG("Less.");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 0, 64);

        if (v1 < v2) {
            PRINT_MSG("Less..");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 0, 63);
        add_values(v2, 0, 64);

        if (v1 < v2) {
            PRINT_MSG("Less...");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 64);
        add_value(v2, 0, 63);

        if (v1 < v2) {
            PRINT_MSG("Less....");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 64);
        add_values(v2, 1024, 63);

        if (v1 < v2) {
            PRINT_MSG("Less......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 64);
        add_values(v2, 1024, 64);

        v1.top() = 1;

        if (v1 < v2) {
            PRINT_MSG("Less.......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 1024, 64);
        add_value(v2, 1024, 64);

        if (v1 < v2) {
            PRINT_MSG("Less........");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        if (v1 <= v2) {
            PRINT_MSG("Less Eq");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v2, 0, 64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq.");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq..");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 63);
        add_value(v2, 0, 64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq...");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 64);
        add_value(v2, 0, 63);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq....");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 63);
        add_values(v2, 1024, 64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq.....");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 64);
        add_values(v2, 1024, 63);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1, 64);
        add_values(v2, 1, 64);

        v1.top() = 1;

        if (v1 <= v2) {
            PRINT_MSG("Less Eq.......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 1, 64);
        add_value(v2, 1, 64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq........");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        if (v1 < v2) {
            PRINT_MSG("Greater");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v2, 0, 64);

        if (v1 < v2) {
            PRINT_MSG("Greater.");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 0, 64);

        if (v1 < v2) {
            PRINT_MSG("Greater..");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 0, 63);
        add_values(v2, 0, 64);

        if (v1 < v2) {
            PRINT_MSG("Greater...");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 64);
        add_value(v2, 0, 63);

        if (v1 < v2) {
            PRINT_MSG("Greater....");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 64);
        add_values(v2, 1024, 63);

        if (v1 < v2) {
            PRINT_MSG("Greater......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 64);
        add_values(v2, 1024, 64);

        v1.top() = 1;

        if (v1 < v2) {
            PRINT_MSG("Greater.......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 1024, 64);
        add_value(v2, 1024, 64);

        if (v1 < v2) {
            PRINT_MSG("Greater........");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v2, 0, 64);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq.");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 64);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq..");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 63);
        add_value(v2, 0, 64);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq...");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 0, 64);
        add_value(v2, 0, 63);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq....");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 63);
        add_values(v2, 1024, 64);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq.....");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1024, 64);
        add_values(v2, 1024, 63);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_values(v1, 1, 64);
        add_values(v2, 1, 64);

        v1.top() = 1;

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq.......");
        }
    }
    {
        ft::stack<int> v1;
        ft::stack<int> v2;

        add_value(v1, 1, 64);
        add_value(v2, 1, 64);

        if (v1 <= v2) {
            PRINT_MSG("Greater Eq........");
        }
    }
}

#ifndef SINGLE_BINARY
int main()
{
    stack_test_comparisons();
    CHECK_LEAKS(long);
    CHECK_LEAKS(int);
}
#endif
