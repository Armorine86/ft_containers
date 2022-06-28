/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:34:27 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/27 22:23:25 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/stack.hpp"

#include <vector>
#include <algorithm>
#include <exception>
#include <iterator>
#include <list>
#include <stack>
#include <iostream>
#include <limits>

#ifndef NAMESPACE
 #define NAMESPACE ft
#endif

template <typename T>
void	compare_check(const NAMESPACE::vector<T> &left, const NAMESPACE::vector<T> &right,  std::string msg, int line)
{

	std::cout << "*** Line: " << line << " ***\n";
	std::cout <<  "[" << msg << "]\n"  << std::endl;
	std::cout << "equal: " << (left == right) << " | not equal: " << (left != right) << std::endl;
	std::cout << "lesser than: " << (left <  right) << " | lesser or equal: " << (left <= right) << std::endl;
	std::cout << "greater than: " << (left >  right) << " | greater or equal: " << (left >= right) << std::endl;

	std::cout << std::endl;
}

template<typename T>
void printStack(NAMESPACE::stack<T> s)
{
    if (s.empty()){
        std::cout << std::endl;
        return;
    }    
    int x = s.top();
    s.pop();
    std::cout << x << ' ';
    printStack(s);
    s.push(x);
}

template<typename T>
void print_stack(const NAMESPACE::stack<T>& stack, int line) {
    std::cout << "line: " << line << std::endl;
    printStack(stack);
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

NAMESPACE::stack<int> build_rand() {

	int size = 100;
	NAMESPACE::stack<int> v;

	for (int i = 0; i < size; ++i)
		v.push(rand() % 1000);
	
	return v;
}

NAMESPACE::stack<int> fill_vec() {

	NAMESPACE::stack<int> v;

	for (int i = 0; i < 100; ++i)
		v.push(i);
	
	return v;
}

int main() {

	{
		std::cout << "\n=========================================================\n";
		std::cout << "||                  MEMBER FUNCTIONS                   ||\n";
		std::cout << "=========================================================\n\n";

		std::cout << "Assign Operator\n";
		std::cout << "===============\n" << std::endl;

		NAMESPACE::stack<int> rand_v(build_rand());
		NAMESPACE::stack<int> v;
		
		print_stack(rand_v, __LINE__);
		print_stack(v, __LINE__);

		v = rand_v;
		
		print_stack(v, __LINE__);

	}

	{
		std::cout << "\n=========================================================\n";
		std::cout << "||                   ELEMENTS ACCESS                   ||\n";
		std::cout << "=========================================================\n\n";

		std::cout << "TOP Functions\n";
		std::cout << "=================\n" << std::endl;

		NAMESPACE::stack<int> rand_v(build_rand());

		std::cout << " *** Line: " << __LINE__ << " ***" << "\nValue at front: " << rand_v.top() << "\n" << std::endl;

	}

	{
		std::cout << "\n=========================================================\n";
		std::cout << "||                 CAPACITY FUNCTIONS                  ||\n";
		std::cout << "=========================================================\n\n";

		std::cout << "empty() Function\n";
		std::cout << "================\n" << std::endl;
	
		{
			NAMESPACE::stack<int> empty_v;
			NAMESPACE::stack<int> rand_v(build_rand());
			
			print_stack(empty_v, __LINE__);
			std::cout << std::boolalpha;
			std::cout << " *** Line: " << __LINE__ << " ***" << "\n";
			std::cout << "Vec is empty: " << empty_v.empty() << "\n" << std::endl;

			std::cout << "Filling Vector...\n" << std::endl;
			empty_v = rand_v;

			print_stack(empty_v, __LINE__);
			std::cout << std::boolalpha;
			std::cout << " *** Line: " << __LINE__ << " ***" << "\n";
			std::cout << "Vec is empty: " << empty_v.empty() << "\n" << std::endl;

		}
		
		{
			std::cout << "size() Function\n";
			std::cout << "================\n" << std::endl;
			
			NAMESPACE::stack<int> v(build_rand());
			
			print_stack(v, __LINE__);

		}

	}

	{
		std::cout << "\n=========================================================\n";
		std::cout << "||                MODIFIERS FUNCTIONS                  ||\n";
		std::cout << "=========================================================\n\n";

		{
			std::cout << "\npop() Function\n";
			std::cout << "===================\n" << std::endl;

			
			NAMESPACE::stack<int> v(build_rand());
			print_stack(v, __LINE__);
			
			v.pop();
			print_stack(v, __LINE__);
			
			for (size_t i = v.size(); i > 0; --i)
				v.pop();
			print_stack(v, __LINE__);
		}
	}

	{
		std::cout << "\n=========================================================\n";
		std::cout << "||                 COMPARISON OPERATORS                ||\n";
		std::cout << "=========================================================\n\n";

		NAMESPACE::vector<int> s1(4);
		NAMESPACE::vector<int> s2(4);

		compare_check(s1, s1, "s1 VS s1", __LINE__);
		compare_check(s1, s2, "s1 VS s2", __LINE__);

		s2.resize(10);

		compare_check(s1, s2, "s1 VS s2", __LINE__);
		compare_check(s2, s1, "s2 VS s1", __LINE__);

		s1[2] = 42;

		compare_check(s1, s2, "s1 VS s2", __LINE__);
		compare_check(s2, s1, "s2 VS s1", __LINE__);

		swap(s1, s2);

		compare_check(s1, s2, "s1 VS s2", __LINE__);
		compare_check(s2, s1, "s2 VS s1", __LINE__);
	}
}
