#include "Vector.hpp"
#include "colors.hpp"
#include <iostream>
#include <list>
#include <vector>

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

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

template <class T, class Alloc>
void cmp(const TESTED_NAMESPACE::vector<T, Alloc>& lhs,
         const TESTED_NAMESPACE::vector<T, Alloc>& rhs) {
    static int i = 0;

    std::cout << "############### [" << i++ << "] ###############" << std::endl;
    std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
    std::cout << "lt: " << (lhs < rhs) << " | le: " << (lhs <= rhs) << std::endl;
    std::cout << "gt: " << (lhs > rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int main(void) {
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct(4);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct2(4);

    cmp(vct, vct);  // 0
    cmp(vct, vct2); // 1

    vct2.resize(10);

    cmp(vct, vct2); // 2
    cmp(vct2, vct); // 3

    vct[2] = 42;

    cmp(vct, vct2); // 4
    cmp(vct2, vct); // 5

    swap(vct, vct2);

    cmp(vct, vct2); // 6
    cmp(vct2, vct); // 7

    return (0);
}
