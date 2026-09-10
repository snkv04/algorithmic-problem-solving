#include <iostream>

// the normal template is the recursive case
template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// the specialization of the template is the base case
template <>
struct Factorial<0> {
    static constexpr int value = 1;
};

template <int A, int B>
struct GCD {
    static constexpr int value = GCD<B, A % B>::value;
};

template <int A>
struct GCD<A, 0> {
    static constexpr int value = A;
};

void recursion_examples() {
    // computes factorial.
    // all template structs in [0, N] are instantiated, increasing executable's size.
    std::cout << "Factorial<5>::value = " << Factorial<5>::value << std::endl;
    std::cout << "Factorial<0>::value = " << Factorial<0>::value << std::endl;  // base case
    // std::cout << "Factorial<-1>::value = " << Factorial<-1>::value << std::endl;  // template instantiation has max depth of 1024
    std::cout << std::endl;

    // computes gcd.
    std::cout << "GCD<32, 12>::value = " << GCD<32, 12>::value << std::endl;
    std::cout << "GCD<6, 21>::value = " << GCD<6, 21>::value << std::endl;  // A < B also works
    std::cout << "GCD<5, 0>::value = " << GCD<5, 0>::value << std::endl;  // base case
    std::cout << std::endl;
}

template <typename T>
void print_kind(T obj) {
    // "if constexpr" evaluates the if condition at compile-time,
    // instead of evaluating it once (or more) at runtime.
    // as a result, when instantiating the template,
    // only one branch actually gets placed into the assembly code per instantiation.
    if constexpr (std::is_integral<T>::value) {
        std::cout << obj << " is an integer" << std::endl;
    } else {
        std::cout << obj << " is not an integer" << std::endl;
    }
}

template <typename T, bool Invert>
T process_value(T obj) {
    if constexpr (Invert) {
        return -1 * obj;
    } else {
        return obj;
    }
}

void branching_examples() {
    // branches based on checking a type at compile-time.
    print_kind(7);
    long long ll_value = 8;
    print_kind(ll_value);
    size_t st_value = 9;
    print_kind(st_value);
    print_kind(10.0);
    float float_value = 11.5;
    print_kind(float_value);
    std::cout << std::endl;

    // branches based on checking a value at compile-time.
    std::cout << "process_value<int, true>(7) = " << process_value<int, true>(7) << std::endl;
    std::cout << "process_value<int, false>(7) = " << process_value<int, false>(7) << std::endl;
    std::cout << std::endl;
}

// base case is not a template specialization,
// just a template function with a single argument.
template <typename T>
T sum(T head) {
    return head;
}

// recursive case is a variadic template (so it uses a parameter pack).
// very similar logic to iterating over loops in Haskell.
// the "container" is given in the form of arguments,
// so that the compiler can do recursive TMP on it.
template <typename T, typename... Rest>
T sum(T head, Rest... rest) {
    return head + sum(rest...);
}

void variadic_example() {
    std::cout << "sum(1, 2, 3, 4) = " << sum(1, 2, 3, 4) << std::endl;
}

int main() {
    // template metaprogramming lets you compute things at compile-time instead of runtime.
    // the "meta" comes having this functional programming language inside the C++ language.
    // core concept: we replace functions + arguments + return values with
    // template classes + template parameters + static fields.
    // it's mainly used for 3 things:

    // (1) optimizing recursion (or loops expressed as recursion)
    recursion_examples();

    // (2) optimizing if conditions
    branching_examples();

    // (3) optimizing loops that iterate over containers
    variadic_example();

    return 0;
}
