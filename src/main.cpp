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

struct abc {
    abc()
        : data(4),
          num(1000)
    {
    }

    abc(int d, long n)
        : data(d),
          num(n)
    {
    }

    int data;
    long num;
};


int main(void) {

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

    //* INSERT
    {
        typedef ft::vector<int>::iterator iter;

        ft::vector<int> v;

        iter it = v.insert(v.begin(), 64);


        v.insert(v.begin(), 34);
        v.insert(v.begin(), 21);
        v.insert(v.begin(), 6);
        it = v.insert(v.begin(), 45);

    }
    {
        typedef ft::vector<int>::iterator iter;

        ft::vector<int> v;

        iter it = v.insert(v.end(), 64);


        it = v.insert(v.end(), 63);


        it = v.insert(v.end(), 62);

    }
    
    {
        typedef ft::vector<long>::iterator iter;

        ft::vector<long> v(128, -5);


        iter it = v.insert(v.end(), 64);


        it = v.insert(v.end(), -64);

    }
    
    {
        typedef ft::vector<int> vec;

        vec v;


        v.insert(v.begin(), 42);
        std::cout << "===== STEP 1 =====" << std::endl;
    }
    
    {
        typedef ft::vector<int> vec;

        vec v;


        v.insert(v.end(), 42);
        std::cout << "===== STEP 2 =====" << std::endl;
    }
    
    {
        typedef ft::vector<int> vec;

        vec v(64);
        std::cout << "===== STEP 3 =====" << std::endl;



        v.push_back(42);
        std::cout << "===== STEP 4 =====" << std::endl;

        v.insert(v.end(), 69);
        std::cout << "===== STEP 5 =====" << std::endl;
    }


    //* INSERT RANGE

    {
        typedef ft::vector<abc> vec;

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
        typedef ft::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);


        std::list<abc> li(63);
        v.insert(v.end(), li.begin(), li.end());

    }
    {
        typedef ft::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);


        std::list<abc> li(63);
        v.insert(v.begin(), li.begin(), li.end());

    }
    {
        typedef ft::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);


        std::list<abc> li(64);
        v.insert(v.end(), li.begin(), li.end());

    }
    {
        typedef ft::vector<abc> vec;

        vec v(64);

        abc a(1234, -9786523495);
        v.insert(v.begin() + 7, a);

        std::list<abc> li(64);
        v.insert(v.begin(), li.begin(), li.end());

    }
    {
        typedef ft::vector<int> vec;

        vec v;

        v.insert(v.begin(), v.begin(), v.begin());


        v.insert(v.begin(), v.begin(), v.end());


        v.insert(v.end(), v.end(), v.end());


        v.insert(v.begin(), 42);


        vec v1(5178, 42);
        v.insert(v.begin(), v1.begin(), v1.end());

    }
    {
        typedef ft::vector<int> vec;

        vec v(64);

        v.insert(v.begin() + 7, 42);


        std::list<int> li(63);
        v.insert(v.end(), li.begin(), li.end());

    }
    {
        typedef ft::vector<int> vec;

        vec v(64);

        v.insert(v.begin() + 7, 42);


        std::list<int> li(63);
        v.insert(v.begin(), li.begin(), li.end());
    }
    {
        typedef ft::vector<int> vec;

        vec v(64);
        v.insert(v.begin() + 7, 42);


        std::list<int > li(64);
        v.insert(v.end(), li.begin(), li.end());

    }
    {
        typedef ft::vector<int> vec;

        vec v(64);

        v.insert(v.begin() + 7, 42);


        std::list<int> li(64);
        v.insert(v.begin(), li.begin(), li.end());

    }
    {
        typedef ft::vector<char> vec;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        vec v;


        v.insert(v.begin(), it, end);
    }
    {
        typedef ft::vector<char> vec;

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
}
