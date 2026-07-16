#include <iostream>
#include <bits/stdc++.h>

class ManuallyManagedBuffer {
    size_t data_length;
    int *data;

public:
    ManuallyManagedBuffer() : data_length(0), data(nullptr) {}

    // constructor
    // initializes size and allocates memory
    ManuallyManagedBuffer(size_t size) : data_length(size), data(new int[data_length]) {}

    // destructor
    ~ManuallyManagedBuffer() {
        // sets size to 0
        data_length = 0;

        // deallocates memory, then updates pointer to nullptr
        delete[] data;
        data = nullptr;
    }

    // copy constructor
    ManuallyManagedBuffer(const ManuallyManagedBuffer &other)
        // copies the size and allocates the memory
        : data_length(other.data_length), data(new int[data_length]) {
        
        // copies the data into the allocated memory
        std::copy(other.data, other.data + data_length, data);
    }

    // copy assignment operator
    // technically not exception safe, because it deallocates before doing a potentially risky allocation...
    ManuallyManagedBuffer& operator=(const ManuallyManagedBuffer &other) {
        if (this != &other) {
            // deallocates existing memory
            delete[] data;  // if nullptr, then the C++ standard guarantees a no-op

            // initializes new size, allocates new memory, and fills in data
            data_length = other.data_length;
            data = new int[data_length];
            std::copy(other.data, other.data + data_length, data);
        }
        return *this;
    }

    // move constructor
    // we use `noexcept` because it can't throw, so vector reallocations on resize will use this,
    // without fail, instead of copy constructor
    ManuallyManagedBuffer(ManuallyManagedBuffer &&other) noexcept
        // initialize size, and initialize pointer to other pointer
        : data_length(other.data_length), data(other.data) {

        // reset size and pointer of other object
        other.data_length = 0;
        other.data = nullptr;
    }

    // move assignment operator
    ManuallyManagedBuffer& operator=(ManuallyManagedBuffer &&other) noexcept {
        if (this != &other) {
            // deallocates existing memory
            delete[] data;

            // initialize size and pointer to that of other
            data_length = other.data_length;
            data = other.data;

            // reset size and pointer of other object
            other.data_length = 0;
            other.data = nullptr;
        }
        return *this;
    }

    int& operator[](size_t idx) {
        if (idx >= data_length) {  // don't have to check if < 0 because size_t is always >= 0
            throw std::runtime_error("Invalid index: " + std::to_string(idx));
        }

        return data[idx];
    }

    // const overload, so that const instances can call operator[]
    const int& operator[](size_t idx) const {
        if (idx >= data_length) {
            throw std::runtime_error("Invalid index: " + std::to_string(idx));
        }

        return data[idx];
    }
};

int main() {
    // barebones example of using non-default constructor
    int n = 6;
    ManuallyManagedBuffer my_buffer(n);
    std::cout << "my_buffer = ";
    for (int i = 0; i < n; ++i) {
        std::cout << my_buffer[i] << " \n"[i == n - 1];
    }

    // demonstrates necessity of destructor.
    // without the destructor, the memory leaks are so bad that the program actually terminates.
    // with it, the program is simply slow (due to the large allocs/deallocs), but is functional.
    for (int i = 0; i < (1 << 20); ++i) {
        ManuallyManagedBuffer new_buffer(1 << 30);
    }

    // demonstrates necessity of copy constructor/assignment operator.
    // without it, we have a double free, because the two Buffer objects point to the same address.
    // with it, the data gets deep-copied, and there are no double-frees.
    for (int i = 0; i < 10; ++i) {
        ManuallyManagedBuffer new_buffer = my_buffer;  // move constructor called
    }
    for (int i = 0; i < 10; ++i) {
        ManuallyManagedBuffer new_buffer;
        new_buffer = my_buffer;  // move assignment operator called
    }

    // demonstrates necessity of move constructor/assignment operator.
    // (the "necessity" is really just avoiding a performance degradation.
    // to see the performance benefit, comment out the move ctor/operator= and compare times after/before doing that.
    // it's approximately 300 ms -> 45 ms for each function.)
    // without it, the compiler falls back to copying.
    // with it, the data gets moved (stolen), which is obviously much faster.
    {
        auto before = std::chrono::steady_clock::now();
        for (int i = 0; i < (1 << 20); ++i) {
            ManuallyManagedBuffer a(1 << 10);
            ManuallyManagedBuffer b = std::move(a);  // explicit move ctor call
        }
        auto after = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
        std::cout << "[move ctor] time elapsed = " << diff.count() << " ms\n";
    }
    {
        auto before = std::chrono::steady_clock::now();
        for (int i = 0; i < (1 << 20); ++i) {
            ManuallyManagedBuffer a(1 << 10), b;
            b = std::move(a);  // explicit move assignment operator call
        }
        auto after = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
        std::cout << "[move operator=] time elapsed = " << diff.count() << " ms\n";
    }

    return 0;
}
