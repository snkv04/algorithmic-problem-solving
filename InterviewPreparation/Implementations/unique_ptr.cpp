#include <iostream>
#include "assert.h"
#include "point.h"

namespace custom {
    // TODO: add custom deleter as a template parameter,
    // so we can use its operator() instead of `delete`,
    // which is useful if, e.g., the pointer is of type FILE*
    // TODO: add a specialization for unique_ptrs to arrays (e.g., unique_ptr<int[]>)
    template <typename T>
    class unique_ptr {
        T *ptr;

    public:
        unique_ptr() noexcept : ptr(nullptr) {}

        // made explicit to avoid, e.g., accidentally casting raw ptr to unique_ptr
        // in a call to a function, which would unintentionally delete at end of function
        explicit unique_ptr(T *ptr) noexcept : ptr(ptr) {}

        ~unique_ptr() {
            if (ptr) delete ptr;
        }

        unique_ptr(const unique_ptr& other) = delete;
        unique_ptr& operator=(const unique_ptr& other) = delete;

        unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
            other.release();
        }

        // recall that in classes, all functions can access all others,
        // regardless of order of declaration or access specifier.
        unique_ptr& operator=(unique_ptr&& other) noexcept {
            if (this != &other) {
                reset(other.release());
            }
            return *this;
        }

        T& operator*() const {
            return *ptr;
        }

        // special case for an operator: after returning something from operator->(),
        // the "->" is applied AGAIN to the resulting return value,
        // which is useful here because we want to do "->" on the actual pointer.
        T* operator->() const {
            return ptr;
        }

        // ctors, dtors, and conversion functions are the only functions
        // without return types.
        operator bool() const noexcept {
            return ptr != nullptr;
        }

        // always try to add in the `const` and `noexcept` modifiers, if applicable,
        // because they can enable safer and faster code.
        T* get() const noexcept {
            return ptr;
        }

        T* release() noexcept {
            // gives up ownership of the ptr
            T* result = ptr;
            ptr = nullptr;

            // returns the now-released address
            return result;
        }

        // remember, noexcept just means that no exception object will arise,
        // not that undefined behavior will not arise,
        // so it's safe to add here even though a double-free (from bad code) can cause UB.
        void reset(T *new_ptr) noexcept {
            if (ptr != new_ptr) {
                if (ptr) delete ptr;
                ptr = new_ptr;
            }
        }

        void reset() noexcept {
            reset(nullptr);
        }

        void swap(unique_ptr &other) noexcept {
            std::swap(ptr, other.ptr);
        }
    };

    template <typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

int main() {
    custom::unique_ptr<Point> ptr = custom::make_unique<Point>(1, 2);
    std::cout << "before moving, ptr.get() = " << ptr.get() << std::endl;
    custom::unique_ptr<Point> ptr2 = std::move(ptr);
    std::cout << "after moving, ptr.get() = " << ptr.get() << " and ptr2.get() = " << ptr2.get() << std::endl;

    custom::unique_ptr<Point> ptr3 = custom::make_unique<Point>(4, 8);
    std::cout << "before swapping, ptr2.get() = " << ptr2.get() << " and ptr3.get() = " << ptr3.get() << std::endl;
    ptr2.swap(ptr3);
    std::cout << "after swapping, ptr2.get() = " << ptr2.get() << " and ptr3.get() = " << ptr3.get() << std::endl;

    assert(sizeof(ptr2) == sizeof(ptr2.get()));
    std::cout << "assertion passed!" << std::endl;

    return 0;
}
