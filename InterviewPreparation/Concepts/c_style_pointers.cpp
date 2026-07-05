#include <bits/stdc++.h>
using namespace std;

void modifier_function(const int **ptr, int* new_address) {
    *ptr = new_address;
}

int main() {
    // pointer to stack variable
    // remember, a pointer is just a variable holding an address
    int x = 5;
    int *ptr = &x;
    printf("x = %d\n", x);
    printf("ptr = %p\n", ptr);

    // 4 types of const ========================================
    // can change where it points to + value
    int y = 10, z = 20;
    int *p = &y;
    *p = 15;
    assert(y == 15);
    p = &z;
    assert(*p == 20);

    // can point to new place, but can't update value it's pointing to
    // if const is before the type of the thing being pointed to, then the thing being pointed to is unmodifiable
    y = 10; z = 20;
    // example 1:
    const int *q = &y;
    // *q = 15;  // not allowed!
    q = &z;  // allowed
    assert(*q == 20);
    // example 2:
    int const *q2 = &y;
    // *q = 15;  // not allowed!
    q = &z;
    assert(*q == 20);

    // can't point to new place, but can update values freely
    // if const is before the variable name, then since the variable itself is a pointer to a place,
    // we can't change the place it's pointing to
    y = 10; z = 20;
    int* const r = &y;
    // r = &z;  // not allowed!
    *r = 15;
    assert(y == 15);

    // can't point to a new place or change the value being pointed to
    // don't need any mnemonic; is obvious
    y = 10; z = 20;
    const int* const s = &y;
    // s = &z;  // compile-time error :)
    // *s = 15;  // compile-time error :)

    // alternative way to remember it:
    // - "const" comes after the type that it makes const, with the very first type (the value's type) being the
    // exception, where const can come BEFORE it
    // - e.g., with "const int* const x":
    //     - the second const says that the pointer (*) is const, because it comes after the *
    //     - as for the first const, the expression would be the same as "int const * const", which says that
    //       the value (int) is const, because it comes after the "int"
    // =========================================================

    // pointer to heap variable
    ptr = new int(5);
    printf("ptr to heap = %p\n", ptr);
    printf("value on heap = %d\n", *ptr);
    delete ptr;
    printf("after deletion, ptr to heap = %p\n", ptr);
    // printf("after deletion, value on heap = %d\n", *ptr);  // undefined behavior :)
    ptr = nullptr;
    printf("after null-initialization, ptr = %p\n", ptr);
    assert(ptr == 0x00000000);

    // double pointers
    x = 5;
    // int **ptr2 = &&x;  // doesn't compile; can't take the address of an rvalue ("&x")
    ptr = &x;
    int **ptr2 = &ptr;
    printf("x = %d\n", x);
    printf("ptr = %p\n", ptr);
    printf("ptr2 = %p\n", ptr2);

    // use case of double pointers: modifying a pointer in any way with a function
    // in general, if you want to modify something, you need either a reference to it or a pointer to it,
    // because every function argument is either pass-by-reference or pass-by-value
    x = 5; z = 20;
    const int *ptr3 = &x;
    assert(ptr3 == &x);
    assert(*ptr3 == 5);
    const int** ptr4 = &ptr3;  // can't set "const int**" to address of "int*", must be set to address of "const int*"
    modifier_function(ptr4, &z);
    assert(ptr3 == &z);
    assert(*ptr3 == 20);
    printf("modified successfully!\n");

    return 0;
}
