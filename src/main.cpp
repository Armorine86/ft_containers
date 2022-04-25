#include "Iterator.hpp"
#include "Vector.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main(void) {

    // {
    //     try {
    //         std::vector<int> vec2(3);
    //         std::cout << vec2.at(4) << std::endl;
    //     } catch (std::exception& e) {
    //         std::cerr << e.what() << std::endl;
    //     }
    // }

    {
        try {
            ft::vector<int> vec(3);
            std::cout << vec.at(4) << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
