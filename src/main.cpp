#include "vector.hpp"
#include <iostream>
#include <vector>

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

// template <typename T>
// std::ostream& operator<<(std::ostream& os, ft::vector<T>& vec) {

//     for (size_t i = 0; i < vec.size(); ++i)
//         os << vec[i] << " ";

//     return os;
// }

// template <typename T>
// std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
//     for (size_t i = 0; i < vec.size(); ++i)
//         os << vec[i] << " ";

//     return os;
// }

int main(void) {

    TESTED_NAMESPACE::vector<char> v;

    v.assign(0, 'c');

    //std::cout << v << std::endl;

}
