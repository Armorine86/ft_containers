/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:34:27 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/28 09:33:10 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template <typename T>
void compare_check(const NAMESPACE::vector<T>& left, const NAMESPACE::vector<T>& right,
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
void print_vec(const NAMESPACE::vector<T>& vec, const int& line) {
    std::cout << "*** Line: " << line << " ***" << std::endl;
    std::cout << "Vector content:\n";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";

    std::cout << "\n-------------------\n"
              << "Vec size: " << vec.size() << std::endl;
    // std::cout << "Vec capacity: " << vec.capacity() << std::endl;
    std::cout << "============================================================\n" << std::endl;
}

NAMESPACE::vector<int> build_rand() {

    int size = rand() % 250 + 50;
    NAMESPACE::vector<int> v;

    for (int i = 0; i < size; ++i)
        v.push_back(rand() % 1000);

    return v;
}

NAMESPACE::vector<int> fill_vec() {

    NAMESPACE::vector<int> v;

    for (int i = 0; i < 100; ++i)
        v.push_back(i);

    return v;
}

int main() {

    {
        std::cout << "=========================================================\n";
        std::cout << "||                CONSTRUCTOR TESTS                    ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "Default Constructor\n";
            std::cout << "===================\n" << std::endl;

            NAMESPACE::vector<int> default_v;

            print_vec(default_v, __LINE__);
        }

        {
            std::cout << "Fill Constructor\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::vector<int> fill_v(42, 60);

            print_vec(fill_v, __LINE__);
        }

        {
            std::cout << "Range Constructor\n";
            std::cout << "=================\n" << std::endl;

            NAMESPACE::vector<int> fill_v(69, 420);
            NAMESPACE::vector<int>::iterator first = fill_v.begin();
            NAMESPACE::vector<int>::iterator last = fill_v.end() - 10;

            NAMESPACE::vector<int> range_v(first, last);

            print_vec(range_v, __LINE__);
        }

        {
            std::cout << "Copy Constructor\n";
            std::cout << "=================\n" << std::endl;

            NAMESPACE::vector<int> copy_v(build_rand());

            print_vec(copy_v, __LINE__);
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                  MEMBER FUNCTIONS                   ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "Assign Operator\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::vector<int> rand_v(build_rand());
            NAMESPACE::vector<int> v;

            print_vec(rand_v, __LINE__);
            print_vec(v, __LINE__);

            v = rand_v;

            print_vec(v, __LINE__);
        }

        {
            std::cout << "Assign Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::vector<int> rand_v(build_rand());
            NAMESPACE::vector<int>::iterator first = rand_v.begin() + 5;
            NAMESPACE::vector<int>::iterator last = rand_v.end() - 15;

            NAMESPACE::vector<int> assigned_v(fill_vec());

            print_vec(assigned_v, __LINE__);

            assigned_v.assign(first, last);

            print_vec(assigned_v, __LINE__);
        }

        {
            std::cout << "Get Allocator\n";
            std::cout << "=============\n" << std::endl;

            NAMESPACE::vector<int> vector;

            NAMESPACE::vector<int>::allocator_type alloc = vector.get_allocator();

            int* ptr = alloc.allocate(42);
            std::cout << " *** Line: " << __LINE__ << " ***" << std::endl;
            std::cout << "The allocated array contains:";

            alloc.deallocate(ptr, 42);
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                   ELEMENTS ACCESS                   ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "at() Function\n";
            std::cout << "===========\n" << std::endl;

            NAMESPACE::vector<int> rand_v(build_rand());

            print_vec(rand_v, __LINE__);

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nValue at index [42]: " << rand_v.at(42) << "\n"
                      << std::endl;

            try {
                std::cout << " *** Line: " << __LINE__ << " ***"
                          << "\nValue at index [" << rand_v.size()
                          << "]: " << rand_v.at(rand_v.size()) << "\n"
                          << std::endl;
            } catch (std::exception& e) {
                std::cout << "COUGTH EXCEPTION: Index out of range " << std::endl;
            }
        }

        {
            std::cout << "\nOperator []\n";
            std::cout << "===========\n" << std::endl;

            NAMESPACE::vector<int> rand_v(build_rand());

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nValue at index [69]: " << rand_v[69] << "\n"
                      << std::endl;

            try {
                std::cout << " *** Line: " << __LINE__ << " ***"
                          << "\nValue at index [" << rand_v.size() << "]: " << rand_v[rand_v.size()]
                          << "\n"
                          << std::endl;
            } catch (std::exception& e) {
                std::cout << "COUGTH EXCEPTION: Index out of range "
                          << "\n"
                          << std::endl;
            }
        }

        std::cout << std::endl;

        {
            std::cout << "Front / Back Functions\n";
            std::cout << "======================\n" << std::endl;

            NAMESPACE::vector<int> rand_v(build_rand());

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nValue at front: " << rand_v.front() << "\n"
                      << std::endl;
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nValue at back: " << rand_v.back() << "\n"
                      << std::endl;
        }

        {
            std::cout << "data() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::vector<int> rand_v(build_rand());

            int* data = rand_v.data();

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nValue pointed by data: " << *rand_v.data() << "\n"
                      << std::endl;

            std::cout << "\nChanging value of data to 42...\n" << std::endl;
            *data = 42;

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nValue pointed by data: " << *rand_v.data() << "\n"
                      << std::endl;
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                     ITERATORS                       ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "begin() Function\n";
        std::cout << "================\n" << std::endl;

        NAMESPACE::vector<int> rand_v(build_rand());
        NAMESPACE::vector<int>::iterator begin = rand_v.begin();
        print_vec(rand_v, __LINE__);

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by begin: " << *begin << "\n"
                  << std::endl;

        std::advance(begin, 10);

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by begin: " << *begin << "\n"
                  << std::endl;

        NAMESPACE::vector<int>::iterator end = rand_v.end();

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by end: " << *end << "\n"
                  << std::endl;

        std::advance(end, -1);

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by end: " << *end << "\n"
                  << std::endl;
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                 REVERSE ITERATORS                   ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "rbegin() Function\n";
        std::cout << "================\n" << std::endl;

        NAMESPACE::vector<int> rand_v(build_rand());
        NAMESPACE::vector<int>::reverse_iterator rbegin = rand_v.rbegin();
        print_vec(rand_v, __LINE__);

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by rbegin: " << *rbegin << "\n"
                  << std::endl;

        std::advance(rbegin, 10);

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by rbegin: " << *rbegin << "\n"
                  << std::endl;

        NAMESPACE::vector<int>::reverse_iterator rend = rand_v.rend();

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by rend: " << *rend << "\n"
                  << std::endl;

        std::advance(rend, -1);

        std::cout << " *** Line: " << __LINE__ << " ***"
                  << "\nValue pointed by rend: " << *rend << "\n"
                  << std::endl;
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                 CAPACITY FUNCTIONS                  ||\n";
        std::cout << "=========================================================\n\n";

        std::cout << "empty() Function\n";
        std::cout << "================\n" << std::endl;

        {
            NAMESPACE::vector<int> empty_v;
            NAMESPACE::vector<int> rand_v(build_rand());

            print_vec(empty_v, __LINE__);
            std::cout << std::boolalpha;
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\n";
            std::cout << "Vec is empty: " << empty_v.empty() << "\n" << std::endl;

            std::cout << "Filling Vector...\n" << std::endl;
            empty_v = rand_v;

            print_vec(empty_v, __LINE__);
            std::cout << std::boolalpha;
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\n";
            std::cout << "Vec is empty: " << empty_v.empty() << "\n" << std::endl;

            std::cout << "Assinging 0 to Vector...\n" << std::endl;
            empty_v.assign(0, 0);

            print_vec(empty_v, __LINE__);
            std::cout << std::boolalpha;
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\n";
            std::cout << "Vec is empty: " << empty_v.empty() << "\n" << std::endl;
        }

        {
            std::cout << "size() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::vector<int> v(build_rand());

            print_vec(v, __LINE__);

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;

            NAMESPACE::vector<int>::iterator first = v.begin();
            NAMESPACE::vector<int>::iterator last = v.end() - 10;

            v.erase(first, last);
            print_vec(v, __LINE__);

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;

            v.clear();
            print_vec(v, __LINE__);

            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;
        }

        {
            std::cout << "\nmax_size() Function\n";
            std::cout << "===================\n" << std::endl;

            std::cout << "Unsigned Char max size: " << NAMESPACE::vector<unsigned char>().max_size()
                      << std::endl;
            std::cout << "Char max size: " << NAMESPACE::vector<char>().max_size() << std::endl;
            std::cout << "Int max size: " << NAMESPACE::vector<int>().max_size() << std::endl;
            std::cout << "Long max size: " << NAMESPACE::vector<long>().max_size() << std::endl;
            std::cout << "Short max size: " << NAMESPACE::vector<short>().max_size() << std::endl;
            std::cout << "Float max size: " << NAMESPACE::vector<float>().max_size() << std::endl;
        }

        {
            std::cout << "\nreserve() Function\n";
            std::cout << "===================\n" << std::endl;

            NAMESPACE::vector<int> v;
            NAMESPACE::vector<int> v_rand(build_rand());

            v.reserve(100);
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;

            v.reserve(0);
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;

            v.reserve(64);
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;

            v.reserve(128);
            std::cout << " *** Line: " << __LINE__ << " ***"
                      << "\nVector size: " << v.size() << std::endl;

            try {
                v.reserve(v.max_size() + 1);
                std::cout << " *** Line: " << __LINE__ << " ***"
                          << "\nVector size: " << v.size() << std::endl;
            } catch (std::exception& e) {
                std::cout << "\nEXCEPTION COUGHT: Exceeding vector max size\n" << std::endl;
            }
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                MODIFIERS FUNCTIONS                  ||\n";
        std::cout << "=========================================================\n\n";

        {
            std::cout << "\nclear() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::vector<int> v_rand(build_rand());
            print_vec(v_rand, __LINE__);

            v_rand.clear();

            std::cout << std::boolalpha;
            std::cout << " *** Line: " << __LINE__ << "\nis Vector empty: " << v_rand.empty()
                      << "\n"
                      << std::endl;

            print_vec(v_rand, __LINE__);
        }

        {
            std::cout << "\ninsert() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::vector<int> v;
            NAMESPACE::vector<int>::iterator first;

            v.insert(v.begin(), 42);
            print_vec(v, __LINE__);

            first = v.begin();
            first = v.insert(first, 69);
            print_vec(v, __LINE__);

            v.insert(first, 15, 5);
            print_vec(v, __LINE__);

            NAMESPACE::vector<int> int_v(42, 10);

            v.insert(v.begin() + 3, int_v.begin(), int_v.end());
            print_vec(v, __LINE__);
        }

        {
            std::cout << "\nerase() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::vector<int> v(build_rand());
            print_vec(v, __LINE__);

            NAMESPACE::vector<int>::iterator it = v.begin();

            it = v.erase(v.begin());
            print_vec(v, __LINE__);
            std::cout << "\nIt value after erase: " << *it << "\n" << std::endl;

            it = v.erase(v.begin() + 3);
            print_vec(v, __LINE__);
            std::cout << "\nIt value after erase: " << *it << "\n" << std::endl;

            it = v.erase(v.end(), v.end());
            std::cout << "\nIt value after erase: " << *it << "\n" << std::endl;
            print_vec(v, __LINE__);

            it = v.erase(v.end() - 5, v.end() - 1);
            std::cout << "\nIt value after erase: " << *it << "\n" << std::endl;
            print_vec(v, __LINE__);

            it = v.erase(v.begin(), v.end());
            std::cout << "\nIt value after erase: " << *it << "\n" << std::endl;
            print_vec(v, __LINE__);
        }

        {
            std::cout << "\nerase() Function\n";
            std::cout << "================\n" << std::endl;

            NAMESPACE::vector<int> v(build_rand());

            v.resize(500);
            print_vec(v, __LINE__);

            v.resize(10);
            print_vec(v, __LINE__);

            v.resize(100);
            print_vec(v, __LINE__);
        }

        {
            std::cout << "\npop_back() Function\n";
            std::cout << "===================\n" << std::endl;

            NAMESPACE::vector<int> v(build_rand());
            print_vec(v, __LINE__);

            v.pop_back();
            print_vec(v, __LINE__);

            for (size_t i = v.size(); i > 0; --i)
                v.pop_back();
            print_vec(v, __LINE__);
        }

        {
            std::cout << "\nswap() Function\n";
            std::cout << "===============\n" << std::endl;

            NAMESPACE::vector<int> v1(10, 69);
            NAMESPACE::vector<int> v2(25, 42);

            std::cout << "BEFORE SWAP\n";
            std::cout << "===========\n\n";
            std::cout << "Vector 1\n";
            print_vec(v1, __LINE__);
            std::cout << "Vector 2\n";
            print_vec(v2, __LINE__);

            v1.swap(v2);
            std::cout << "AFTER SWAP\n";
            std::cout << "==========\n\n";

            std::cout << "Vector 1\n";
            print_vec(v1, __LINE__);

            v1.resize(0);
            NAMESPACE::swap(v1, v2);
            std::cout << "Vector 1\n";
            print_vec(v1, __LINE__);
            std::cout << "Vector 2\n";
            print_vec(v2, __LINE__);
        }
    }

    {
        std::cout << "\n=========================================================\n";
        std::cout << "||                 COMPARISON OPERATORS                ||\n";
        std::cout << "=========================================================\n\n";

        NAMESPACE::vector<int> v1(4);
        NAMESPACE::vector<int> v2(4);

        compare_check(v1, v1, "v1 VS v1", __LINE__);
        compare_check(v1, v2, "v1 VS v2", __LINE__);

        v2.resize(10);

        compare_check(v1, v2, "v1 VS v2", __LINE__);
        compare_check(v2, v1, "v2 VS v1", __LINE__);

        v1[2] = 42;

        compare_check(v1, v2, "v1 VS v2", __LINE__);
        compare_check(v2, v1, "v2 VS v1", __LINE__);

        swap(v1, v2);

        compare_check(v1, v2, "v1 VS v2", __LINE__);
        compare_check(v2, v1, "v2 VS v1", __LINE__);
    }
}
