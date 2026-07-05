#include <bits/stdc++.h>
using namespace std;

int main() {
    // pointer to stack variable
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
    const int *q = &y;
    // *q = 15;  // not allowed!
    q = &z;  // allowed
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

    return 0;
}
