/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:45:21 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/28 11:55:46 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/set.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <set>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template <typename Key, typename T>
void compare_check(const NAMESPACE::set<Key, T>& left, const NAMESPACE::set<Key, T>& right,
                   std::string msg, int line) {

    std::cout << "*** Line: " << line << " ***\n";
    std::cout << "[" << msg << "]\n" << std::endl;
    std::cout << "equal: " << (left == right) << " | not equal: " << (left != right) << std::endl;
    std::cout << "lesser than: " << (left < right) << " | lesser or equal: " << (left <= right)
              << std::endl;
    std::cout << "greater than: " << (left > right) << " | greater or equal: " << (left >= right)
              << std::endl;

    std::cout << std::endl;
}

template <typename T>
NAMESPACE::set<T> build_set() {

    NAMESPACE::set<T> m;
    for (size_t i = 0; i < static_cast<size_t>(rand() % 100) + 10; ++i)
        m.insert(rand() % 25000);

    return m;
}

template <typename Key, typename T>
void print_set(const NAMESPACE::set<Key, T>& set, int line) {

    typedef typename NAMESPACE::set<Key, T>::const_iterator const_iter;

    std::cout << "*** line: " << line << " ***" << std::endl;

    std::cout << "set Content:\n";
    for (const_iter it = set.begin(); it != set.end(); ++it)
        std::cout << "key: " << *it << ' ';
    std::cout << std::endl;

    std::cout << "\nset size: " << set.size() << std::endl;
    std::cout << "\n----------------------------------------------------------------------\n\n"
              << std::endl;
}

