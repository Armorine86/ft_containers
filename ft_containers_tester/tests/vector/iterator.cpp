/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:57 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:51:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

static void test_begin()
{
    {
        ft::vector<int, leak_allocator<int> > v(0);

        if (v.begin() != v.end()) {
            PRINT_MSG("Iterator error");
        }
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::const_iterator const_iter;

        const ft::vector<int, leak_allocator<int> > v(0);

        const_iter it = v.begin();
        if (it != v.end()) {
            PRINT_MSG("Iterator error");
        }
    }
    {
        ft::vector<int, leak_allocator<int> > v(0);

        if (v.rbegin() != v.rend()) {
            PRINT_MSG("Iterator error");
        }
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::const_reverse_iterator const_iter;

        const ft::vector<int, leak_allocator<int> > v(0);

        const_iter it = v.rbegin();
        if (it != v.rend()) {
            PRINT_MSG("Iterator error");
        }
    }
}

static void test_end()
{
    {
        ft::vector<int, leak_allocator<int> > v(0);

        if (v.begin() != v.end()) {
            PRINT_MSG("Iterator error");
        }
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::const_iterator const_iter;

        const ft::vector<int, leak_allocator<int> > v(0);

        const_iter it = v.end();
        if (it != v.begin()) {
            PRINT_MSG("Iterator error");
        }
    }
    {
        ft::vector<int, leak_allocator<int> > v(0);

        if (v.rbegin() != v.rend()) {
            PRINT_MSG("Iterator error");
        }
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::const_reverse_iterator const_iter;

        const ft::vector<int, leak_allocator<int> > v(0);

        const_iter it = v.rend();
        if (it != v.rbegin()) {
            PRINT_MSG("Iterator error");
        }
    }
}

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

int times2(const int& x)
{
    return x * 2;
}

static void test_iterator()
{
    {
        typedef ft::vector<unsigned int, leak_allocator<unsigned int> > vec;
        typedef vec::iterator iter;

        iter it;

        PRINT_LINE("It:", it.base());

        vec v(6, 34);

        iter it2 = v.begin();

        PRINT_LINE("It2:", *it2);

        it = v.end() - 1;

        PRINT_LINE("It:", *it);
    }
    {
        typedef ft::vector<unsigned int, leak_allocator<unsigned int> > vec;
        typedef vec::iterator iter;

        vec v(1024, 7543);

        iter it = v.begin();
        iter it2 = it;

        if (it == it2) {
            PRINT_MSG("Equal iterators");
        }
        if (it != it2) {
            PRINT_MSG("Not equal iterators");
        }

        it += 10;

        if (it == it2) {
            PRINT_MSG("Equal iterators..");
        }
        if (it != it2) {
            PRINT_MSG("Not equal iterators..");
        }
    }
    {
        typedef ft::vector<long>::iterator iter;

        ft::vector<long> v(1024);
        iota(v.begin(), v.end(), 0);

        iter it = v.begin() + 10;

        PRINT_LINE("It:", *it);

        *it = 9999;

        PRINT_LINE("It:", v[10]);
    }
    {
        abc arr[30] = {};

        ft::vector<abc> v(arr, &arr[30]);

        PRINT_LINE("Elem:", v.begin()->data);
        PRINT_LINE("Elem:", (v.begin() + 20)->num);
    }
    {
        typedef ft::vector<short>::iterator iter;

        ft::vector<short> v(2048);

        iota(v.begin(), v.end(), 50);

        iter it = v.end() - 4;

        PRINT_LINE("It:", *it);

        iter it2 = it;

        it2++;
        it++;
        if (it == it2) {
            PRINT_LINE("It2:", *it2);
        }
        PRINT_LINE("It:", *it);
        ++it;

        PRINT_LINE("It:", *it);
        PRINT_LINE("It:", *it++);
        PRINT_LINE("It:", *it);
    }
    {
        typedef ft::vector<short>::iterator iter;

        ft::vector<short> v(2048);

        iota(v.begin(), v.end(), 50);

        iter it = v.end();

        it--;
        PRINT_LINE("It:", *it);

        it--;
        PRINT_LINE("It:", *it);
        --it;

        PRINT_LINE("It:", *it);
        PRINT_LINE("It:", *it--);
        PRINT_LINE("It:", *it);
    }
    {
        ft::vector<std::size_t> v(24000);

        iota(v.begin(), v.end(), 0);

        PRINT_LINE("It:", *(v.begin() + 10024));
        PRINT_LINE("It:", *(3456 + v.begin()));
        PRINT_LINE("It:", *(v.end() - 1));
        PRINT_LINE("It:", *(v.end() - 20000));
        PRINT_LINE("Size:", v.end() - v.begin());
    }
    {
        typedef ft::vector<long>::iterator iter;

        ft::vector<long> v(512);

        iota(v.begin(), v.end(), -123456);

        iter it(v.begin() + 332);

        if (v.begin() >= v.end()) {
            PRINT_MSG("Ge");
        }
        if (v.begin() <= v.end()) {
            PRINT_MSG("Le");
        }
        if (it >= it && it <= it) {
            PRINT_LINE("It:", *it);
        }
        if (it >= it - 1) {
            PRINT_LINE("It:", *(it - 1));
        }
        if (it <= it + 1) {
            PRINT_LINE("It:", *(it + 1));
        }
        if (it > it) {
            PRINT_MSG("G");
        }
        if (it < it) {
            PRINT_MSG("L");
        }
        if (it > it + 1) {
            PRINT_MSG("G.");
        }
        if (it < it - 1) {
            PRINT_MSG("L.");
        }
        if (it > it - 1) {
            PRINT_LINE("G", *(it - 1));
        }
        if (it < it + 1) {
            PRINT_LINE("L", *(it + 1));
        }
    }
    {
        typedef ft::vector<int>::iterator iter;

        ft::vector<int> v(64);

        iota(v.begin(), v.end(), 1);

        iter it = v.begin();
        iter it2 = v.end() - 1;

        PRINT_LINE("It:", *it);
        it += 23;
        PRINT_LINE("It:", *it);
        it -= 15;
        PRINT_LINE("It:", *it);

        PRINT_LINE("It2:", *it2);
        it2 -= 60;
        PRINT_LINE("It2:", *it2);
        it2 += 60;
        PRINT_LINE("It2:", *it2);
        it2 -= 3;
        PRINT_LINE("It2:", *it2);
    }
    {
        typedef ft::vector<int>::iterator iter;

        ft::vector<int> v(128);

        iota(v.begin(), v.end(), -127);

        PRINT_LINE("Begin + 10:", v.begin()[10]);

        iter it = v.begin();

        it += 56;

        PRINT_LINE("It:", it[0]);
        PRINT_LINE("It:", it[10]);
        PRINT_LINE("It:", it[5]);
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::iterator iter;

        ft::vector<int, leak_allocator<int> > v(256, 56);

        std::size_t count = 0;
        for (iter it = v.begin(); it != v.end(); ++it) {
            ++count;
        }

        PRINT_LINE("Loop count:", count);
    }
    {
        ft::vector<int> v(64, 2);

        iota(v.begin(), v.end(), 1);

        std::transform(v.begin(), v.end() - 15, v.begin(), &times2);

        for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            PRINT_LINE("V:", *it);
        }

        std::reverse(v.begin(), v.end());

        for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            PRINT_LINE("V:", *it);
        }
    }
}

