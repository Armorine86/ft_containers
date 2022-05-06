#include "colors.hpp"
#include "vector.hpp"
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value = T()) {
    while (first != last) {
        *first++ = value;
        ++value;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, ft::vector<T>& vec) {

    for (size_t i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";

    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
    for (size_t i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";

    return os;
}

template <typename T>
void printSize(TESTED_NAMESPACE::vector<T> const& vct, bool print_content = true) {
    const T_SIZE_TYPE size = vct.size();
    const T_SIZE_TYPE capacity = vct.capacity();
    const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
    // Cannot limit capacity's max value because it's implementation dependent

    std::cout << "size: " << size << std::endl;
    std::cout << "capacity: " << isCapacityOk << std::endl;
    std::cout << "VCT cap: " << vct.capacity() << std::endl;
    std::cout << "max_size: " << vct.max_size() << std::endl;
    if (print_content) {
        typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
        typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
        std::cout << std::endl << "Content is:" << std::endl;
        for (; it != ite; ++it)
            std::cout << "- " << *it << std::endl;
    }
    std::cout << "###############################################" << std::endl;
}

int main(void) {
    {
        typedef TESTED_NAMESPACE::vector<std::size_t> vec;

        vec v;

        v.insert(v.begin(), 64, 1);
        std::cout << "VEC: " << v << "\n" << std::endl;
        std::cout << "SIZE: " << v.size() << "\n" << std::endl;

        v.insert(v.begin() + 10, 64, 2);
        std::cout << "VEC: " << v << "\n" << std::endl;
        std::cout << "SIZE: " << v.size() << "  CAPACITY: " << v.capacity() << std::endl;

        v.insert(v.end(), 512, 3);
        std::cout << "VEC: " << v << "\n" << std::endl;
        std::cout << "SIZE: " << v.size() << "  CAPACITY: " << v.capacity() << std::endl;

        v.insert(v.end(), 23);
        v.insert(v.end() - 2, 10, 4);
        std::cout << "VEC: " << v << "\n" << std::endl;
        std::cout << "SIZE: " << v.size() << "  CAPACITY: " << v.capacity() << std::endl;

        // v.insert(v.end(), 0, 10);
        // std::cout << "VEC: " << v << "\n" << std::endl;
        // std::cout << "SIZE: " << v.size() << "  CAPACITY: " << v.capacity() << std::endl;

        //     v.insert(v.begin(), 0, 10);
        //     std::cout << "VEC: " << v << "\n" << std::endl;

        //     v.insert(v.begin() + 50, 1, 5);
        //     std::cout << "VEC: " << v << "\n" << std::endl;

        // }
        // {
        //     typedef ft::vector<double> vec;

        //     vec v;

        //     v.insert(v.end(), 0, 23.0);

        //     v.insert(v.begin(), 0, 1.0);

        //     v.insert(v.begin(), 1, 64.0);

        //     std::cout << "VEC size: " << v.size() << std::endl;
        //     std::cout << "VEC capacity: " << v.capacity() << std::endl;
        //     std::cout << "VEC: " << v << std::endl;
        //     v.insert(v.begin(), 24000, 64.0);

        // }
        // {
        //     typedef ft::vector<int> vec;

        //     vec v;

        //     v.insert(v.end(), 40, 42);
        // }
        // {
        //     typedef ft::vector<int> vec;

        //     vec v(64);

        //     v.push_back(42);

        //     v.insert(v.end(), 2, 42);
        // }
        // {
        //     typedef ft::vector<int> vec;

        //     vec v(64);

        //     v.push_back(42);

        //     v.insert(v.end(), 222, 42);

        // }
        // {
        //     ft::vector<int> v(5000);

        //     try {
        //         v.insert(v.begin() + 115, std::numeric_limits<std::ptrdiff_t>::max(), 5);
        //     } catch (std::length_error& e) {
        //         std::cout << e.what() << std::endl;
        //     }
    }
}
