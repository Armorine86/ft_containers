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

    TESTED_NAMESPACE::map<int, const char*>::iterator iter = m.begin();

    iter = m.insert(ft::make_pair(61, "Hello")).first;
    iter = m.insert(ft::make_pair(52, "WAZZAAA")).first;
    iter = m.insert(ft::make_pair(85, "KRAKOUKAS")).first;
    m.printTree();
    std::cout << "\n\n------------------------" << std::endl;
    // iter = m.insert(ft::make_pair(76, "Shut Up Karen!")).first;
    iter = m.insert(ft::make_pair(93, "Babye")).first;
    m.printTree();
    std::cout << "\n\n------------------------" << std::endl;
    // iter = m.insert(ft::make_pair(100, "Pouet!")).first;
    iter = m.insert(ft::make_pair(87, "Kapout!")).first;

    // TESTED_NAMESPACE::map<int, const char*>::iterator result;

    // result = m.insert(iter, ft::pair<int, const char*>(420, "Enhance your calm"));

    // std::cout << result.base()->value.first << "=>" << result.base()->value.second << std::endl;

    m.printTree();
}
