/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:27:42 by mmondell          #+#    #+#             */
/*   Updated: 2022/06/17 15:58:02 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <iostream>
#include <limits>

#ifndef NAMESPACE
 #define NAMESPACE ft
#endif

template <typename Key, typename T>
NAMESPACE::map<Key, T> build_map() {

	NAMESPACE::map<Key, T> m;
	for (size_t i = 0; i < static_cast<size_t>(rand() % 100) + 10; ++i)
		m.insert(NAMESPACE::make_pair(i, rand() % 25000));
	
	return m;
}

template<typename Key, typename T>
void print_map(const NAMESPACE::map<Key, T>& map, int line) {
	
	typedef typename NAMESPACE::map<Key,T>::const_iterator const_iter;
    
	std::cout << "*** line: " << line << " ***" << std::endl;
	
	std::cout << "Map Content:\n";
    for (const_iter it = map.begin(); it != map.end(); ++it)
		std::cout << "(key: " <<it->first << " || value: " << it->second << ")" << ' ';
    std::cout << std::endl;
    
	std::cout << "\nMap size: " << map.size() << std::endl;
	std::cout << "\n----------------------------------------------------------------------\n\n" << std::endl;
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
		
        NAMESPACE::map<char,int> map;
        NAMESPACE::pair<const char,int>* p;
		
        p=map.get_allocator().allocate(5);
		
        psize = sizeof(std::map<char,int>::value_type)*5;
		
        std::cout << "*** line: " << __LINE__ << " ***\n" <<  "The allocated array has a size of " << psize << " bytes." << std::endl;
		
        map.get_allocator().deallocate(p,5);
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
			
		} catch (std::exception &e) {
			std::cout << "EXCEPTION COUGHT: Key does not exist\n" << std::endl;
		}
		
		std::cout << "operator[] Function\n";
		std::cout << "===================\n" << std::endl;

		try {
			std::cout << "Value at key[5]: " << m[5] << std::endl;
			std::cout << "Value at key[10]: " << m[10] << std::endl;
			std::cout << "Value at key[2]: " << m[2] << std::endl;
			std::cout << "Value at key[30]: " << m[30] << std::endl;
			
		} catch (std::exception &e) {
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
			std::cout << "Key / Value at begin(): " << begin->first << " || " << begin->second << std::endl;

			std::cout << "\nend() Function\n";
			std::cout << "===============" << std::endl;

			--last;
			std::cout << "\n*** line: " << __LINE__ << " ***\n"; 
			std::cout << "Key / Value at end() - 1: " << last->first << " || " << last->second << std::endl;
		}

		{

			NAMESPACE::map<int, int> m(build_map<int, int>());
			print_map(m, __LINE__);
			
			NAMESPACE::map<int, int>::reverse_iterator rbegin = m.rbegin();
			NAMESPACE::map<int, int>::reverse_iterator rlast = m.rend();

			std::cout << "\nrbegin() Function\n";
			std::cout << "===============\n" << std::endl;
			std::cout << "*** line: " << __LINE__ << " ***\n"; 
			std::cout << "Key / Value at begin(): " << rbegin->first << " || " << rbegin->second << std::endl;

			std::cout << "\nrend() Function\n";
			std::cout << "===============\n" << std::endl;

			--rlast;
			std::cout << "*** line: " << __LINE__ << " ***\n"; 
			std::cout << "Key / Value at end() - 1: " << rlast->first << " || " << rlast->second << std::endl;
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
			std::cout << "Iterator element Key / Value: " << it->first << " || " << it->second << "\n" << std::endl;
			print_map(m, __LINE__);
		
			it = m.insert(it, NAMESPACE::make_pair(100, 123456));
			std::cout << "*** line: " << __LINE__ << " ***\n";
			std::cout << "Iterator element Key / Value: " << it->first << " || " << it->second << "\n" << std::endl;
			print_map(m, __LINE__);

			it = m.insert(it, NAMESPACE::make_pair(69, 420));
			std::cout << "*** line: " << __LINE__ << " ***\n";
			std::cout << "Iterator element Key / Value: " << it->first << " || " << it->second << "\n" << std::endl;
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
	
	//TODO REST OF MAP TESTS
}
