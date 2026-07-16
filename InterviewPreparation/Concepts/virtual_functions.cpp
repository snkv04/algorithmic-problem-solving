#include <iostream>
#include <vector>

// base class = superclass = general case (less variables/functions)
class Base {
    int base_val;

// this access specifier changes what parts of Base are accessible through Base from external code
// (including INSIDE the code of Derived).
// by "through", i mean either through the class Base or through an instance/object of Base.
public:
    // constructor
    Base() : base_val(5) {}

    // normal function
    void print_base_val() {
        std::cout << "base_val = " << base_val << std::endl;
    }

    // virtual function (i.e., intended to be overridden)
    virtual void print_personal_val() {
        std::cout << "val = " << base_val << std::endl;
    }

    // virtual destructor
    // when? if we use a "Base*" to point to an object of type Derived. why? in order to run ~Derived().
    // especially important when ~Derived() would trigger destructors of data that are in Derived but not Base.
    virtual ~Base() = default;  // "default" = "give me the compiler-generated function (here, destructor)"
};

// abstract class
// is ONLY treated as an "abstract class" because it owns a pure virtual function,
// and therefore cannot be instantiated.
class Abstract {
protected:
    double abstract_val;

public:
    // constructor only exists to be (implicitly) called through Derived()
    Abstract() : abstract_val(40.0) {}

    // pure virtual function
    // has no implementation; MUST be implemented in derived classes
    virtual void print_smth() = 0;

    // virtual destructor (again)
    virtual ~Abstract() = default;
};

// derived class = subclass = special case (more variables/functions)
// this access specifier changes what parts of Base are accessible through Derived from external code.
// again, by "through", i mean either through the class Derived or through an instance/object of Derived.
class Derived : public Base, public Abstract {
    std::vector<int> derived_val;

public:
    // constructor implicitly calls Base() and Abstract() at the beginning,
    // similar to what is explicitly done in Python
    Derived() : derived_val(10, 20) {}

    void print_personal_val() override {
        std::cout << "val = ";
        for (size_t i = 0; i < derived_val.size(); ++i) {
            std::cout << derived_val[i] << ' ';
        }
        std::cout << std::endl;
    }

    void print_derived_val() {
        std::cout << "derived_val = ";
        for (size_t i = 0; i < derived_val.size(); ++i) {
            std::cout << derived_val[i] << ' ';
        }
        std::cout << std::endl;
    }

    void print_smth() override {
        std::cout << "abstract_val = " << abstract_val << std::endl;
    }

    ~Derived() override = default;  // same as "~Derived() override {}"
};

int main() {
    // base class functions
    Base *b = new Base();
    std::cout << "b:" << std::endl;
    b->print_base_val();
    b->print_personal_val();
    std::cout << std::endl;
    delete b;

    // if we don't use a pointer, then the object gets "sliced",
    // meaning that everything from Derived is sliced off
    // and we can only access variables and functions from Base
    Base b2 = Derived();
    // b2.print_derived_val();  // compile-time error

    // abstract class can't be instantiated
    // Abstract a;  // compiler error!

    // derived class functions, through a pointer
    Base *d = new Derived();
    std::cout << "d:" << std::endl;
    d->print_base_val();
    d->print_personal_val();
    std::cout << std::endl;
    delete d;

    // another derived class function, through a pointer
    Abstract *d2 = new Derived();
    std::cout << "d2:" << std::endl;
    d2->print_smth();
    std::cout << std::endl;
    delete d2;

    // can also just construct a derived object directly, through pointer or regularly,
    // and ignore the polymorphism
    Derived *d3 = new Derived();
    std::cout << "d3:" << std::endl;
    d3->print_base_val();
    d3->print_personal_val();
    d3->print_smth();
    delete d3;

    // some notes on dynamic dispatch:
    // - each class with virtual functions has a vtable
    // - each instance of a class with virtual functions (such as the instance created on the heap by "new")
    // has a vptr, pointing to the vtable of its true class
    // - the vtable itself has an entry for each virtual function, mapping to the address in the text/code segment
    // in memory where the function really lives
    // - all of this gets way more complex with multiple inheritance (e.g., above), so dw about it
    
    return 0;
}
