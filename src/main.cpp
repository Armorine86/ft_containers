#include "colors.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <ios>
#include <iostream>
#include <list>
#include <sstream>
#include <utility>
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

template <typename T1, typename T2>
void pair_ops_test(TESTED_NAMESPACE::pair<T1, T2>& left, TESTED_NAMESPACE::pair<T1, T2>& right) {

    std::cout << std::boolalpha;
    std::cout << "Left < Right : " << (left < right) << std::endl;
    std::cout << "Left > Right : " << (left > right) << std::endl;
    std::cout << "Left <= Right: " << (left <= right) << std::endl;
    std::cout << "Left >= Right: " << (left >= right) << std::endl;
    std::cout << "Left == Right: " << (left == right) << std::endl;
    std::cout << "Left != Right: " << (left != right) << std::endl;
}

struct abc {
    abc() : data(4), num(1000) {}

    abc(int d, long n) : data(d), num(n) {}

    int data;
    long num;
};

struct big_struct {
    double n;
    long n1;
    long n2;
    long n3;
    std::string str;
    abc a;
    void* p1;
    void* p2;
    void* p3;
    void* p4;
};

int main(void) {
    {
        std::string c_str = "Hello, World!";
        char* str;

        str = const_cast<char*>(c_str.c_str());

        std::cout << str << std::endl;
    }

    {
        std::cout << GREEN << "========== TEST 1 ==========" << END << std::endl;
        int x = 10;
        std::string str = "Hello";
        TESTED_NAMESPACE::pair<int, std::string> p1 = TESTED_NAMESPACE::make_pair(x, str);

        std::cout << "First : " << p1.first << std::endl;
        std::cout << "Second: " << p1.second << std::endl;
        std::cout << std::endl;

        TESTED_NAMESPACE::pair<int, std::string> p2;

        p2 = p1;

        std::cout << "First P2 : " << p2.first << std::endl;
        std::cout << "Second P2: " << p2.second << std::endl;
        std::cout << std::endl;

        pair_ops_test(p1, p2);

        TESTED_NAMESPACE::pair<abc, big_struct> p3;
    }

    {
        std::cout << GREEN << "\n========== TEST 2 ==========" << END << std::endl;

        int x = 10;
        std::string str = "Hello";
        TESTED_NAMESPACE::pair<int, std::string> p1 = TESTED_NAMESPACE::make_pair(x, str);

        std::string str2 = "World";
        TESTED_NAMESPACE::pair<int, std::string> p2 = TESTED_NAMESPACE::make_pair(x, str2);

        std::cout << "First : " << p1.first << std::endl;
        std::cout << "Second: " << p1.second << std::endl;
        std::cout << std::endl;

        std::cout << "First P2 : " << p2.first << std::endl;
        std::cout << "Second P2: " << p2.second << std::endl;
        std::cout << std::endl;

        pair_ops_test(p1, p2);
    }

    {
        std::cout << GREEN << "\n========== TEST 3 ==========" << END << std::endl;

        int x = 10;
        std::string str = "Hello";
        TESTED_NAMESPACE::pair<int, std::string> p1 = TESTED_NAMESPACE::make_pair(x, str);

        std::string str2 = "World";
        int y = 5;
        TESTED_NAMESPACE::pair<int, std::string> p2 = TESTED_NAMESPACE::make_pair(y, str2);

        std::cout << "First : " << p1.first << std::endl;
        std::cout << "Second: " << p1.second << std::endl;
        std::cout << std::endl;

        std::cout << "First P2 : " << p2.first << std::endl;
        std::cout << "Second P2: " << p2.second << std::endl;
        std::cout << std::endl;

        pair_ops_test(p1, p2);
    }
}

