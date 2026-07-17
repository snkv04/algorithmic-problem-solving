#include <bits/stdc++.h>
#include "point.h"

struct Node {
    int value;
    std::vector<std::shared_ptr<Node>> adjacency_list;

    Node() = default;
    
    Node(int value) : value(value) {}
};

struct DLLNode {
    int value;
    std::shared_ptr<DLLNode> next;  // strong forward chain
    std::weak_ptr<DLLNode> prev;  // weak back reference, to avoid cycles

    DLLNode(int value) : value(value) {}
};

std::shared_ptr<DLLNode> build_dll(size_t length) {
    std::shared_ptr<DLLNode> head = std::make_shared<DLLNode>(-1);
    std::shared_ptr<DLLNode> tail = std::make_shared<DLLNode>(-1);
    head->next = tail;
    tail->prev = head;
    assert(head->prev.lock().get() == 0x0000);
    assert(tail->next.get() == 0x0000);

    auto push_back = [&](int value) {
        auto back = tail->prev.lock();
        auto new_node = std::make_shared<DLLNode>(value);
        back->next = new_node; new_node->prev = back;
        tail->prev = new_node; new_node->next = tail;
    };
    for (size_t index = 0; index < length; ++index) {
        push_back(index);
    }
    return head;
}

void traverse(std::shared_ptr<DLLNode> head_sentinel) {
    std::cout << "doubly-linked list:";
    std::shared_ptr<DLLNode> curr = head_sentinel;
    while (curr->next->value != -1) {
        curr = curr->next;
        std::cout << ' ' << curr->value;
    }
    std::cout << "\n";
}

