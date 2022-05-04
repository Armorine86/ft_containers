/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_range.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:05:18 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:49:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>

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

std::ostream& operator<<(std::ostream& os, const abc& a)
{
    os << a.data << " " << a.num;
    return os;
}

void vec_test_insert_range()
{
    {
        typedef ft::vector<abc, leak_allocator<abc> > vec;

        vec v;

        v.insert(v.begin(), v.begin(), v.begin());

        PRINT_ALL(v);

        v.insert(v.begin(), v.begin(), v.end());

        PRINT_ALL(v);

        v.insert(v.end(), v.end(), v.end());

        PRINT_ALL(v);

        abc a(1234, -9786523495);
        v.insert(v.begin(), a);

        PRINT_ALL(v);

        abc a1(7643, -3453);
        vec v1(5178, a1);
        v.insert(v.begin(), v1.begin(), v1.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<abc, leak_allocator<abc> > vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        PRINT_ALL(v);

        std::list<abc> li(63);
        v.insert(v.end(), li.begin(), li.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<abc, leak_allocator<abc> > vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        PRINT_ALL(v);

        std::list<abc> li(63);
        v.insert(v.begin(), li.begin(), li.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<abc, leak_allocator<abc> > vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        PRINT_ALL(v);

        std::list<abc> li(64);
        v.insert(v.end(), li.begin(), li.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<abc, leak_allocator<abc> > vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        PRINT_ALL(v);

        std::list<abc> li(64);
        v.insert(v.begin(), li.begin(), li.end());

        PRINT_ALL(v);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v;

        v.insert(v.begin(), v.begin(), v.begin());

        PRINT_SIZE_CAP(v);

        v.insert(v.begin(), v.begin(), v.end());

        PRINT_SIZE_CAP(v);

        v.insert(v.end(), v.end(), v.end());

        PRINT_SIZE_CAP(v);

        ctor_dtor_checker<int> a;
        v.insert(v.begin(), a);

        PRINT_SIZE_CAP(v);

        vec v1(5178, a);
        v.insert(v.begin(), v1.begin(), v1.end());

        PRINT_SIZE_CAP(v);

        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        CHECK_DTOR(int);

        ctor_dtor_checker<int> a;
        v.insert(v.begin() + 7, a);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        std::list<ctor_dtor_checker<int> > li(63);
        v.insert(v.end(), li.begin(), li.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        CHECK_DTOR(int);

        ctor_dtor_checker<int> a;
        v.insert(v.begin() + 7, a);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        std::list<ctor_dtor_checker<int> > li(63);
        v.insert(v.begin(), li.begin(), li.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        CHECK_DTOR(int);

        ctor_dtor_checker<int> a;
        v.insert(v.begin() + 7, a);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        std::list<ctor_dtor_checker<int> > li(64);
        v.insert(v.end(), li.begin(), li.end());
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);
        CHECK_DTOR(int);
    }
    {
        typedef ft::vector<ctor_dtor_checker<int>, leak_allocator<ctor_dtor_checker<int> > > vec;

        vec v(64);
        CHECK_DTOR(int);

        ctor_dtor_checker<int> a;
        v.insert(v.begin() + 7, a);
        CHECK_DTOR(int);

        PRINT_SIZE_CAP(v);

        std::list<ctor_dtor_checker<int> > li(64);
        v.insert(v.begin(), li.begin(), li.end());
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

        v.insert(v.begin(), it, end);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(45, 'A');

        PRINT_VEC(v);

        v.insert(v.begin() + 20, it, end);
    }
    {
        typedef ft::vector<char, leak_allocator<char> > vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(3, 'A');

        PRINT_VEC(v);

        v.insert(v.end(), it, end);
    }
}

#ifndef SINGLE_BINARY
int main()
{
    vec_test_insert_range();
    CHECK_LEAKS(char);
    CHECK_LEAKS(abc);
    CHECK_LEAKS(ctor_dtor_checker<int>);
    CHECK_DTOR(int);
}
#endif
