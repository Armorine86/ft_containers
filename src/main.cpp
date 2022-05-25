#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define STRVECTOR TESTED_NAMESPACE::vector<std::string>

template <typename T>
std::ostream& operator<<(std::ostream& os, ft::vector<T>& vec) {

    for (size_t i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";

    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
    for (size_t i = 0; i < vec.capacity(); ++i)
        os << vec[i] << " ";

    return os;
}

int main(void) {

    TESTED_NAMESPACE::map<int, const char*> m;

    m.insert(ft::make_pair(10, "Hello"));
    m.insert(ft::make_pair(5, "WAZZAAA"));
    m.insert(ft::make_pair(2, "KARAKOUKAS"));
    m.insert(ft::make_pair(6, "Shut Up Karen!"));
    m.insert(ft::make_pair(42, "Babye"));
    m.insert(ft::make_pair(35, "Pouet!"));
    m.insert(ft::make_pair(50, "Kapout!"));

    m.printTree();
    
    // {
    //     TESTED_NAMESPACE::vector<char> v;

    //     v.assign(0, 'c');
    //     std::cout << " ====== STEP 1 ======" << std::endl;
    //     std::cout << v << std::endl;
    //     std::cout << std::endl;

    //     v.assign(64, 'A');
    //     std::cout << " ====== STEP 2 ======" << std::endl;
    //     std::cout << v << std::endl;
    //     std::cout << std::endl;

    //     v.assign(32, '5');
    //     std::cout << " ====== STEP 3 ======" << std::endl;
    //     std::cout << v << std::endl;
    //     std::cout << std::endl;

    //     v.assign(49, '8');
    //     std::cout << " ====== STEP 4 ======" << std::endl;
    //     std::cout << v << std::endl;
    //     std::cout << std::endl;

    //     v.assign(77, '2');
    //     std::cout << " ====== STEP 5 ======" << std::endl;
    //     std::cout << v << std::endl;
    //     std::cout << std::endl;
    // }
}