int main() {
    // std::unique_ptr is just an RAII pointer.
    // unique ownership, no copies (only moves), and zero overhead.
    // unique "ownership"? think of ownership as "responsibility for calling `delete`".
    // zero overhead? meaning, size of an instance of std::unique_ptr is same as the ptr itself;
    // the additional functions are all code, not data, so they don't make this statement false.
    {
        // when using constructor:
        // allocation and construction of object happens when making raw pointer.
        // destruction and deallocation happen in destructor of std::unique_ptr.
        Point *raw_ptr = new Point(2, 4);
        std::unique_ptr<Point> ptr(raw_ptr);
        std::cout << "*ptr = " << *ptr << std::endl;

        // when using std::make_unique():
        // allocation and construction of object happen in std::make_unique().
        // again, destruction and deallocation happen in destructor of std::unique_ptr.
        // much safer, because it never exposes you to the raw pointer.
        // for example, that avoids a memory leak in *exception*al circumstances.
        std::unique_ptr<Point> ptr2 = std::make_unique<Point>(8, 16);
        std::cout << "*ptr2 = " << *ptr2 << std::endl;

        // some functionality of the class
        // std::unique_ptr<Point> ptr3 = ptr2;  // compile-time error: copies are not allowed!
        std::unique_ptr<Point> ptr3 = std::move(ptr2);  // moves are fine
        // std::cout << "*ptr2 = " << *ptr2 << std::endl;  // undefined behavior, because was moved
        std::cout << "after moving from ptr2 to ptr3, *ptr3 = " << *ptr3 << " and ptr3->get_x() = " << ptr3->get_x() << std::endl;  // dereferencing
        assert(sizeof(ptr3) == sizeof(ptr3.get()));  // quite literally, zero overhead

        // some functions in the class
        std::cout << "ptr3 = " << ptr3 << std::endl;  // raw address
        std::cout << "ptr3.get() = " << ptr3.get() << std::endl;  // raw address, the idiomatic way
        Point *raw_ptr2 = ptr3.release();  // remove the ptr from the unique_ptr
        std::cout << "after releasing, ptr3.get() = " << ptr3.get() << ", and raw_ptr2 = " << raw_ptr2 << std::endl;
        ptr2.reset(raw_ptr2);  // assign a ptr to the unique_ptr
        std::cout << "after resetting, ptr2.get() = " << ptr2.get() << std::endl;
    }
    std::cout << std::endl;

    // std::shared_ptr
    // non-unique ownership (through copying), but added overhead (through control block).
    // if an object will be pointed to multiple times, use std::shared_ptr.
    {
        // when using constructor, two heap allocations:
        // one for the pointer to the data itself,
        // and one for the control block (strong refcnt + weak refcnt + pointer).
        Point *raw = new Point(32, 64);
        std::shared_ptr<Point> ptr = std::shared_ptr<Point>(raw);
        std::cout << "*ptr = " << *ptr << std::endl;

        // when using std::make_shared(), one heap allocation:
        // control block is right before the data.
        // this benefit is in addition to never exposing the raw ptr, as discussed for unique_ptr.
        std::shared_ptr<Point> ptr2 = std::make_shared<Point>(128, 256);
        std::cout << "*ptr2 = " << *ptr2 << std::endl;

        // basic idea: reference counting.
        // use_count() returns the strong refcount,
        // which is the number of shared_ptrs pointing to the same address.
        std::cout << "ptr2.use_count() = " << ptr2.use_count() << std::endl;
        {
            // refcount only ever really gets updated through either
            // the copy constructor or copy assignment operator.
            std::shared_ptr<Point> ptr3 = ptr2;
            std::cout << "in scope, ptr2.use_count() = " << ptr2.use_count() << std::endl;
            std::cout << "in scope, ptr3.use_count() = " << ptr3.use_count() << std::endl;
        }
        std::cout << "after scope, ptr2.use_count() = " << ptr2.use_count() << std::endl;
        assert(sizeof(ptr2) == 2 * sizeof(ptr2.get()));  // ptr to data + ptr to control block

        // common use case: good for DAG-shaped structures.
        // if there's a cycle, then refcounts will never reach 0,
        // and there'll be a memory leak.
        std::shared_ptr<Node> layer0 = std::make_shared<Node>(00);
        std::shared_ptr<Node> layer1_0 = std::make_shared<Node>(10);
        std::shared_ptr<Node> layer1_1 = std::make_shared<Node>(11);
        std::shared_ptr<Node> layer2 = std::make_shared<Node>(20);
        layer0->adjacency_list.push_back(layer1_0);
        layer0->adjacency_list.push_back(layer1_1);
        layer1_0->adjacency_list.push_back(layer2);
        layer1_1->adjacency_list.push_back(layer2);
        std::cout << "00.use_count() = " << layer0.use_count() << std::endl;
        std::cout << "10.use_count() = " << layer1_0.use_count() << std::endl;
        std::cout << "11.use_count() = " << layer1_1.use_count() << std::endl;
        std::cout << "20.use_count() = " << layer2.use_count() << std::endl;
    }
    std::cout << std::endl;

    // std::weak_ptr
    // just a non-owning pointer that points to a shared_ptr's control block. nothing more.
    {
        // can either copy a shared_ptr or a weak_ptr
        std::shared_ptr<Point> shared = std::make_shared<Point>(512, 1024);
        std::weak_ptr<Point> weak = shared;
        std::weak_ptr<Point> weak2 = weak;
        std::cout << "shared.use_count() = " << shared.use_count() << std::endl;  // weak_ptrs don't count!
        std::cout << "weak.use_count() = " << weak.use_count() << std::endl;

        // can't directly dereference; need to use lock() to obtain a shared_ptr
        // std::cout << "*weak = " << *weak << std::endl;  // operator* is disabled
        // std::cout << "weak->get_x() = " << weak->get_x() << std::endl;  // operator-> is disabled
        std::shared_ptr<Point> as_shared = weak.lock();
        std::cout << "after calling lock(), weak.use_count() = " << weak.use_count() << " and *as_shared = " << *as_shared << std::endl;
        shared.reset(); as_shared.reset();  // drop both references
        as_shared = weak.lock();
        std::cout << "after resetting all shared, weak.use_count() = " << weak.use_count() << " and as_shared.get() = " << as_shared.get() << std::endl;

        // example of avoiding cyclic shared_ptr bug.
        // why not only use weak_ptrs instead of shared_ptrs as classes' instance variables?
        // because then we'd need an in-scope local variable pointing to every single object,
        // which (e.g.) would stop us from holding a full linked list using only its head.
        std::shared_ptr<DLLNode> head_sentinel = build_dll(10);
        traverse(head_sentinel);
    }
}
