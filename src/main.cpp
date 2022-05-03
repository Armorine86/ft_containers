#include "Iterator.hpp"
#include "Vector.hpp"
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "colors.hpp"

#define T_SIZE_TYPE typename ft::vector<T>::size_type

template <typename T>
std::ostream& operator<<(std::ostream& os, ft::vector<T>& vec) {

    os << "FT::VEC : ";
    for (size_t i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec)
{
    os << "STD::VEC: ";
    for (size_t i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    
    return os;
}

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T>
void	printSize(std::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename std::vector<T>::const_iterator it = vct.begin();
		typename std::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int main(void) {

    {
        std::cout << GREEN << "==========================================\n";
        std::cout << "|             FT_VECTORS             |\n";
        std::cout << "==========================================\n" << END << std::endl;

        ft::vector<int> vct(5);
        ft::vector<int>::iterator it = vct.begin(), ite = vct.end();

        std::cout << "len: " << (ite - it) << std::endl;
        for (; it != ite; ++it)
            *it = (ite - it);

        it = vct.begin();
        ft::vector<int> vct_range(it, --(--ite));
        for (int i = 0; it != ite; ++it)
            *it = ++i * 5;

        it = vct.begin();
        ft::vector<int> vct_copy(vct);
        for (int i = 0; it != ite; ++it)
            *it = ++i * 7;
        vct_copy.push_back(42);
        vct_copy.push_back(21);

        std::cout << "\t-- PART ONE --" << std::endl;
        printSize(vct);
        printSize(vct_range);
        printSize(vct_copy);

        vct = vct_copy;
        vct_copy = vct_range;
        vct_range.clear();

        std::cout << "\t-- PART TWO --" << std::endl;
        printSize(vct);
        printSize(vct_range);
        printSize(vct_copy);
    }

    {
        std::cout << GREEN << "==========================================\n";
        std::cout << "|             STD_VECTORS            |\n";
        std::cout << "==========================================\n" << END << std::endl;
        std::vector<int> vct(5);
        std::vector<int>::iterator it = vct.begin(), ite = vct.end();

        std::cout << "len: " << (ite - it) << std::endl;
        for (; it != ite; ++it)
            *it = (ite - it);

        it = vct.begin();
        std::vector<int> vct_range(it, --(--ite));
        for (int i = 0; it != ite; ++it)
            *it = ++i * 5;

        it = vct.begin();
        std::vector<int> vct_copy(vct);
        for (int i = 0; it != ite; ++it)
            *it = ++i * 7;
        vct_copy.push_back(42);
        vct_copy.push_back(21);

        std::cout << "\t-- PART ONE --" << std::endl;
        printSize(vct);
        printSize(vct_range);
        printSize(vct_copy);

        vct = vct_copy;
        vct_copy = vct_range;
        vct_range.clear();

        std::cout << "\t-- PART TWO --" << std::endl;
        printSize(vct);
        printSize(vct_range);
        printSize(vct_copy);
        return (0);
    }
    // {
    //     try {
    //         std::vector<int> vec;
    //         std::cout << vec.front() << std::endl;
    //     } catch (std::exception& e) {
    //         std::cerr << e.what() << std::endl;
    //     }
    // }

    // {
    //     try {
    //         ft::vector<int> vec(10);
    //         std::cout << vec.max_size() << std::endl;
    //     } catch (std::exception& e) {
    //         std::cerr << e.what() << std::endl;
    //     }
    // }

    // //* VEC PUSH_BACK SUCCESS
    // {
    //     try {
    //         ft::vector<int> vec;
    //         std::vector<int> vec1;

    //         for (size_t i = 0; i < 10; ++i)
    //             vec.push_back(i);

    //         for (size_t i = 0; i < 10; ++i)
    //             vec1.push_back(i);

    //         for (size_t i = 0; i < vec.size(); ++i)
    //             std::cout << vec.at(i) << std::flush;
    //         std::cout << vec.size() << std::endl;
    //         std::cout << vec.capacity() << std::endl;
    //         std::cout << vec.max_size() << std::endl;

    //         std::cout << std::endl;

    //         for (size_t i = 0; i < vec.size(); ++i)
    //             std::cout << vec.at(i) << std::flush;
    //         std::cout << vec1.size() << std::endl;
    //         std::cout << vec1.capacity() << std::endl;
    //         std::cout << vec1.max_size() << std::endl;

    //     } catch (std::exception &e) {
    //         std::cerr << e.what() << std::endl;
    //     }
    // }

    // //* ERASE TEST SUCCESS
    // {
    //     try {
    //         ft::vector<int> ft_vec;
    //         std::vector<int> std_vec;

    //         for (size_t i = 0; i < 10; ++i)
    //             ft_vec.push_back(i);

    //         for (size_t i = 0; i < 10; ++i)
    //             std_vec.push_back(i);

    //         std::cout << "ft::vec: " << std::flush;
    //         for (size_t i = 0; i < ft_vec.size(); ++i)
    //             std::cout << ft_vec.at(i) << std::flush;
    //         std::cout << "\nsize: " << ft_vec.size() << std::endl;
    //         std::cout << "size: " << ft_vec.capacity() << std::endl;
    //         std::cout << std::endl;

    //         std::cout << "std::vec: " << std::flush;
    //         for (size_t i = 0; i < ft_vec.size(); ++i)
    //             std::cout << std_vec.at(i) << std::flush;
    //         std::cout << "\nsize: " << std_vec.size() << std::endl;
    //         std::cout << "capacity: " << std_vec.capacity() << std::endl;
    //         std::cout << std::endl;

    //         std::cout << std::endl;

    //         ft::vector<int>::iterator it, end_it;

    //         it = ft_vec.begin();
    //         end_it = it;
    //         it += 2;
    //         end_it += 5;
    //         ft_vec.erase(it, end_it);

    //         std::cout << "ft::vec: " << std::flush;
    //         for (size_t i = 0; i < ft_vec.size(); ++i)
    //             std::cout << ft_vec.at(i) << std::flush;

    //         std::cout << "\nsize: " << ft_vec.size() << std::endl;
    //         std::cout << "size: " << ft_vec.capacity() << std::endl;
    //         std::cout << std::endl;

    //         std::vector<int>::iterator it1, end_it1;

    //         it1 = std_vec.begin();
    //         end_it1 = it1;
    //         it1 += 2;
    //         end_it1 += 5;
    //         std_vec.erase(it1, end_it1);

    //         std::cout << "std::vec: " << std::flush;
    //         for (size_t i = 0; i < std_vec.size(); ++i)
    //             std::cout << std_vec.at(i) << std::flush;

    //         std::cout << "\nsize: " << std_vec.size() << std::endl;
    //         std::cout << "capacity: " << std_vec.capacity() << std::endl;
    //         std::cout << std::endl;

    //     } catch (std::exception &e) {
    //         std::cerr << e.what() << std::endl;
    //     }
    // }

    // //* Data()  returns address

    // {
    //     ft::vector<int> ft_vec;

    //     std::vector<int> std_vec;

    // for (size_t i = 0; i < 50; ++i) {
    //     ft_vec.push_back(i);
    //     std_vec.push_back(i);
    // }

    //     int* ft_ptr = ft_vec.data();
    //     int* std_ptr = std_vec.data();

    //     std::cout << "ft_vec data: " << *ft_ptr << std::endl;
    //     std::cout << "std_vec data: " << *std_ptr << std::endl;

    //     ++ft_ptr;
    //     ++std_ptr;

    //     std::cout << std::endl;

    //     std::cout << "ft_vec data: " << *ft_ptr << std::endl;
    //     std::cout << "std_vec data: " << *std_ptr << std::endl;

    //     std::cout << std::endl;

    //     std::cout << "ft_vec data: " << ft_ptr[35] << std::endl;
    //     std::cout << "std_vec data: " << std_ptr[35] << std::endl;

    //     std::cout << std::endl;
    // }

    // {
    //     ft::vector<int> ft_vec;

    //     ft_vec.push_back(1);
    //     //ft_vec.clear();

    //     int* ft_ptr = ft_vec.data();

    //     std::vector<int> std_vec;

    //     std_vec.push_back(1);
    //     //std_vec.clear();

    //     int* std_ptr = std_vec.data();

    //     std::cout << ft_ptr << std::endl;
    //     std::cout << std_ptr << std::endl;

    //     std::cout << std::endl;

    // }

    //* SINGLE INSERT
    // {
    //     ft::vector<int> ft_vec;
    //     ft::vector<int>::iterator ft_it;

    //     std::vector<int> std_vec;
    //     std::vector<int>::iterator std_it;

    //     for (size_t i = 1; i < 6; ++i) {
    //         ft_vec.push_back(i);
    //         std_vec.push_back(i);
    //     }

    //     ft_it = ft_vec.begin() + 3;
    //     std_it = std_vec.begin() + 3;

    //     // ft_it = ft_vec.end();
    //     // std_it = std_vec.end();

    //     std::cout << "STD_VEC before Insert:\n";
    //     for (size_t i = 0; i < std_vec.size(); ++i)
    //         std::cout << " " << std_vec[i] << std::flush;

    //     std::cout << "\nSTD Capacity: " << std_vec.capacity() << std::endl;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC before Insert:" << std::endl;
    //     ft_vec.print_vec();
    //     std::cout << "\nFT Capacity: " << ft_vec.capacity() << std::endl;

    //     size_t ft_cap = ft_vec.capacity();
    //     size_t std_cap = std_vec.capacity();

    //     for (size_t i = 1; i < 16; ++i) {

    //         ft_vec.insert(ft_it, 42);
    //         if (ft_vec.capacity() > ft_cap){
    //             ft_cap = ft_vec.capacity();
    //             ft_it = ft_vec.end();
    //         }

    //         std_vec.insert(std_it, 42);
    //         if (std_vec.capacity() > std_cap) {
    //             std_cap = std_vec.capacity();
    //             std_it = std_vec.end();
    //         }
    //     }

    //     std::cout << "\nSTD_VEC AFTER Insert:\n";
    //     for (size_t i = 0; i < std_vec.size(); ++i)
    //         std::cout << std_vec[i] << " " << std::flush;

    //     std::cout << "\nSTD Capacity: " << std_vec.capacity() << "\nSize: " << ft_vec.size() << std::endl;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC AFTER Insert:" << std::endl;
    //     ft_vec.print_vec();
    //     std::cout << "\nFT Capacity: " << ft_vec.capacity() << "\nSize: " << ft_vec.size() << std::endl;
    // }

    //* INSERT N ELEMENTS
    // {
    //     ft::vector<int> vec;

    //     std::vector<int> vec2;

    //     for (size_t i = 1; i < 11; ++i) {
    //         vec.push_back(i);
    //         vec2.push_back(i);
    //     }

    //     std::cout << "\nSTD_VEC BEFORE Insert ---> Capacity: " << vec2.capacity() << std::endl;
    //     for (size_t i = 0; i < vec2.size(); ++i)
    //         std::cout << vec2[i] << " " << std::flush;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC BEFORE Insert ---> Capacity: " << vec.capacity() << std::endl;
    //     vec.print_vec();

    //     ft::vector<int>::iterator it = vec.begin() + 5;
    //     std::vector<int>::iterator it2 = vec2.begin() + 5;

    //     vec.insert(it, 7, 42);
    //     vec2.insert(it2, 7, 42);

    //     std::cout << "\nSTD_VEC AFTER Insert ---> Capacity: " << vec2.capacity() << std::endl;
    //     for (size_t i = 0; i < vec2.capacity(); ++i)
    //         std::cout << vec2[i] << " " << std::flush;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC AFTER Insert ---> Capacity: " << vec.capacity() << std::endl;
    //     vec.print_vec();
    // }

    //* INSERT ARRAY
    // {
    //     ft::vector<int> vec;

    //     std::vector<int> vec2;

    //     for (size_t i = 1; i < 9; ++i) {
    //         vec.push_back(i);
    //         vec2.push_back(i);
    //     }

    //     std::cout << "\nSTD_VEC AFTER Insert:\n";
    //     for (size_t i = 0; i < vec2.size(); ++i)
    //         std::cout << " " << vec2[i] << std::flush;

    //     std::cout << "\nSTD Capacity: " << vec2.capacity() << std::endl;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC AFTER Insert:" << std::endl;
    //     vec.print_vec();
    //     std::cout << "\nFT Capacity: " << vec.capacity() << std::endl;

    //     ft::vector<int>::iterator it = vec.begin() + 3;
    //     std::vector<int>::iterator it2 = vec2.begin() + 3;

    //     // int arr[] = {4242, 6969, 5678, 42, 42, 42, 42, 42,42,42,42,42,42,42,24,24,42};

    //     ft::vector<int> ins_vec(9, 69);
    //     std::vector<int> tmp_vec(9, 69);

    //     vec.insert(it, ins_vec.begin(), ins_vec.end());
    //     vec2.insert(it2, tmp_vec.begin(), tmp_vec.end());

    //     std::cout << "\nSTD_VEC AFTER Insert:\n";
    //     for (size_t i = 0; i < vec2.capacity(); ++i)
    //         std::cout << " " << vec2[i] << std::flush;

    //     std::cout << "\nSTD Capacity: " << vec2.capacity() << std::endl;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC AFTER Insert:" << std::endl;
    //     vec.print_vec();
    //     std::cout << "\nFT Capacity: " << vec.capacity() << std::endl;
    // }

    //* REVERSE ITERATOR
    // {
    //     ft::vector<int> vec;
    //     std::vector<int> std_vec;

    //     ft::vector<int>::reverse_iterator r_it;
    //     std::vector<int>::reverse_iterator std_r_it;

    //     for (size_t i = 1; i < 6; ++i) {
    //         vec.push_back(i * 5);
    //         std_vec.push_back(i * 5);
    //     }

    //     std::cout << "STD_VEC: ";
    //     for (size_t i = 0; i < std_vec.size(); ++i)
    //         std::cout << std_vec[i] << " " << std::flush;
    //     std::cout << std::endl;

    //     std::cout << "FT_VEC : " << std::flush;
    //     vec.print_vec();

    //     r_it = vec.rbegin();
    //     std_r_it = std_vec.rbegin();

    //     std::cout << std::endl;

    //     std::cout << "STD *IT: " << *std_r_it << std::endl;
    //     std::cout << "FT *IT : " << *r_it << std::endl;

    //     r_it = r_it + 4;
    //     std_r_it = std_r_it + 4;

    //     std::cout << std::endl;

    //     std::cout << "STD IT + 5: " << *std_r_it << std::endl;
    //     std::cout << "FT IT + 5 : " << *r_it << std::endl;

    //     r_it = r_it + 4;
    //     std_r_it = std_r_it + 4;

    //     std::cout << std::endl;

    //     std::cout << "STD IT + 5: " << *std_r_it << std::endl;
    //     std::cout << "FT IT + 5 : " << *r_it << std::endl;
    // }

    //* REVERSE ITERATORS TEST
    // {
    //     const int size = 5;
    //     ft::vector<int> vct(size);
    //     ft::vector<int>::reverse_iterator it = vct.rbegin();
    //     ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

    //     for (int i = 0; i < size; ++i)
    //         it[i] = (size - i) * 5;

    //     it = it + 5;
    //     it = 1 + it;
    //     it = it - 4;
    //     std::cout << *(it += 2) << std::endl;
    //     std::cout << *(it -= 1) << std::endl;

    //     *(it -= 2) = 42;
    //     *(it += 2) = 21;

    //     std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

    //     std::cout << "(it == const_it): " << (ite == it) << std::endl;
    //     std::cout << "(const_ite - it): " << (ite - it) << std::endl;
    //     std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
    //     std::cout << "#####################################" << std::endl;
    // }

    // {
    //     const int size = 5;
    //     std::vector<int> vct(size);
    //     std::vector<int>::reverse_iterator it = vct.rbegin();
    //     std::vector<int>::const_reverse_iterator ite = vct.rbegin();

    //     for (int i = 0; i < size; ++i)
    //         it[i] = (size - i) * 5;

    //     it = it + 5;
    //     it = 1 + it;
    //     it = it - 4;
    //     std::cout << *(it += 2) << std::endl;
    //     std::cout << *(it -= 1) << std::endl;

    //     *(it -= 2) = 42;
    //     *(it += 2) = 21;

    //     std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

    //     std::cout << "(it == const_it): " << (ite == it) << std::endl;
    //     std::cout << "(const_ite - it): " << (ite - it) << std::endl;
    //     std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
    //     std::cout << "#####################################" << std::endl;
    // }

    // {
    //     ft::vector<int> vec;
    //     std::vector<int> vec2;

    //     for (size_t i = 1; i < 11; ++i) {
    //         vec.push_back(i * 5);
    //         vec2.push_back(i * 5);
    //     }

    //     std::cout << vec2 << std::endl;
    //     std::cout << vec << std::endl;

    //     vec.resize(15);
    //     vec2.resize(15);

    //     std::cout << std::endl;
        
    //     std::cout << vec2 << "\nSize: " << vec2.size() << "\nCapacity: " << vec2.capacity() << std::endl;
    //     std::cout << std::endl;
    //     std::cout << vec << "\nSize: " << vec.size() << "\nCapacity: " << vec2.capacity() << std::endl;
    // }

    //* SWAP TEST
    // {
    //     ft::vector<int> vec(5, 1);
    //     ft::vector<int> vec2(5, 2);

    //     std::cout << vec << " Should be 1s" << std::endl;
    //     std::cout << vec2 << " Should be 2s" << std::endl;

    //     vec.swap(vec2);

    //     std::cout << vec << " Should be 2s" << std::endl;
    //     std::cout << vec2 << " Should be 1s" << std::endl;

    // }
    return 0;
}