/*int main(void) {

    // ASSIGN
    {
        TESTED_NAMESPACE::vector<int> v(1);

        v.assign(64, 10);
    }
    {
        TESTED_NAMESPACE::vector<int> v(128);

        v.assign(32, -1);
    }
    {
        TESTED_NAMESPACE::vector<int> v(512);

        v.push_back(7);

        v.assign(564, 101010);
    }
    {
        TESTED_NAMESPACE::vector<int> v(512, 123);

        v.assign(0, 1);
    }
    {
        TESTED_NAMESPACE::vector<int> v(512);

        v.push_back(42);

        v.assign(564, 42);
    }
    {
        TESTED_NAMESPACE::vector<int> v(5);

        v.push_back(42);

        v.assign(8, 42);
    }
    {
        TESTED_NAMESPACE::vector<int> v(65);

        v.assign(8, 42);
    }
    {
        TESTED_NAMESPACE::vector<int> v;

        v.assign(0, 101010);
    }

    // Assign_Range
    {
        long arr[12];
        long arr1[24];

        iota(arr, &arr[12], 0);
        iota(arr1, &arr1[24], 64);

        TESTED_NAMESPACE::vector<long> v(arr, &arr[12]);

        v.assign(arr1, &arr1[24]);
    }
    {
        short arr[24];
        short arr1[12];

        iota(arr, &arr[24], 1024);
        iota(arr1, &arr1[12], -567);

        TESTED_NAMESPACE::vector<short> v(arr, &arr[24]);

        v.assign(arr1, &arr1[12]);
    }
    {
        short arr[24];

        iota(arr, &arr[24], 2048);

        TESTED_NAMESPACE::vector<short> v(48, -1);
        TESTED_NAMESPACE::vector<short> v1(arr, &arr[24]);

        v.push_back(34);
        v.assign(v1.begin(), v1.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec data(5);

        vec v(data.begin(), data.end());

        v.push_back(42);

        vec data2(64);
        v.assign(data2.begin(), data2.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec data(64);

        vec v(data.begin(), data.end());

        vec data2(15);
        v.assign(data2.begin(), data2.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v;

        v.assign(it, end);
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(45, 'A');

        v.assign(it, end);
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(3, 'A');

        v.assign(it, end);
    }

    // Assignement

    {
        TESTED_NAMESPACE::vector<double> v(128, -345783);
        TESTED_NAMESPACE::vector<double> v_copy;

        v_copy = v;

        if (v.data() == v_copy.data()) {
            std::cout << "Copy ctor doesn't do a deep copy!.";
        }

        if (!std::equal(v.begin(), v.end(), v_copy.begin())) {
            std::cout << "Copy ctor error..";
        }

        TESTED_NAMESPACE::vector<double> v1;
        TESTED_NAMESPACE::vector<double> v_copy1;

        v_copy1 = v1;

        if (v1.data() != v_copy1.data()) {
            std::cout << "Non-null pointer in vector of size 0.";
        }

        if (!std::equal(v1.begin(), v1.end(), v_copy1.begin())) {
            std::cout << "Copy ctor error...";
        }

        TESTED_NAMESPACE::vector<double> v2(256, -1);
        TESTED_NAMESPACE::vector<double> v_copy2(255, 56);

        v_copy2.push_back(1);
        v_copy2 = v2;

        if (!std::equal(v2.begin(), v2.end(), v_copy2.begin())) {
            std::cout << "Copy ctor error....";
        }

        TESTED_NAMESPACE::vector<double> v3(64);
        TESTED_NAMESPACE::vector<double> v_copy3(128, -1234);

        v_copy3 = v3;
        TESTED_NAMESPACE::vector<double>& x = v_copy3;

        if (!std::equal(v3.begin(), v3.end(), v_copy3.begin())) {
            std::cout << "Copy ctor error.....";
        }

        v_copy3 = x;

        if (!std::equal(v3.begin(), v3.end(), v_copy3.begin())) {
            std::cout << "Copy ctor error.....";
        }
    }
    {
        TESTED_NAMESPACE::vector<int> v1(64);
        TESTED_NAMESPACE::vector<int> v2(5);

        v2 = v1;
    }
    {
        TESTED_NAMESPACE::vector<int> v1(64);
        TESTED_NAMESPACE::vector<int> v2(5);

        v1 = v2;

        TESTED_NAMESPACE::vector<int>& x = v1;

        v1 = x;
    }

    // CTOR

    // Default
    { TESTED_NAMESPACE::vector<int> v; }
    // Allocator ctor
    {
        std::allocator<double> alloc;
        TESTED_NAMESPACE::vector<double> v(alloc);
    }

    // CTOR COPY

    {
        TESTED_NAMESPACE::vector<double> v(128, -345783);
        TESTED_NAMESPACE::vector<double> v_copy(v);

        if (v.data() == v_copy.data()) {
            std::cout << "Copy ctor doesn't do a deep copy!";
        }

        if (!std::equal(v.begin(), v.end(), v_copy.begin())) {
            std::cout << "Copy ctor error";
        }

        TESTED_NAMESPACE::vector<double> v1;
        TESTED_NAMESPACE::vector<double> v_copy1(v1);

        if (v1.data() != v_copy1.data()) {
            std::cout << "Non-null pointer in vector of size 0";
        }

        if (!std::equal(v1.begin(), v1.end(), v_copy1.begin())) {
            std::cout << "Copy ctor error.";
        }
    }
    {
        TESTED_NAMESPACE::vector<int> v1(512);
        TESTED_NAMESPACE::vector<int> v2(v1);
    }

    // CTOR RANGE

    {
        float arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        TESTED_NAMESPACE::vector<float> v(arr, &arr[10]);

        if (!std::equal(arr, &arr[10], v.begin())) {
            std::cout << "Iterator ctor error";
        }

        TESTED_NAMESPACE::vector<int> v1(arr, arr);

        if (!std::equal(v1.begin(), v1.end(), arr)) {
            std::cout << "Iterator ctor error.";
        }

        TESTED_NAMESPACE::vector<float> v2(v.begin(), v.end());

        if (!std::equal(v2.begin(), v2.end(), v.begin())) {
            std::cout << "Iterator ctor error..";
        }

        std::string str = "Hello World!";
        TESTED_NAMESPACE::vector<char> v3(str.begin(), str.end());

        if (!std::equal(str.begin(), str.end(), v3.begin())) {
            std::cout << "Iterator ctor error...";
        }
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec data(64);
        vec v(data.begin(), data.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(it, end);
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("");
        std::istreambuf_iterator<char> it(str), end;
        vec v(it, end);
    }

    // CTOR SIZE

    {
        TESTED_NAMESPACE::vector<int> v(64);

        TESTED_NAMESPACE::vector<int> v1(10, 32);
        int arr[10] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };

        if (!std::equal(arr, &arr[10], v1.begin())) {
            std::cout << "Size ctor error";
        }

        TESTED_NAMESPACE::vector<int> v2(0, 1234);

        try {
            TESTED_NAMESPACE::vector<big_struct>
            v3(TESTED_NAMESPACE::vector<big_struct>().max_size() + 1);
        } catch (std::length_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    {
        typedef TESTED_NAMESPACE::vector<long> vec;

        vec v(64);

        vec v1(4);

        v1 = v;
    }
    {
        typedef TESTED_NAMESPACE::vector<long> vec;

        vec v(4);

        vec v1(64);

        v1 = v;
    }
    { TESTED_NAMESPACE::vector<abc> v(100); }
}*/

