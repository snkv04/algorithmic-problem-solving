#include <iostream>
#include <cassert>

namespace custom {
    struct ControlBlock {
        size_t strong_refcnt{1};  // same as `size_t strong_refcnt = 1;`; gets run if variable not in initializer list
        size_t weak_refcnt{0};
    };

    template <typename T>
    class weak_ptr;

    // TODO: make the reference counting thread-safe using atomics
    // (though the data itself still isn't intended to be thread-safe, even in the STL)
    // TODO: implement make_shared() (which probably won't work with the
    // current new/delete usage, since we'd require placement new)
    template <typename T>
    class shared_ptr {
        T *ptr;
        ControlBlock *block_ptr;

        void drop_reference() noexcept {
            // if we're not pointing to anything, just do a no-op
            if (!ptr) return;

            // deallocates data if nothing's pointing to it
            if (block_ptr->strong_refcnt == 1) {
                delete ptr;
            }
            ptr = nullptr;

            // deallocates control block if nothing's pointing to it
            block_ptr->strong_refcnt -= 1;
            if (block_ptr->strong_refcnt == 0 && block_ptr->weak_refcnt == 0) {
                delete block_ptr;
            }
            block_ptr = nullptr;
        }

    public:
        // don't need a control block if pointing to nothing
        shared_ptr() : ptr(nullptr), block_ptr(nullptr) {}

        // must check if pointing to nothing before making control block!
        explicit shared_ptr(T *raw) :
            ptr(raw),
            block_ptr(raw == nullptr ? nullptr : new ControlBlock()) {}

        // alternative constructor, used in weak_ptr::lock()
        explicit shared_ptr(T *raw, ControlBlock *block) noexcept : ptr(raw), block_ptr(block) {
            if (block_ptr) {
                block_ptr->strong_refcnt += 1;
            }
        }

        // should not be able to construct shared_ptr from weak_ptr;
        // weak_ptrs are just the observers, not the owners, of data.
        // weak_ptr::lock() is the mechanism for that.
        shared_ptr(const weak_ptr<T> &other) = delete;

        shared_ptr(const shared_ptr &other) noexcept : ptr(other.ptr), block_ptr(other.block_ptr) {
            // increments strong reference count
            if (block_ptr) {
                block_ptr->strong_refcnt += 1;
            }
        }

        shared_ptr& operator=(const shared_ptr &other) noexcept {
            if (this != &other) {  // don't need to do ANYTHING if we're self-assigning
                // detaches from existing data
                drop_reference();

                // attaches to new data
                ptr = other.ptr;
                block_ptr = other.block_ptr;

                // increments strong reference count
                if (block_ptr) {
                    block_ptr->strong_refcnt += 1;
                }
            }
            return *this;
        }

        shared_ptr(shared_ptr &&other) noexcept : ptr(other.ptr), block_ptr(other.block_ptr) {
            other.ptr = nullptr;
            other.block_ptr = nullptr;
        }

        shared_ptr& operator=(shared_ptr &&other) noexcept {
            if (this != &other) {
                // detaches from existing data
                drop_reference();

                // steals everything
                ptr = other.ptr;
                block_ptr = other.block_ptr;

                // erases everything from other
                other.ptr = nullptr;
                other.block_ptr = nullptr;
            }
            return *this;
        }

        ~shared_ptr() {
            drop_reference();
        }

        operator bool() const noexcept {
            return ptr != nullptr;
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        T* get() const noexcept {
            return ptr;
        }

        T* release() = delete;  // no unique ownership; auto-release when all references are dropped

        // we must assume that this raw pointer has not been used anywhere
        // in another smart pointer; if it has, that's bad code,
        // because it breaks the contract the STL assumes we're making
        void reset(T *new_ptr) {
            if (ptr != new_ptr) {
                drop_reference();
                if (new_ptr) {
                    ptr = new_ptr;
                    block_ptr = new ControlBlock();
                }
            }
        }

        // can be noexcept, because the other reset() won't allocate if input is nullptr
        void reset() noexcept {
            reset(nullptr);
        }

        size_t use_count() {
            return block_ptr ? block_ptr->strong_refcnt : 0;
        }

        void swap(shared_ptr &other) noexcept {
            std::swap(ptr, other.ptr);
            std::swap(block_ptr, other.block_ptr);
        }

        friend class weak_ptr<T>;  // just so that weak_ptr can access instance variables of shared_ptr
    };

    template <typename T>
    class weak_ptr {
        T *ptr;
        ControlBlock *block_ptr;

