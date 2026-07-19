#include <iostream>
#include <array>

template <typename T>
struct Point {
    T x, y;

    // the only reason this default constructor even compiles is that
    // we don't force a template instantiation like `Point<std::string> point;`.
    // basically, if a template can have an issue when instantiated a specific way,
    // then there are no issues at all until it's actually instantiated with those params.
    Point() : x(17), y(0.23) {}
    
    Point (T x, T y) : x(x), y(y) {}
};

template <typename T1, typename T2>
class Printer {
public:
    void print(const T1 &obj1, const T2 &obj2) {
        std::cout << "non-specialized: (first=" << obj1 << ", second=" << obj2 << ")\n";
    }
};

template <typename T>
class Printer<T, std::string> {  // this line is where the specialization happens
public:
    void print(const T &obj, const std::string &str) {
        std::cout << "partially-specialized: (first=" << obj << ", second=\"" << str << "\")\n";
    }
};

template <>
class Printer<std::string, std::string> {
public:
    void print(const std::string &str1, const std::string &str2) {
        std::cout << "fully-specialized: (first=\"" << str1 << "\", second=\"" << str2 << "\")\n";
    }
};

template <typename T, size_t N>
void print_arr(std::array<T, N> &arr) {
    std::cout << "printing arbitrary array: ";
    for (size_t index = 0; index < N; ++index) {
        std::cout << arr[index] << " \n"[index == N - 1];
    }
}

// partial specialization is not allowed for function templates
// template <typename T>
// void print_arr<T, 5>(std::array<T, 5> &arr) {
//     std::cout << "printing arbitrarily-typed, length-5 array: ";
//     for (size_t index = 0; index < 5; ++index) {
//         std::cout << arr[index] << " \n"[index == 4];
//     }
// }

template <>
void print_arr<int, 5>(std::array<int, 5> &arr) {
    std::cout << "printing length-5 int array: ";
    for (size_t index = 0; index < 5; ++index) {
        std::cout << arr[index] << " \n"[index == 4];
    }
}

int main() {
    // regular class template instantiation.
    // each of these generates a literal new block of assembly code
    // (lazily, though, so only for the constructors/functions that are used),
    // assuming no optimizations (e.g., "-O2") are applied.
    Point<int> p_int(1, 2);
    Point<double> p_double(1, 2);
    Point<std::string> point(std::string("abc"), std::string("def"));

    // class template specialization.
    Printer<int, int> printer;
    Printer<int, std::string> printer2;
    Printer<std::string, std::string> printer3;
    printer.print(1, 2);
    printer2.print(1, "b");
    printer3.print("a", "b");
    std::cout << '\n';

    // function template specialization.
    std::array<double, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<double, 5> arr2 = {0, 1, 2, 3.5, 4.0};
    std::array<int, 5> arr3 = {0, 1, 2, 3, 4};
    print_arr(arr);
    print_arr(arr2);
    print_arr(arr3);

    return 0;
}