/*int main(void) {

    {
        typedef TESTED_NAMESPACE::vector<int>::iterator iter;

        TESTED_NAMESPACE::vector<int> v;

        iter it = v.insert(v.begin(), 64);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        v.insert(v.begin(), 34);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        v.insert(v.begin(), 21);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        v.insert(v.begin(), 6);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        it = v.insert(v.begin(), 45);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;
    }
    {
        typedef TESTED_NAMESPACE::vector<int>::iterator iter;

        TESTED_NAMESPACE::vector<int> v;

        iter it = v.insert(v.end(), 64);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        it = v.insert(v.end(), 63);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        it = v.insert(v.end(), 62);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;
    }
    {
        typedef TESTED_NAMESPACE::vector<long>::iterator iter;

        TESTED_NAMESPACE::vector<long> v(128, -5);

        iter it = v.insert(v.end(), 64);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        it = v.insert(v.end(), -64);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v;

        v.insert(v.begin(), 42);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v;

        v.insert(v.end(), 42);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v(64);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        v.push_back(42);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;

        v.insert(v.end(), 69);
        std::cout << "VEC: " << v << std::endl;
        std::cout << "VEC size    : " << v.size() << std::endl;
        std::cout << "VEC capacity: " << v.capacity() << std::endl;
        std::cout << std::endl;
    }

    {
        typedef TESTED_NAMESPACE::vector<int>::iterator iter;

        TESTED_NAMESPACE::vector<int> v;

        iter it = v.insert(v.begin(), 64);

        v.insert(v.begin(), 34);
        v.insert(v.begin(), 21);
        v.insert(v.begin(), 6);
        it = v.insert(v.begin(), 45);
    }
    {
        typedef TESTED_NAMESPACE::vector<int>::iterator iter;

        TESTED_NAMESPACE::vector<int> v;

        iter it = v.insert(v.end(), 64);

        it = v.insert(v.end(), 63);

        it = v.insert(v.end(), 62);
    }

    {
        typedef TESTED_NAMESPACE::vector<long>::iterator iter;

        TESTED_NAMESPACE::vector<long> v(128, -5);

        iter it = v.insert(v.end(), 64);

        it = v.insert(v.end(), -64);
    }

    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v;

        v.insert(v.begin(), 42);
        std::cout << "===== STEP 1 =====" << std::endl;
    }

    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v;

        v.insert(v.end(), 42);
        std::cout << "===== STEP 2 =====" << std::endl;
    }

    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v(64);
        std::cout << "===== STEP 3 =====" << std::endl;

        v.push_back(42);
        std::cout << "===== STEP 4 =====" << std::endl;

        v.insert(v.end(), 69);
        std::cout << "===== STEP 5 =====" << std::endl;
    }

    {
        typedef TESTED_NAMESPACE::vector<abc> vec;

        vec v;

        v.insert(v.begin(), v.begin(), v.begin());

        v.insert(v.begin(), v.begin(), v.end());

        v.insert(v.end(), v.end(), v.end());

        abc a(1234, -9786523495);
        v.insert(v.begin(), a);

        abc a1(7643, -3453);
        vec v1(5178, a1);
        v.insert(v.begin(), v1.begin(), v1.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        std::list<abc> li(63);
        v.insert(v.end(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        std::list<abc> li(63);
        v.insert(v.begin(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        std::list<abc> li(64);
        v.insert(v.end(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        std::list<abc> li(64);
        v.insert(v.begin(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v;

        v.insert(v.begin(), v.begin(), v.begin());

        v.insert(v.begin(), v.begin(), v.end());

        v.insert(v.end(), v.end(), v.end());

        v.insert(v.begin(), 42);

        vec v1(5178, 42);
        v.insert(v.begin(), v1.begin(), v1.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v(64);

        v.insert(v.begin() + 7, 42);

        std::list<int> li(63);
        v.insert(v.end(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v(64);

        v.insert(v.begin() + 7, 42);

        std::list<int> li(63);
        v.insert(v.begin(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v(64);
        v.insert(v.begin() + 7, 42);

        std::list<int> li(64);
        v.insert(v.end(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<int> vec;

        vec v(64);

        v.insert(v.begin() + 7, 42);

        std::list<int> li(64);
        v.insert(v.begin(), li.begin(), li.end());
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v;

        v.insert(v.begin(), it, end);
    }
    {
        typedef TESTED_NAMESPACE::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(45, 'A');

        v.insert(v.begin() + 20, it, end);
    }
    {
        typedef ft::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v(3, 'A');

        v.insert(v.end(), it, end);
    }
}*/
