/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisons.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:38:24 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:45:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void vec_test_comparisons()
{
    {
        ft::vector<long> v1;
        ft::vector<long> v2;

        if (v1 == v2) {
            PRINT_MSG("Equal");
        }
    }
    {
        ft::vector<long> v1(5);
        ft::vector<long> v2;

        if (v1 == v2) {
            PRINT_MSG("Equal.");
        }
    }
    {
        ft::vector<long> v1(8);
        ft::vector<long> v2(9);

        if (v1 == v2) {
            PRINT_MSG("Equal..");
        }
    }
    {
        ft::vector<long> v1(64);
        ft::vector<long> v2(64);

        iota(v1.begin(), v1.end(), 1);
        iota(v2.begin(), v2.end(), 1);

        if (v1 == v2) {
            PRINT_MSG("Equal...");
        }
    }
    {
        ft::vector<long> v1;
        ft::vector<long> v2;

        if (v1 != v2) {
            PRINT_MSG("Not Equal");
        }
    }
    {
        ft::vector<long> v1(5);
        ft::vector<long> v2;

        if (v1 != v2) {
            PRINT_MSG("Not Equal.");
        }
    }
    {
        ft::vector<long> v1(1);
        ft::vector<long> v2(9);

        if (v1 != v2) {
            PRINT_MSG("Not Equal..");
        }
    }
    {
        ft::vector<long> v1(64);
        ft::vector<long> v2(64);

        iota(v1.begin(), v1.end(), 1);
        iota(v2.begin(), v2.end(), 1);

        if (v1 != v2) {
            PRINT_MSG("Not Equal...");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2;

        if (v1 < v2) {
            PRINT_MSG("Less");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2(64);

        if (v1 < v2) {
            PRINT_MSG("Less.");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2;

        if (v1 < v2) {
            PRINT_MSG("Less..");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        if (v1 < v2) {
            PRINT_MSG("Less...");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        if (v1 < v2) {
            PRINT_MSG("Less....");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 < v2) {
            PRINT_MSG("Less.....");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 < v2) {
            PRINT_MSG("Less......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1);
        iota(v2.begin(), v2.end(), 1);

        v1.back() = 1;

        if (v1 < v2) {
            PRINT_MSG("Less.......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        if (v1 < v2) {
            PRINT_MSG("Less........");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2;

        if (v1 <= v2) {
            PRINT_MSG("Less Eq");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2(64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq.");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2;

        if (v1 <= v2) {
            PRINT_MSG("Less Eq..");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq...");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq....");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq.....");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1);
        iota(v2.begin(), v2.end(), 1);

        v1.back() = 1;

        if (v1 <= v2) {
            PRINT_MSG("Less Eq.......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        if (v1 <= v2) {
            PRINT_MSG("Less Eq........");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2;

        if (v1 > v2) {
            PRINT_MSG("Greater");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2(64);

        if (v1 > v2) {
            PRINT_MSG("Greater.");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2;

        if (v1 > v2) {
            PRINT_MSG("Greater..");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        if (v1 > v2) {
            PRINT_MSG("Greater...");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        if (v1 > v2) {
            PRINT_MSG("Greater....");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 > v2) {
            PRINT_MSG("Greater.....");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 > v2) {
            PRINT_MSG("Greater......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1);
        iota(v2.begin(), v2.end(), 1);

        v1.back() = 1;

        if (v1 > v2) {
            PRINT_MSG("Greater.......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        if (v1 > v2) {
            PRINT_MSG("Greater........");
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> v2(64);

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq.");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2;

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq..");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq...");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq....");
        }
    }
    {
        ft::vector<int> v1(63);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq.....");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(63);

        iota(v1.begin(), v1.end(), 1024);
        iota(v2.begin(), v2.end(), 1024);

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        iota(v1.begin(), v1.end(), 1);
        iota(v2.begin(), v2.end(), 1);

        v1.back() = 1;

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq.......");
        }
    }
    {
        ft::vector<int> v1(64);
        ft::vector<int> v2(64);

        if (v1 >= v2) {
            PRINT_MSG("Greater Eq........");
        }
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_comparisons();
    CHECK_LEAKS(long);
    CHECK_LEAKS(int);
}
#endif
