#include <iostream>

namespace custom {
    // this can all be optimized by using malloc(), placement new, manually calling destructors, and free(),
    // so that we avoid default-constructing elements with indices in the interval [num_elems, capacity)
    // and so that emplace_back really does emplace (instead of making a temporary then moving),
    // but refactoring it is for another time
    template <typename T>
    class vector {
        size_t num_elems, capacity;
        T *buffer;

    public:
        vector() : num_elems(0), capacity(0), buffer(nullptr) {}

        vector(size_t initial_capacity) : num_elems(0), capacity(initial_capacity), buffer(new T[capacity]) {}

        vector(const vector& other)
            : num_elems(other.num_elems), capacity(other.capacity), buffer(new T[capacity]) {
                
            std::copy(other.buffer, other.buffer + num_elems, buffer);
        }

        vector& operator=(const vector& other) {
            if (this != &other) {
                // exception-safe; if allocation or copying throws exception, existing pointer will remain intact
                T *new_buffer = new T[other.capacity];
                std::copy(other.buffer, other.buffer + other.num_elems, new_buffer);
                num_elems = other.num_elems;
                capacity = other.capacity;

                delete[] buffer;
                buffer = new_buffer;
            }
            return *this;
        }

        vector(vector&& other) noexcept : num_elems(other.num_elems), capacity(other.capacity), buffer(other.buffer) {
            other.num_elems = 0;
            other.capacity = 0;
            other.buffer = nullptr;
        }

        vector& operator=(vector&& other) noexcept {
            if (this != &other) {
                num_elems = other.num_elems;
                capacity = other.capacity;
                delete[] buffer;
                buffer = other.buffer;

                other.num_elems = 0;
                other.capacity = 0;
                other.buffer = nullptr;
            }
            return *this;
        }

        ~vector() {
            delete[] buffer;
            buffer = nullptr;
            num_elems = 0;
            capacity = 0;
        }

        // operator[] for regular vectors and non-const references to vectors
        T& operator[](size_t index) {
            if (index >= num_elems) {
                throw std::runtime_error("Index out of bounds: " + std::to_string(index));
            }
            return buffer[index];
        }

        // operator[] for const references to vectors.
        // const-correctness just makes sure that things marked const are truly not modifiable.
        // this function maintains const-correctness (making it, for example, usable on const references) by:
        // (1) making the function const, so no instance variables are modified
        // (2) returning a const reference, so the instance cannot be modified through the return value
        const T& operator[](size_t index) const {
            if (index >= num_elems) {
                throw std::runtime_error("Index out of bounds: " + std::to_string(index));
            }
            return buffer[index];
        }

        size_t size() const {
            return num_elems;
        }

        bool empty() const {
            return !num_elems;
        }

        size_t get_capacity() const {
            return capacity;
        }

        void reserve(size_t new_capacity) {
            // if we already have enough capacity, skip the whole logic
            if (new_capacity <= capacity) return;

            // gets a new pointer with the new capacity
            T *new_buffer = new T[new_capacity];

            // copies over all the data to the new pointer
            std::copy(buffer, buffer + num_elems, new_buffer);

            // bookkeeping
            delete[] buffer;
            buffer = new_buffer;
            capacity = new_capacity;
        }

        void resize(size_t new_size) {
            // makes sure the capacity is sufficiently high
            if (new_size > capacity) {
                reserve(new_size);
            }

            // moves end of vector to new spot in buffer,
            // which is fine since everything's default-constructed
            num_elems = new_size;
        }

        // push_back that copies the input
        void push_back(const T& object) {
            // makes new buffer and copies everything over, if vector is full
            if (num_elems == capacity) {
                reserve(capacity ? 2 * capacity : 1);
            }

            // copies object onto vector
            buffer[num_elems++] = object;
        }

        // push_back that moves the input
        void push_back(T&& object) {
            // makes new buffer and copies everything over, if vector is full
            if (num_elems == capacity) {
                reserve(capacity ? 2 * capacity : 1);
            }

            // moves object onto vector
            // need to make sure to explicitly cast back to rvalue with std::move()!
            buffer[num_elems++] = std::move(object);
        }

        // the "..." means that instead of one template parameter, we have a "pack" of them, collectively called Args.
        // (this makes the template (function) a "variadic" template (function).)
        // the "&&", when used after a template parameter deduced right there in that template,
        // is a forwarding reference, meaning it binds to either lvalues or rvalues.
        // (this enables "perfect forwarding" through std::forward<Args>(), which recovers an arg's category.
        // without std::forward<Args>(), every arg is always treated as an lvalue.)
        // both of these things can be used without the other.
        template <typename... Args>
        T& emplace_back(Args&&... args) {
            // makes new buffer and copies everything over, if vector is full
            if (num_elems == capacity) {
                reserve(capacity ? 2 * capacity : 1);
            }

            // constructs object on vector (not really, since we're not using placement new)
            buffer[num_elems++] = T(std::forward<Args>(args)...);

            // returns reference to constructed object
            return buffer[num_elems - 1];
        }

        void pop_back() {
            // checks edge case
            if (empty()) {
                throw std::runtime_error("Called pop_back() with no elements on vector");
            }

            // simply decrements num_elems pointer.
            // don't need to call destructor, because that will be done with delete[] when the vector's destructor runs.
            // can optionally do a reallocation to shrink capacity if num_elems <= 1/4 * capacity.
            --num_elems;
        }
    };
}

struct Point {
    int x, y;

    Point() {}

    Point(int x, int y) : x(x), y(y) {}

    Point(const Point& other) : x(other.x), y(other.y) {}

    Point& operator=(const Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Point(Point&& other) noexcept : x(other.x), y(other.y) {
        other.x = other.y = 0;
    }

    Point& operator=(Point&& other) noexcept {
        if (this != &other) {
            x = other.x;
            y = other.y;
            other.x = other.y = 0;
        }
        return *this;
    }

    ~Point() = default;

    friend std::ostream& operator<<(std::ostream &os, const Point &point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

int main() {
    custom::vector<Point> vec(10);
    std::cout << "vec.size() = " << vec.size() << ", vec.get_capacity() = " << vec.get_capacity() << std::endl;
    for (int i = 0; i < 10; ++i) {
        if (i % 2) vec.emplace_back(2 * i, 2 * i + 1);
        else vec.push_back(Point(2 * i, 2 * i + 1));
    }
    std::cout << "vec.size() = " << vec.size() << ", vec.get_capacity() = " << vec.get_capacity() << std::endl;
    vec.push_back(Point(20, 21));  // allocates new block, and copies over data
    std::cout << "vec.size() = " << vec.size() << ", vec.get_capacity() = " << vec.get_capacity() << std::endl;

    custom::vector<Point> &ref = vec;
    const custom::vector<Point> &const_ref = vec;
    ref.pop_back();
    std::cout << "vec.size() = " << vec.size() << ", vec.get_capacity() = " << vec.get_capacity() << std::endl;
    std::cout << "ref[9] = " << ref[9] << std::endl;
    std::cout << "const_ref[9] = " << const_ref[9] << std::endl;

    return 0;
}
