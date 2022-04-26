#include "Iterator.hpp"
#include "Vector.hpp"
#include <exception>
#include <iostream>
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

    {
        try {
            ft::vector<int> vec(10);
            std::cout << vec.max_size() << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    {
        ft::vector<int> vec;
        std::vector<int> vec1;

        for (size_t i = 0; i < 10; ++i)
            vec.push_back(i);

        for (size_t i = 0; i < 10; ++i)
            vec1.push_back(i);

        std::cout << vec.size() << std::endl;
        std::cout << vec.capacity() << std::endl;
        std::cout << vec.max_size() << std::endl;

        std::cout << std::endl;

        std::cout << vec1.size() << std::endl;
        std::cout << vec1.capacity() << std::endl;
        std::cout << vec1.max_size() << std::endl;
    }
    return 0;
}
