#include "Iterator.hpp"
#include "Vector.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main(void) {


    {
        try {
            std::vector<int> vec;
            std::cout << vec.front() << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    {
        try {
            ft::vector<int> vec(10);
            std::cout << vec.max_size() << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    //* VEC PUSH_BACK SUCCESS
    {   
        try {
            ft::vector<int> vec;
            std::vector<int> vec1;

            for (size_t i = 0; i < 10; ++i)
                vec.push_back(i);

            for (size_t i = 0; i < 10; ++i)
                vec1.push_back(i);

            for (size_t i = 0; i < vec.size(); ++i)
                std::cout << vec.at(i) << std::flush;
            std::cout << vec.size() << std::endl;
            std::cout << vec.capacity() << std::endl;
            std::cout << vec.max_size() << std::endl;

            std::cout << std::endl;

            for (size_t i = 0; i < vec.size(); ++i)
                std::cout << vec.at(i) << std::flush;
            std::cout << vec1.size() << std::endl;
            std::cout << vec1.capacity() << std::endl;
            std::cout << vec1.max_size() << std::endl;

        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }



    //* ERASE TEST SUCCESS
    {
        try {
            ft::vector<int> ft_vec;
            std::vector<int> std_vec;

            for (size_t i = 0; i < 10; ++i)
                ft_vec.push_back(i);

            for (size_t i = 0; i < 10; ++i)
                std_vec.push_back(i);

            std::cout << "ft::vec: " << std::flush;
            for (size_t i = 0; i < ft_vec.size(); ++i)
                std::cout << ft_vec.at(i) << std::flush;
            std::cout << std::endl;

            std::cout << "std::vec: " << std::flush;
            for (size_t i = 0; i < ft_vec.size(); ++i)
                std::cout << std_vec.at(i) << std::flush;
            std::cout << std::endl;

            std::cout << std::endl;

            ft::vector<int>::iterator it, end_it;

            it = ft_vec.begin();
            end_it = it;
            it += 2;
            end_it += 5;
            ft_vec.erase(it, end_it);

            std::cout << "ft::vec: " << std::flush;
            for (size_t i = 0; i < ft_vec.size(); ++i)
                std::cout << ft_vec.at(i) << std::flush;

            std::cout << "\nsize: " << ft_vec.size() << std::endl;
            std::cout << std::endl;

            std::vector<int>::iterator it1, end_it1;

            it1 = std_vec.begin();
            end_it1 = it1;
            it1 += 2;
            end_it1 += 5;
            std_vec.erase(it1, end_it1);

            std::cout << "std::vec: " << std::flush;
            for (size_t i = 0; i < std_vec.size(); ++i)
                std::cout << std_vec.at(i) << std::flush;

            std::cout << "\nsize: " << ft_vec.size() << std::endl;
            std::cout << std::endl;

        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl; 
        }
    }
    return 0;
}
