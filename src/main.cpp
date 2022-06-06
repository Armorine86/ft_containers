#include "map.hpp"
#include "pair.hpp"
#include "tree_utils.hpp"
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
    TESTED_NAMESPACE::map<int, const char*>::iterator root = m.end().base()->left;

    iter = m.insert(ft::make_pair(50, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(70, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(40, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(25, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(35, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(20, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(36, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(45, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(27, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(28, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.insert(ft::make_pair(65, "Hello")).first;
    m.printTree();
    std::cout << "\n------------------------" << std::endl;
    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;

    iter = m.begin();

    m.erase(m.find(20));

    m.printTree();
    std::cout << "\n------------------------" << std::endl;

    std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n" << std::endl;
}
