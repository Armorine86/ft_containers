#include "RBTree/tree_utils.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#define TESTED_TYPE int
#define NAMESPACE ft
#define STRVECTOR NAMESPACE::vector<std::string>

template <typename T>
void init_array_int_str(NAMESPACE::pair<int, std::string>* arr, std::size_t size)
{
    std::string x[64] = { "CBCId4lUU6oYms60JkNr", "V5sbXjlqYRAV1C1LgJbt", "TPcK94z2htaoK5hWpR1j",
                          "WA1JMsjadjyjQjJLxVkE", "aDhJUsH7AVnKLfzQGcPC", "DPpRIm6G9C5CWSWYLwnt",
                          "aKyxvwuxzUAksmm7s8o3", "d8NpBFRFI87WxlYiRzJB", "5RDlRrY8OFBkqtlD5R33",
                          "W4dsiGdNWranxT1qbPt9", "uUxBDNzk3Tpg1bIow0uf", "FiKAXgTFhhPhmRkfXci9",
                          "02Fxrj1KnMufOpH1gbxw", "hSV7LrNPzTKHS6h7BRW6", "YzIjmI4i4Fum1gzs9QFy",
                          "6jjGwGu20C7dXFRgdCU8", "bej1zTuyCJGa0b4KXgQO", "ckkK36lt3kBVH1PYvbib",
                          "Gs9kLamEeSWqM9ORSlzF", "oJTGXtRpq4rz6IBt2Gc2", "6XSQM096yPnzWqydO7Fl",
                          "Kw91n77jigS09IQEYFw0", "K0Qj3EOV96U6xbBDMkaP", "i0b4NYygRb7ZuT3HOE61",
                          "C6KyCaoRm5MncGCjjP0I", "6xxl5c88m0Rq5CkTPsTU", "xtZ16NJzNU4IEnzsily8",
                          "2ofwuG2e80JGsK8VdB6r", "UjhRe94EahPlXuBbIV0q", "be5WTfjjKVBU8cezAjH8",
                          "zOWJPAQLV4wgVGJTC0uV", "nuqgXoNhZpL8uMvbDcT7", "HdCk0Gm8Gn3eqcVYxcYD",
                          "PuIS5xPbBpGe3MHG7SNm", "ZY6finqJMbHpB6dKlenn", "VJfBTOFj9reLm3iGU2Fs",
                          "UFWOX8UzTSzSAGMvGRIC", "cZfcw5yVwFprkH2v3FQO", "V34DSjjaiDianUKjRFCj",
                          "j7SHtomH6GvAY8y0nL9E", "3z82NvciqTwWW2Lp7MET", "S1BDCdeUHLIVB6I8zaIc",
                          "OkuQPNHq0AnYY9Pemxpn", "yH5J2tI4oQzVsPBB226z", "aafwp6lvuOxv5JkUBUlA",
                          "RjRwqlQ0hnxYnglid2x3", "3RBzhOIHFtRtZBHNlCVv", "lttYCjRWSXYKeyIgvpJv",
                          "6KhIc7LvaTTwklmmbjBO", "IDlAqFCEdFTJcVW36RsY", "pDGkqtvKVRReq19BFVwN",
                          "88UJAeNtrlAwEu4BGiSb", "eFN5bxsWa4dAnvZdzToE", "B3cqY0IqO2IH2yGMnX7e",
                          "BRcU6oFTAC8IWuiSrTEa", "dtBZVLQMx9MBw1eak8SB", "zM2XVrazn2fXAsRHDc16",
                          "qqlM2sERpGhcZJAv3qPR", "4Lru0dOIQpWGYlcx9oyn", "HSH0O0igQruyLC1FmQVs",
                          "mXHcnXiXhKJwJ0BUSpje", "sXhbSe7MQHhvJ9XQcrrX", "aTejup4iQw70n78erKEB",
                          "1IRLC9sfQI5AzDYeotLd" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = NAMESPACE::make_pair(rand(), x[i]);
    }
}