static void test_riterator()
{
    {
        typedef ft::vector<unsigned int, leak_allocator<unsigned int> > vec;
        typedef vec::reverse_iterator iter;

        vec v(6, 34);

        iter it2 = v.rbegin();

        PRINT_LINE("It2:", *it2);

        iter it = v.rend() - 1;

        PRINT_LINE("It:", *it);

        void* ptr = it.base().base();
        (void)ptr;
    }
    {
        typedef ft::vector<unsigned int, leak_allocator<unsigned int> > vec;
        typedef vec::reverse_iterator iter;

        vec v(1024, 7543);

        iter it = v.rbegin();
        iter it2 = it;

        if (it == it2) {
            PRINT_MSG("Equal reverse_iterators");
        }
        if (it != it2) {
            PRINT_MSG("Not equal reverse_iterators");
        }

        it += 10;

        if (it == it2) {
            PRINT_MSG("Equal reverse_iterators..");
        }
        if (it != it2) {
            PRINT_MSG("Not equal reverse_iterators..");
        }
    }
    {
        typedef ft::vector<long>::reverse_iterator iter;

        ft::vector<long> v(1024);
        iota(v.rbegin(), v.rend(), 0);

        iter it = v.rbegin() + 10;

        PRINT_LINE("It:", *it);

        *it = 9999;

        PRINT_LINE("It:", v[10]);
    }
    {
        abc arr[30] = {};

        ft::vector<abc> v(arr, &arr[30]);

        PRINT_LINE("Elem:", v.rbegin()->data);
        PRINT_LINE("Elem:", (v.rbegin() + 20)->num);
    }
    {
        typedef ft::vector<short>::reverse_iterator iter;

        ft::vector<short> v(2048);

        iota(v.rbegin(), v.rend(), 50);

        iter it = v.rend() - 4;

        PRINT_LINE("It:", *it);

        iter it2 = it;

        it2++;
        it++;
        if (it == it2) {
            PRINT_LINE("It2:", *it2);
        }
        PRINT_LINE("It:", *it);
        ++it;

        PRINT_LINE("It:", *it);
        PRINT_LINE("It:", *it++);
        PRINT_LINE("It:", *it);
    }
    {
        typedef ft::vector<short>::reverse_iterator iter;

        ft::vector<short> v(2048);

        iota(v.rbegin(), v.rend(), 50);

        iter it = v.rend();

        it--;
        PRINT_LINE("It:", *it);

        it--;
        PRINT_LINE("It:", *it);
        --it;

        PRINT_LINE("It:", *it);
        PRINT_LINE("It:", *it--);
        PRINT_LINE("It:", *it);
    }
    {
        ft::vector<std::size_t> v(24000);

        iota(v.rbegin(), v.rend(), 0);

        PRINT_LINE("It:", *(v.rbegin() + 10024));
        PRINT_LINE("It:", *(3456 + v.rbegin()));
        PRINT_LINE("It:", *(v.rend() - 1));
        PRINT_LINE("It:", *(v.rend() - 20000));
        PRINT_LINE("Size:", v.rend() - v.rbegin());
    }
    {
        typedef ft::vector<long>::reverse_iterator iter;

        ft::vector<long> v(512);

        iota(v.rbegin(), v.rend(), -123456);

        iter it(v.rbegin() + 332);

        if (v.rbegin() >= v.rend()) {
            PRINT_MSG("Ge");
        }
        if (v.rbegin() <= v.rend()) {
            PRINT_MSG("Le");
        }
        if (it >= it && it <= it) {
            PRINT_LINE("It:", *it);
        }
        if (it >= it - 1) {
            PRINT_LINE("It:", *(it - 1));
        }
        if (it <= it + 1) {
            PRINT_LINE("It:", *(it + 1));
        }
        if (it > it) {
            PRINT_MSG("G");
        }
        if (it < it) {
            PRINT_MSG("L");
        }
        if (it > it + 1) {
            PRINT_MSG("G.");
        }
        if (it < it - 1) {
            PRINT_MSG("L.");
        }
        if (it > it - 1) {
            PRINT_LINE("G", *(it - 1));
        }
        if (it < it + 1) {
            PRINT_LINE("L", *(it + 1));
        }
    }
    {
        typedef ft::vector<int>::reverse_iterator iter;

        ft::vector<int> v(64);

        iota(v.rbegin(), v.rend(), 1);

        iter it = v.rbegin();
        iter it2 = v.rend() - 1;

        PRINT_LINE("It:", *it);
        it += 23;
        PRINT_LINE("It:", *it);
        it -= 15;
        PRINT_LINE("It:", *it);

        PRINT_LINE("It2:", *it2);
        it2 -= 60;
        PRINT_LINE("It2:", *it2);
        it2 += 60;
        PRINT_LINE("It2:", *it2);
        it2 -= 3;
        PRINT_LINE("It2:", *it2);
    }
    {
        typedef ft::vector<int>::reverse_iterator iter;

        ft::vector<int> v(128);

        iota(v.rbegin(), v.rend(), -127);

        PRINT_LINE("Begin + 10:", v.rbegin()[10]);

        iter it = v.rbegin();

        it += 56;

        PRINT_LINE("It:", it[0]);
        PRINT_LINE("It:", it[10]);
        PRINT_LINE("It:", it[5]);
    }
    {
        typedef ft::vector<int, leak_allocator<int> >::reverse_iterator iter;

        ft::vector<int, leak_allocator<int> > v(256, 56);

        std::size_t count = 0;
        for (iter it = v.rbegin(); it != v.rend(); ++it) {
            ++count;
        }

        PRINT_LINE("Loop count:", count);
    }
    {
        ft::vector<int> v(64, 2);

        iota(v.rbegin(), v.rend(), 1);

        std::transform(v.rbegin(), v.rend() - 15, v.rbegin(), &times2);

        for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
            PRINT_LINE("V:", *it);
        }

        std::reverse(v.rbegin(), v.rend());

        for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
            PRINT_LINE("V:", *it);
        }
    }
    {
        ft::vector<int> v(64, 64);

        iota(v.begin(), v.end(), 64);

        PRINT_LINE("It:", *((v.begin() + 10).base()));
        PRINT_LINE("It:", *((v.begin()).base()));
        PRINT_LINE("It:", (v.begin()).base()[0]);
        PRINT_LINE("It:", (v.begin()).base()[10]);
    }
    {
        typedef ft::vector<int>::iterator it1;
        typedef ft::vector<int>::const_iterator it2;

        ft::vector<int> v(64);

        it1 it = v.begin();
        it2 i = it;
        (void)i;
    }
}

void vec_test_iterators()
{
    test_begin();
    test_end();
    test_iterator();
    test_riterator();
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_iterators();
    CHECK_LEAKS(int);
    CHECK_LEAKS(unsigned int);
    CHECK_LEAKS(abc);
    CHECK_LEAKS(long);
    CHECK_LEAKS(short);
}
#endif
