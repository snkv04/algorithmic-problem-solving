#include <iostream>

int main() {
    // allocated onto stack
    // "default-initialized": initialized to some garbage
    // "value-initialized": initialized to that datatype's understanding of 0
    {
        // standard case of default-initialization
        int arr[5];
        printf("this should be some garbage: ");
        for (int i = 0; i < 5; ++i) printf("%d ", arr[i]);
        printf("\n");
    }
    {
        // when using initializer list, can fill in some prefix of values and value-initialize the rest
        int arr[5] = {1, 2, 3};
        printf("first few filled in, rest are : ");
        for (int i = 0; i < 5; ++i) printf("%d ", arr[i]);
        printf("\n");
    }
    {
        // can also use initializer list to value-initialize everything
        int arr1[5] = {};
        printf("all 0s: ");
        for (int i = 0; i < 5; ++i) printf("%d ", arr1[i]);
        printf("\n");

        // or manually initialize everything
        int arr2[5] = {1, 2, 3, 4, 5};
        printf("manually initialized: ");
        for (int i = 0; i < 5; ++i) printf("%d ", arr2[i]);
        printf("\n");
    }
    {
        // surprisingly, can also infer static array size, due to using initializer list
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
        printf("inferred size through initializer list: ");
        for (int i = 0; i < 8; ++i) printf("%d ", arr[i]);
        printf("\n");
    }
    std::ios::sync_with_stdio(true);
    std::cout << std::endl;
    
    // allocated onto heap
    // the "new" keyword automatically means that it's allocated on the heap
    {
        // standard case of default-initialization
        // (though the OS is generous and fills in 0s, but that's not always the case)
        int *ptr = new int[5];
        printf("this should be some garbage: ");
        for (int i = 0; i < 5; ++i) printf("%d ", ptr[i]);
        printf("\nalso, weird syntax: ");
        for (int i = 0; i < 5; ++i) printf("%d ", i[ptr]);
        printf("\n");
    }
    {
        // value-initialization with "constructor" syntax
        // (no constructors for primitive types, technically, but does same thing)
        int *arr1 = new int[5]();
        printf("constructor syntax: ");
        for (int i = 0; i < 5; ++i) printf("%d ", arr1[i]);
        printf("\n");
        delete[] arr1;

        // value-initialization with initializer list syntax
        int *arr2 = new int[5]{};
        printf("initializer list syntax: ");
        for (int i = 0; i < 5; ++i) printf("%d ", arr2[i]);
        printf("\n");
        delete[] arr2;
    }
    
    // random concept: most vexing parse is when a (seeming) variable declaration is actually a function
    // declaration due to C++'s weird and somewhat unintuitive ambiguity resolution
    int a();

    return 0;
}
