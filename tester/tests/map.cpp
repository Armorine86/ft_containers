/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:27:42 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/28 12:04:57 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template <typename Key, typename T>
void compare_check(const NAMESPACE::map<Key, T>& left, const NAMESPACE::map<Key, T>& right,
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

template <typename Key, typename T>
NAMESPACE::map<Key, T> build_map() {

    NAMESPACE::map<Key, T> m;
    for (size_t i = 0; i < static_cast<size_t>(rand() % 100) + 10; ++i)
        m.insert(NAMESPACE::make_pair(i, rand() % 25000));

    return m;
}

template <typename Key, typename T>
void print_map(const NAMESPACE::map<Key, T>& map, int line) {

    typedef typename NAMESPACE::map<Key, T>::const_iterator const_iter;

    std::cout << "*** line: " << line << " ***" << std::endl;

    std::cout << "Map Content:\n";
    for (const_iter it = map.begin(); it != map.end(); ++it)
        std::cout << "(key: " << it->first << " || value: " << it->second << ")" << ' ';
    std::cout << std::endl;

    std::cout << "\nMap size: " << map.size() << std::endl;
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

        NAMESPACE::map<int, int> m;

        print_map(m, __LINE__);

        NAMESPACE::map<int, int> m2(build_map<int, int>());

        std::cout << "fill Constructor:\n";
        print_map(m2, __LINE__);

        NAMESPACE::map<int, int>::iterator first = m2.begin();
        NAMESPACE::map<int, int>::iterator last = m2.end();
        NAMESPACE::map<int, int> range_m(first, last);

        std::cout << "Range Constructor:\n";
        print_map(m2, __LINE__);

        std::cout << "Copy Constructor:\n";
        NAMESPACE::map<int, int> copy_m(m2);
        print_map(copy_m, __LINE__);

        std::cout << "Assignement Operator:\n";
        std::cout << "=====================\n" << std::endl;

        NAMESPACE::map<int, int> new_m(build_map<int, int>());
        print_map(new_m, __LINE__);

        m = new_m;
        print_map(m, __LINE__);
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                    GET ALLOCATOR                    ||\n";
        std::cout << "=========================================================\n\n";

        int psize;

        NAMESPACE::map<char, int> map;
        NAMESPACE::pair<const char, int>* p;

        p = map.get_allocator().allocate(5);

        psize = sizeof(std::map<char, int>::value_type) * 5;

        std::cout << "*** line: " << __LINE__ << " ***\n"
                  << "The allocated array has a size of " << psize << " bytes." << std::endl;

        map.get_allocator().deallocate(p, 5);
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                   ELEMENTS ACCESS                   ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "at() Function\n";
        std::cout << "=============\n" << std::endl;

        NAMESPACE::map<int, int> m(build_map<int, int>());
        print_map(m, __LINE__);

        try {
            std::cout << "Value at key[5]: " << m.at(5) << std::endl;
            std::cout << "Value at key[10]: " << m.at(10) << std::endl;
            std::cout << "Value at key[2]: " << m.at(2) << std::endl;
            std::cout << "Value at key[30]: " << m.at(30) << std::endl;

        } catch (std::exception& e) {
            std::cout << "EXCEPTION COUGHT: Key does not exist\n" << std::endl;
        }

        std::cout << "operator[] Function\n";
        std::cout << "===================\n" << std::endl;

        try {
            std::cout << "Value at key[5]: " << m[5] << std::endl;
            std::cout << "Value at key[10]: " << m[10] << std::endl;
            std::cout << "Value at key[2]: " << m[2] << std::endl;
            std::cout << "Value at key[30]: " << m[30] << std::endl;

        } catch (std::exception& e) {
            std::cout << "EXCEPTION COUGHT: Key does not exist\n" << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                     ITERATORS                       ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "begin() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::map<int, int> m(build_map<int, int>());
            print_map(m, __LINE__);

            NAMESPACE::map<int, int>::iterator begin = m.begin();
            NAMESPACE::map<int, int>::iterator last = m.end();

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key / Value at begin(): " << begin->first << " || " << begin->second
                      << std::endl;

            std::cout << "\nend() Function\n";
            std::cout << "===============" << std::endl;

            --last;
            std::cout << "\n*** line: " << __LINE__ << " ***\n";
            std::cout << "Key / Value at end() - 1: " << last->first << " || " << last->second
                      << std::endl;
        }

        {

            NAMESPACE::map<int, int> m(build_map<int, int>());
            print_map(m, __LINE__);

            NAMESPACE::map<int, int>::reverse_iterator rbegin = m.rbegin();
            NAMESPACE::map<int, int>::reverse_iterator rlast = m.rend();

            std::cout << "\nrbegin() Function\n";
            std::cout << "===============\n" << std::endl;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key / Value at begin(): " << rbegin->first << " || " << rbegin->second
                      << std::endl;

            std::cout << "\nrend() Function\n";
            std::cout << "===============\n" << std::endl;

            --rlast;
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Key / Value at end() - 1: " << rlast->first << " || " << rlast->second
                      << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                      CAPACITY                       ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "empty() Function\n";
        std::cout << "===============" << std::endl;

        NAMESPACE::map<int, int> empty_m;
        print_map(empty_m, __LINE__);

        std::cout << std::boolalpha;
        std::cout << "Map is empty: " << empty_m.empty() << "\n" << std::endl;

        NAMESPACE::map<int, int> m(build_map<int, int>());
        print_map(m, __LINE__);

        std::cout << std::boolalpha;
        std::cout << "Map is empty: " << m.empty() << "\n" << std::endl;
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                      MODIFIERS                      ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "clear() Function\n";
        std::cout << "================\n" << std::endl;

        {
            NAMESPACE::map<int, int> m(build_map<int, int>());
            print_map(m, __LINE__);

            m.clear();
            print_map(m, __LINE__);
        }

        {
            std::cout << "insert() Function\n";
            std::cout << "=================\n" << std::endl;

            NAMESPACE::map<int, int> m;
            NAMESPACE::map<int, int>::iterator it = m.insert(m.end(), NAMESPACE::make_pair(64, 42));

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Iterator element Key / Value: " << it->first << " || " << it->second
                      << "\n"
                      << std::endl;
            print_map(m, __LINE__);

            it = m.insert(it, NAMESPACE::make_pair(100, 123456));
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Iterator element Key / Value: " << it->first << " || " << it->second
                      << "\n"
                      << std::endl;
            print_map(m, __LINE__);

            it = m.insert(it, NAMESPACE::make_pair(69, 420));
            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "Iterator element Key / Value: " << it->first << " || " << it->second
                      << "\n"
                      << std::endl;
            print_map(m, __LINE__);
        }

        {
            NAMESPACE::map<int, int> m(build_map<int, int>());
            NAMESPACE::map<int, int> range_m;

            NAMESPACE::map<int, int>::iterator first = m.begin();
            NAMESPACE::map<int, int>::iterator last = m.begin();

            std::advance(first, 2);
            std::advance(last, 6);

            range_m.insert(first, last);
            print_map(range_m, __LINE__);
        }

        {
            std::cout << "erase() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::map<int, int> m(build_map<int, int>());
            print_map(m, __LINE__);

            m.erase(3);
            print_map(m, __LINE__);

            NAMESPACE::map<int, int>::iterator first = m.begin();
            NAMESPACE::map<int, int>::iterator last = m.begin();

            std::advance(first, 2);
            std::advance(last, 6);

            m.erase(first, last);
            print_map(m, __LINE__);
        }

        {
            std::cout << "swap() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::map<int, int> m;
            NAMESPACE::map<int, int> filled_m(build_map<int, int>());

            m.swap(filled_m);
            print_map(m, __LINE__);
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                       LOOKUP                        ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "count() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::map<int, int> m;

            std::cout << "Map current count for key 64: " << m.count(64) << "\n" << std::endl;

            m.insert(NAMESPACE::make_pair(64, 1));
            print_map(m, __LINE__);

            std::cout << "Map current count for key 64: " << m.count(64) << "\n" << std::endl;

            m.insert(NAMESPACE::make_pair(64, 1));

            std::cout << "Map current count for key 64: " << m.count(64) << "\n" << std::endl;
        }

        {
            std::cout << "find() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::map<int, int> m(build_map<int, int>());
            NAMESPACE::map<int, int>::iterator it;

            print_map(m, __LINE__);

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

            NAMESPACE::map<int, int> m(build_map<int, int>());
            NAMESPACE::pair<NAMESPACE::map<int, int>::iterator, NAMESPACE::map<int, int>::iterator>
                p;

            print_map(m, __LINE__);

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
            NAMESPACE::map<char, int> m;
            m['I'] = 1;
            m['l'] = 2;
            m['o'] = 3;
            m['v'] = 4;
            m['e'] = 5;
            m['4'] = 6;
            m['2'] = 7;

            print_map(m, __LINE__);

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "lower bound of 'l' is: " << m.lower_bound('l')->first << std::endl;
            std::cout << "upper bound of 'l' is: " << m.upper_bound('l')->first << std::endl;

            std::cout << std::endl;

            const NAMESPACE::map<char, int> const_mymap = m;

            std::cout << "*** line: " << __LINE__ << " ***\n";
            std::cout << "lower bound of 'e' is: " << m.lower_bound('e')->first << std::endl;
            std::cout << "upper bound of 'e' is: " << m.upper_bound('e')->first << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                     KEY COMP                        ||\n";
        std::cout << "=========================================================\n\n";

        NAMESPACE::map<int, int> m(build_map<int, int>());
        print_map(m, __LINE__);

        for (NAMESPACE::map<int, int>::iterator first = m.begin(); first != m.end(); ++first) {
            NAMESPACE::map<int, int>::iterator it = m.find(rand() % m.size() - 1);
            NAMESPACE::map<int, int>::key_compare comp;

            std::cout << std::boolalpha;
            std::cout << "key: " << it->first << " is less than: " << first->first << " --> "
                      << comp(it->first, first->first) << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                COMPARE OPERATORS                    ||\n";
        std::cout << "=========================================================\n\n";

        NAMESPACE::map<int, int> m(build_map<int, int>());
        NAMESPACE::map<int, int> m2(build_map<int, int>());

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