int main() {

    {
        std::cout << "=========================================================\n";
        std::cout << "||                 MEMBER FUNCTIONS                    ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "Constructor\n";
        std::cout << "===========\n" << std::endl;

        NAMESPACE::set<int> m;

        print_set(m, __LINE__);

        NAMESPACE::set<int> m2(build_set<int>());

        std::cout << "fill Constructor:\n";
        print_set(m2, __LINE__);

        NAMESPACE::set<int>::iterator first = m2.begin();
        NAMESPACE::set<int>::iterator last = m2.end();
        NAMESPACE::set<int> range_m(first, last);

        std::cout << "Range Constructor:\n";
        print_set(m2, __LINE__);

        std::cout << "Copy Constructor:\n";
        NAMESPACE::set<int> copy_m(m2);
        print_set(copy_m, __LINE__);

        std::cout << "Assignement Operator:\n";
        std::cout << "=====================\n" << std::endl;

        NAMESPACE::set<int> new_m(build_set<int>());
        print_set(new_m, __LINE__);

        m = new_m;
        print_set(m, __LINE__);
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                    GET ALLOCATOR                    ||\n";
        std::cout << "=========================================================\n\n";

        int psize;

        NAMESPACE::set<char, int> set;
        char* p;

        p = set.get_allocator().allocate(5);

        psize = sizeof(std::set<char, int>::value_type) * 5;

        std::cout << "*** line: " << __LINE__ << " ***\n"
                  << "The allocated array has a size of " << psize << " bytes." << std::endl;

        set.get_allocator().deallocate(p, 5);
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                     ITERATORS                       ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "begin() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::set<int> m(build_set<int>());
            print_set(m, __LINE__);

            NAMESPACE::set<int>::iterator begin = m.begin();
            NAMESPACE::set<int>::iterator last = m.end();

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key at begin(): " << *begin << std::endl;

            std::cout << "\nend() Function\n";
            std::cout << "===============" << std::endl;

            --last;
            std::cout << "\n*** line: " << __LINE__ << " ***\n";
            std::cout << "Key at end() - 1: " << *last << std::endl;
        }

        {

            NAMESPACE::set<int> m(build_set<int>());
            print_set(m, __LINE__);

            NAMESPACE::set<int>::reverse_iterator rbegin = m.rbegin();
            NAMESPACE::set<int>::reverse_iterator rlast = m.rend();

            std::cout << "\nrbegin() Function\n";
            std::cout << "===============\n" << std::endl;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key at begin(): " << *rbegin << std::endl;

            std::cout << "\nrend() Function\n";
            std::cout << "===============\n" << std::endl;

            --rlast;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key at end() - 1: " << *rlast << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                      CAPACITY                       ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "empty() Function\n";
        std::cout << "===============" << std::endl;

        NAMESPACE::set<int> empty_m;
        print_set(empty_m, __LINE__);

        std::cout << std::boolalpha;
        std::cout << "set is empty: " << empty_m.empty() << "\n" << std::endl;

        NAMESPACE::set<int> m(build_set<int>());
        print_set(m, __LINE__);

        std::cout << std::boolalpha;
        std::cout << "set is empty: " << m.empty() << "\n" << std::endl;
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                      MODIFIERS                      ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "clear() Function\n";
        std::cout << "================\n" << std::endl;

        {
            NAMESPACE::set<int> m(build_set<int>());
            print_set(m, __LINE__);

            m.clear();
            print_set(m, __LINE__);
        }

        {
            std::cout << "insert() Function\n";
            std::cout << "=================\n" << std::endl;

            NAMESPACE::set<int> m;
            NAMESPACE::set<int>::iterator it = m.insert(m.end(), 64);

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Iterator element Key: " << *it << std::endl;
            print_set(m, __LINE__);

            it = m.insert(it, 100);
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Iterator element Key: " << *it << std::endl;
            print_set(m, __LINE__);

            it = m.insert(it, 69);
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Iterator element Key / Value: " << *it << std::endl;
            print_set(m, __LINE__);
        }

        {
            NAMESPACE::set<int> m(build_set<int>());
            NAMESPACE::set<int> range_m;

            NAMESPACE::set<int>::iterator first = m.begin();
            NAMESPACE::set<int>::iterator last = m.begin();

            std::advance(first, 2);
            std::advance(last, 6);

            range_m.insert(first, last);
            print_set(range_m, __LINE__);
        }

        {
            std::cout << "erase() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::set<int> m(build_set<int>());
            print_set(m, __LINE__);

            m.erase(3);
            print_set(m, __LINE__);

            NAMESPACE::set<int>::iterator first = m.begin();
            NAMESPACE::set<int>::iterator last = m.begin();

            std::advance(first, 2);
            std::advance(last, 6);

            m.erase(first, last);
            print_set(m, __LINE__);
        }

        {
            std::cout << "swap() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::set<int> m;
            NAMESPACE::set<int> filled_m(build_set<int>());

            m.swap(filled_m);
            print_set(m, __LINE__);
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                       LOOKUP                        ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "count() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::set<int> m;

            std::cout << "set current count for key 64: " << m.count(64) << "\n" << std::endl;

            m.insert(64);
            print_set(m, __LINE__);

            std::cout << "set current count for key 64: " << m.count(64) << "\n" << std::endl;

            m.insert(64);

            std::cout << "set current count for key 64: " << m.count(64) << "\n" << std::endl;
        }

        {
            std::cout << "find() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::set<int> m(build_set<int>());
            NAMESPACE::set<int>::iterator it;

            print_set(m, __LINE__);

            bool found = false;

            it = m.find(3);
            it != m.end() ? found = true : found = false;
            std::cout << std::boolalpha;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key [3] found: " << found << "\n" << std::endl;

            it = m.find(10);
            it != m.end() ? found = true : found = false;
            std::cout << std::boolalpha;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key [10] found: " << found << "\n" << std::endl;

            it = m.find(255);
            it != m.end() ? found = true : found = false;
            std::cout << std::boolalpha;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key [255] found: " << found << "\n" << std::endl;
            std::cout << std::endl;
        }

        {
            std::cout << "equal_range() Function\n";
            std::cout << "======================\n" << std::endl;

            NAMESPACE::set<int> m(build_set<int>());
            NAMESPACE::pair<NAMESPACE::set<int>::iterator, NAMESPACE::set<int>::iterator> p;

            print_set(m, __LINE__);

            p = m.equal_range(3);

            if (p.second == m.find(4))
                std::cout << "*** line: " << __LINE__ << " ***\n"
                          << "end of equal_range (p.second) is one-past p.first\n\n";
            else
                std::cout << "*** line: " << __LINE__ << " ***\n"
                          << "unexpected; p.second expected to be one-past p.first\n\n";

            p = m.equal_range(-1);

            if (p.second == m.begin())
                std::cout << "*** line: " << __LINE__ << " ***\n"
                          << "p.second is iterator to first element greater-than -1\n\n";
            else
                std::cout << "*** line: " << __LINE__ << " ***\n"
                          << "unexpected p.second\n\n";

            p = m.equal_range(m.size() - 1);

            if (p.second == m.end())
                std::cout << "*** line: " << __LINE__ << " ***\n"
                          << "p.second is iterator to first element greater-than -1\n\n";
            else
                std::cout << "*** line: " << __LINE__ << " ***\n"
                          << "unexpected p.second\n\n";
        }

        {
            NAMESPACE::set<char> m;

            m.insert('I');
            m.insert('l');
            m.insert('o');
            m.insert('v');
            m.insert('e');
            m.insert('4');
            m.insert('2');

            print_set(m, __LINE__);

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "lower bound of 'l' is: " << *m.lower_bound('l') << std::endl;
            std::cout << "upper bound of 'l' is: " << *m.upper_bound('l') << std::endl;

            std::cout << std::endl;

            const NAMESPACE::set<char> const_myset = m;

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "lower bound of 'e' is: " << *m.lower_bound('e') << std::endl;
            std::cout << "upper bound of 'e' is: " << *m.upper_bound('e') << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                     KEY COMP                        ||\n";
        std::cout << "=========================================================\n\n";

        NAMESPACE::set<int> m(build_set<int>());
        print_set(m, __LINE__);

        for (NAMESPACE::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
            NAMESPACE::set<int>::iterator it2 = m.begin();
            std::advance(it2, rand() % m.size());
            NAMESPACE::set<int>::key_compare comp;

            std::cout << std::boolalpha;
            std::cout << "key: " << *it << " is less than: " << *it2 << " --> " << comp(*it, *it2)
                      << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                COMPARE OPERATORS                    ||\n";
        std::cout << "=========================================================\n\n";

        NAMESPACE::set<int> m(build_set<int>());
        NAMESPACE::set<int> m2(build_set<int>());

        compare_check(m, m, "m VS m", __LINE__);
        compare_check(m, m2, "m VS m2", __LINE__);

        compare_check(m, m2, "m VS m2", __LINE__);
        compare_check(m2, m, "m2 VS m", __LINE__);

        m = m2;

        compare_check(m, m2, "m VS m2", __LINE__);
        compare_check(m2, m, "m2 VS m", __LINE__);

        swap(m, m2);

        compare_check(m, m2, "m VS m2", __LINE__);
        compare_check(m2, m, "m2 VS m", __LINE__);
    }
}
