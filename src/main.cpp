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

    // std::map<char,int> mymap;

    // // first insert function version (single parameter):
    // mymap.insert ( std::pair<char,int>('a',100) );
    // mymap.insert ( std::pair<char,int>('z',200) );

    // std::pair<std::map<char,int>::iterator,bool> ret;
    // ret = mymap.insert ( std::pair<char,int>('z',500) );
    // if (ret.second==false) {
    //     std::cout << "element 'z' already existed";
    //     std::cout << " with a value of " << ret.first->second << '\n';
    // }

    // // second insert function version (with hint position):
    // std::map<char,int>::iterator it = mymap.begin();
    // mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
    // mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

    // // third insert function version (range insertion):
    // std::map<char,int> anothermap;
    // anothermap.insert(mymap.begin(),mymap.find('c'));

    // // showing contents:
    // std::cout << "mymap contains:\n";
    // for (it=mymap.begin(); it!=mymap.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';

    // std::cout << "anothermap contains:\n";
    // for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';

    // return 0;

    TESTED_NAMESPACE::map<int, const char*> m;

    TESTED_NAMESPACE::map<int, const char*>::iterator iter = m.begin();

    iter = m.insert(ft::make_pair(10, "Hello")).first;
    iter = m.insert(ft::make_pair(5, "WAZZAAA")).first ;
    iter = m.insert(ft::make_pair(2, "KARAKOUKAS")).first;
    iter = m.insert(ft::make_pair(6, "Shut Up Karen!")).first;
    iter = m.insert(ft::make_pair(42, "Babye")).first;
    iter = m.insert(ft::make_pair(35, "Pouet!")).first;
    iter = m.insert(ft::make_pair(50, "Kapout!")).first;

    TESTED_NAMESPACE::map<int, const char*>::iterator result;

    result = m.insert(iter, ft::pair<int, const char*>(420, "Enhance your calm"));

    std::cout << result.base()->value.first << "=>" << result.base()->value.second << std::endl;
    // m.printTree();
}
