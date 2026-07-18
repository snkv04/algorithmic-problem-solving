#include <iostream>
#include <cassert>

enum class Color {
    RED, GREEN, BLUE
};

class Shape {
protected:
    Color color;

    Shape() : color(Color::GREEN) {}

    virtual std::string str() {
        return "(color = " + std::to_string(static_cast<int>(color)) + ")";
    }

    virtual ~Shape() = default;
};

class Square : public Shape {
    int width;

public:
    Square() : width(5) {}

    int get_width() {
        return width;
    }

    std::string str() override {
        return "(color = " + std::to_string(static_cast<int>(color)) + ", width = " + std::to_string(width) + ")";
    }

    ~Square() override = default;
};

class RoundObject {
protected:
    double eccentricity;

public:
    RoundObject() : eccentricity(1) {}

    double get_eccentricity() {
        return eccentricity;
    }
};

class Circle : public Shape, public RoundObject {
    double radius;

public:
    Circle() : radius(10.0) {
        eccentricity = 0;
    }

    double get_radius() {
        return radius;
    }

    std::string str() override {
        return "(color = " + std::to_string(static_cast<int>(color)) + ", radius = " + std::to_string(radius) + ")";
    }

    ~Circle() override = default;
};

void just_print_and_dont_modify(int &num) {
    std::cout << "num = " << num << std::endl;
}

int main() {
    // C-style casting: when used in C++, it does what it does in C but by running through a list of C++-style casts
    // advantage: easy to type.
    // disadvantage: pretty much 0 safety. don't use in modern C++.
    double pi = 3.14159265358979;
    int pi_as_int = (int) pi;
    std::cout << "pi (as double) = " << pi << ", pi_as_int = " << pi_as_int << std::endl;
    std::cout << std::endl;

    // static casting use cases are below.
    // benefit: skips runtime check, so is faster.
    // cost: causes UB if you are wrong.
    {
        // converting basic data types (e.g., float -> int)
        float pi = 3.14;
        std::cout << "pi (as float) = " << pi << ", static_cast<int>(pi) = " << static_cast<int>(pi) << std::endl;

        // casting enums to underlying ints
        Color color = Color::BLUE;
        std::cout << "static_cast<int>(color) = " << static_cast<int>(color) << std::endl;

        // pointer conversion to base/derived class, when true type is really known.
        // btw, "downcast" = base -> derived, and "upcast" = derived -> base.
        Shape *shape = new Square();
        // std::cout << "shape->get_width() = " << shape->get_width() << std::endl;  // compile-time error
        Square *square = static_cast<Square*>(shape);
        std::cout << "square->get_width() = " << square->get_width() << std::endl;  // works!
        // Circle *circle = static_cast<Circle*>(shape);  // undefined behavior
        // std::cout << "circle->get_radius() = " << circle->get_radius() << std::endl;

        // pointer conversion to/from void*
        // remember, void* is just an address, so it can't be dereferenced or have pointer arithmetic done on it
        void* ptr = static_cast<void*>(shape);
        Shape *shape2 = static_cast<Shape*>(ptr);
        std::cout << "shape = " << shape << ", ptr = " << ptr << ", shape2 = " << shape2 << std::endl;
    }
    std::cout << std::endl;

    // dynamic casting is pretty much entirely for casting pointers (or references, but that's not nearly as common).
    // benefit: safer than static_cast.
    // cost: slower at runtime.
    {
        // checking type when downcasting: good when there are multiple subclasses
        Shape *shape = new Circle();
        Square *square = dynamic_cast<Square*>(shape);  // will return nullptr
        assert(square == 0x00000000);  // returned nullptr!
        Circle *circle = dynamic_cast<Circle*>(shape);
        std::cout << "after downcasting from Shape*, circle->get_radius() = " << circle->get_radius() << std::endl;

        // directly casting from one superclass to another: good when a class is using multiple inheritance
        RoundObject *round_object = dynamic_cast<RoundObject*>(shape);
        std::cout << "after casting from Shape*, round_object->get_eccentricity() = " << round_object->get_eccentricity() << std::endl;
    }
    std::cout << std::endl;

    // const_cast is used for modifying the const-ness (or volatile-ness) of a variable.
    // benefit: useful in niche cases?
    // cost: rarely useful in the first place?
    {
        // dropping a const qualifier (useful when passing into functions whose arguments aren't marked const,
        // but you know they won't change your variable's value)
        int x = 5;
        const int &ref = x;
        // just_print_and_dont_modify(ref);  // compile-time error
        just_print_and_dont_modify(const_cast<int&>(ref));

        // adding a const qualifier (rarely needed, such as to avoid copy-on-write getting triggered as soon
        // as operator[] gets called even though the object isn't getting written to, but this only happens in
        // old C++ implementations)
        std::string s = "hello";
        char c = const_cast<const std::string&>(s)[2];
    }
    std::cout << std::endl;

    // reinterpret_cast reinterprets the bits.
    // benefit: very fast, just like static_cast,
    // because no run-time type information (RTTI) is checked at run-time.
    // cost: very low amount of safety.
    int arr[4] = {1, 2, 4, 8};
    int* ptr = arr;
    int* new_ptr_by_elems = ptr + 2;
    int* new_ptr_by_bytes = reinterpret_cast<int*>(reinterpret_cast<size_t>(ptr) + 2 * sizeof(arr[0]));
    std::cout << "ptr = " << ptr << ", *ptr = " << *ptr << ", arr[0] = " << arr[0] << std::endl;
    std::cout << "(new_ptr_by_elems == new_ptr_by_bytes) = " << (new_ptr_by_elems == new_ptr_by_bytes) << std::endl;
    int* new_ptr = new_ptr_by_bytes;
    std::cout << "new_ptr = " << new_ptr << ", *new_ptr = " << *new_ptr << ", arr[2] = " << arr[2] << std::endl;

    return 0;
}