bool mygreater(int i, int j) { return (i > j); }

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

    // {

    //     NAMESPACE::pair<int, int> intarr[64];

    //     for (std::size_t i = 0; i < 64; ++i) {
    //         intarr[i] = NAMESPACE::make_pair(rand(), rand() % 256);
    //     }


    //     NAMESPACE::map<int, int>m(intarr, intarr + 16);

    //     m.printTree();
    //         std::cout << "\n------------------------" << std::endl;
    //         std::cout << "Is valid: " << std::boolalpha << ft::valid_RBtree(m.end().base()->left) << std::endl;
            
    //     m.insert(intarr, intarr + 32);

    //     m.printTree();
    //         std::cout << "\n------------------------" << std::endl;
    //         std::cout << "Is valid: " << std::boolalpha << ft::valid_RBtree(m.end().base()->left) << std::endl;
    // }

    {
        NAMESPACE::map<int, int>m;

        for (int i = 0; i < 50000; ++i) {
            m.insert(NAMESPACE::make_pair(rand(), rand()));
        }

        m.erase(m.begin(), m.end());

    }











    // {
    //     NAMESPACE::map<int, const char*> m;

    //     NAMESPACE::map<int, const char*> to_swap;

    //     NAMESPACE::map<int, const char*>::iterator iter = m.begin();
    //     NAMESPACE::map<int, const char*>::iterator root = m.end().base()->left;

    //     iter = m.insert(ft::make_pair(50, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(70, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(40, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(25, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(35, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(20, "Hello")).first;
        // m.printTree();
        // std::cout << "\n------------------------" << std::endl;
        // std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
        //           << std::endl;

    //     iter = m.insert(ft::make_pair(36, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(45, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(27, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(28, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.insert(ft::make_pair(65, "Hello")).first;
    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;
    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     iter = m.begin();

    //     // m.erase(m.find(20));

    //     // m.printTree();
    //     // std::cout << "\n------------------------" << std::endl;

    //     std::cout << "Tree is valid: " << std::boolalpha << ft::valid_RBtree(root.base()) << "\n"
    //               << std::endl;

    //     // std::cout << "Lower Bound: " << m.lower_bound(45).base()->value.first << std::endl;

    //     // std::cout << "Upper Bound: " << m.upper_bound(45).base()->value.first << std::endl;

    //     // typedef NAMESPACE::map<int, const char*>::iterator MapIter;

    //     // ft::pair<MapIter, MapIter> range = m.equal_range(20);

    //     // for (; range.first != range.second; ++range.first)
    //     //  std::cout << "Key is: " << range.first.base()->value.first << std::endl;
    //     m.printTree();
    //     std::cout << "\n------------------------" << std::endl;
    //     m.erase(m.begin(), m.end());
    //     m.printTree();
    //     std::cout << "\n------------------------" << std::endl;
    //     std::cout   << "Tree is valid: "
    //                 << std::boolalpha
    //                 << ft::valid_RBtree(root.base())
    //                 << "\n" << std::endl;
    // }

    // {
    //     NAMESPACE::map<std::string, std::string> m;
    //     m.insert(NAMESPACE::make_pair("", "23n"));
    //     m.insert(NAMESPACE::make_pair("", "asdasdfsdfsafdsf"));
    //     m.insert(NAMESPACE::make_pair("", "asdssdfdfdffffff"));
    //     m.insert(NAMESPACE::make_pair("", "dsfdffffdfdfdsdfdffa"));
    //     m.insert(NAMESPACE::make_pair("", "sssdfs"));
    //     m.insert(NAMESPACE::make_pair("", "dfse"));
    //     m.insert(NAMESPACE::make_pair("", "sefsadfasdfasdfsadfasdfsf"));
    //     m.insert(NAMESPACE::make_pair("", "dfhkihgbnfbcx5reterjhd"));
    //     m.insert(NAMESPACE::make_pair("", "sdffgdfgrefet34thfgheewt"));
    //     m.insert(NAMESPACE::make_pair("", "98y4rtuohwidsjusdossefsse"));

    //     // m.printTree();
    //     std::cout << "\n------------------------" << std::endl;

    //     m.erase(m.begin(), m.end());

    //     std::cout << "Map size: " << m.size() << std::endl;
    // }

    // {
    //     NAMESPACE::map<char, int> mymap;

    //     mymap['a'] = 10;
    //     mymap['b'] = 20;
    //     mymap['c'] = 30;

    //     NAMESPACE::pair<NAMESPACE::map<char, int>::iterator,
    //                         NAMESPACE::map<char, int>::iterator>
    //         ret;
    //     ret = mymap.equal_range('b');

    // std::cout << "lower bound points to: ";
    // std::cout << ret.first.base()->value.first << " => " << ret.first.base()->value.second <<
    // '\n';

    // std::cout << "upper bound points to: ";
    // std::cout << ret.second.base()->value.first << " => " << ret.second.base()->value.second
    //             << '\n';
    // }
}
