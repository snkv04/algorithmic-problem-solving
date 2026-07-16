#include <iostream>

class Counter {
    unsigned int count;

public:
    // unlike member variables, static variables require both a declaration and definition.
    // if "static ___ const" or "static ___ constexpr", can define it here.
    // else, must define it outside.
    static unsigned int global_count;

    Counter() : count(0) {}

    void increment() {
        this->count += 1;  // think of "this" as an implicit first argument to member functions, like "self" in Python
    }

    static void increment_global() {
        // this->count += 1;  // there does not exist an implicit "this" pointer in static functions
        global_count += 1;
    }

    void display() const {
        // this->count += 1;  // cannot use "this" to modify member variables in const functions
        // global_count += 1;  // CAN modify static variables in const functions, if you want to
        std::cout << "count = " << count << ", global_count = " << global_count << std::endl;
    }
};

unsigned int Counter::global_count = 0;  // without this, there will be a linker error, because declaration but no definition

int main() {
    Counter counter;
    counter.increment();
    counter.increment_global();
    counter.display();

    return 0;
}