        void drop_reference() noexcept {
            // if we're not pointing to anything, just do a no-op
            if (!block_ptr) return;

            // no need to worry about deleting the data;
            // losing a weak reference will never be the reason that the data are deleted
            ptr = nullptr;

            // might delete control block if this is the last thing
            // keeping it alive
            block_ptr->weak_refcnt -= 1;
            if (block_ptr->strong_refcnt == 0 && block_ptr->weak_refcnt == 0) {
                delete block_ptr;
            }
            block_ptr = nullptr;
        }

    public:
        weak_ptr() : ptr(nullptr), block_ptr(nullptr) {}

        weak_ptr(const shared_ptr<T> &other) : ptr(other.ptr), block_ptr(other.block_ptr) {
            if (block_ptr) {
                block_ptr->weak_refcnt += 1;
            }
        }

        weak_ptr(const weak_ptr &other) : ptr(other.ptr), block_ptr(other.block_ptr) {
            if (block_ptr) {
                block_ptr->weak_refcnt += 1;
            }
        }

        weak_ptr& operator=(const weak_ptr &other) {
            if (this != &other) {
                drop_reference();

                ptr = other.ptr;
                block_ptr = other.block_ptr;

                if (block_ptr) {
                    block_ptr->weak_refcnt += 1;
                }
            }
            return *this;
        }

        weak_ptr(weak_ptr &&other) noexcept : ptr(other.ptr), block_ptr(other.block_ptr) {
            other.ptr = other.block_ptr = nullptr;
        }

        weak_ptr& operator=(weak_ptr &&other) noexcept {
            if (this != &other) {
                drop_reference();

                ptr = other.ptr;
                block_ptr = other.block_ptr;

                other.ptr = other.block_ptr = nullptr;
            }
            return *this;
        }

        ~weak_ptr() {
            drop_reference();
        }

        operator bool() = delete;  // need to check availability with lock()

        T& operator*() = delete;  // need to check availability with lock()

        T* operator->() = delete;  // need to check availability with lock()

        T* get() const noexcept = delete;  // need to check availability with lock()

        shared_ptr<T> lock() {
            if (block_ptr && block_ptr->strong_refcnt) {
                return shared_ptr<T>(ptr, block_ptr);
            } else {
                return shared_ptr<T>();
            }
        }

        T* release() = delete;  // no ownership <---> no ability to "give up" the data

        void reset(T *new_ptr) noexcept = delete;  // cannot gain ownership of a raw pointer

        void reset() noexcept {
            drop_reference();
        }

        size_t use_count() {
            return block_ptr ? block_ptr->strong_refcnt : 0;
        }

        void swap(weak_ptr &other) noexcept {
            std::swap(ptr, other.ptr);
            std::swap(block_ptr, other.block_ptr);
        }
    };
}

int main() {
    // moving
    custom::shared_ptr<int> shared(new int(5));
    std::cout << "initially:\n\tshared.use_count() = " << shared.use_count() << '\n';
    custom::shared_ptr<int> shared2 = std::move(shared);
    std::cout << "after moving:\n";
    std::cout << "\tshared.use_count() = " << shared.use_count() << '\n';
    std::cout << "\tshared2.use_count() = " << shared2.use_count() << "\n\n";

    // copying
    {
        custom::shared_ptr<int> shared3 = shared2;
        std::cout << "after copying:\n";
        std::cout << "\tshared2.use_count() = " << shared2.use_count() << '\n';
        std::cout << "\tshared3.use_count() = " << shared3.use_count() << '\n';
    }
    std::cout << "after copy went out of scope:\n\tshared2.use_count() = " << shared2.use_count() << "\n\n";

    // weak copying and locking
    custom::weak_ptr<int> weak = shared2;
    std::cout << "after making weak ptr:\n";
    std::cout << "\tshared2.use_count() = " << shared2.use_count() << '\n';
    std::cout << "\tweak.use_count() = " << weak.use_count() << '\n';
    {
        custom::shared_ptr<int> from_lock = weak.lock();
        std::cout << "after locking weak ptr:\n";
        std::cout << "\tshared2.use_count() = " << shared2.use_count() << '\n';
        std::cout << "\tweak.use_count() = " << weak.use_count() << '\n';
    }
    std::cout << "after lock got destroyed:\n";
    std::cout << "\tshared2.use_count() = " << shared2.use_count() << '\n';
    std::cout << "\tweak.use_count() = " << weak.use_count() << "\n\n";

    // weak ptr with no strong references
    shared2.reset();
    std::cout << "after dropping all strong references:\n";
    std::cout << "\tshared2.use_count() = " << shared2.use_count() << '\n';
    std::cout << "\tweak.use_count() = " << weak.use_count() << '\n';
    weak.reset();
    std::cout << "after dropping weak reference:\n\tweak.use_count() = " << weak.use_count() << "\n\n";

    // checking object size
    assert(sizeof(shared2) == 2 * sizeof(shared2.get()));
    std::cout << "assertion passed!\n";

    return 0;
}
