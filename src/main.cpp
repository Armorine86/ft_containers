#include "Iterator.hpp"
#include "Vector.hpp"
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main(void) {

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

    //     for (size_t i = 1; i < 15; ++i) {

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
    //         std::cout << " " << std_vec[i] << std::flush;

    //     std::cout << "\nSTD Capacity: " << std_vec.capacity() << std::endl;

    //     std::cout << "\n" << std::endl;

    //     std::cout << "FT_VEC AFTER Insert:" << std::endl;
    //     ft_vec.print_vec();
    //     std::cout << "\nFT Capacity: " << ft_vec.capacity() << std::endl;
    // }

    //* INSERT N ELEMENTS
    {
        ft::vector<int> vec;

        std::vector<int> vec2;

        for (size_t i = 1; i < 11; ++i) {
            vec.push_back(i);
            vec2.push_back(i);
        }

        std::cout << "\nSTD_VEC BEFORE Insert ---> Capacity: " << vec2.capacity() << std::endl;
        for (size_t i = 0; i < vec2.size(); ++i)
            std::cout << vec2[i] << " " << std::flush;

        std::cout << "\n" << std::endl;

        std::cout << "FT_VEC BEFORE Insert ---> Capacity: " << vec.capacity() << std::endl;
        vec.print_vec();

        ft::vector<int>::iterator it = vec.begin() + 5;
        std::vector<int>::iterator it2 = vec2.begin() + 5;

        vec.insert(it, 7, 42);
        vec2.insert(it2, 7, 42);

        std::cout << "\nSTD_VEC AFTER Insert ---> Capacity: " << vec2.capacity() << std::endl;
        for (size_t i = 0; i < vec2.capacity(); ++i)
            std::cout << vec2[i] << " " << std::flush;

        std::cout << "\n" << std::endl;

        std::cout << "FT_VEC AFTER Insert ---> Capacity: " << vec.capacity() << std::endl;
        vec.print_vec();
    }

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

    return 0;
}
