#include <iostream>
#include <vector>

class Traced {
    int id;

    std::string id_prefix() const {
        return '[' + std::to_string(id) + "] ";
    }

public:
    Traced(int id) : id(id) {
        std::cout << id_prefix() << "Called constructor" << std::endl;
    }

    Traced(const Traced& other) : id(other.id) {
        std::cout << id_prefix() << "Called copy constructor" << std::endl;
    }

    Traced& operator=(const Traced& other) {
        std::cout << id_prefix() << "Called copy assignment operator" << std::endl;
        if (this != &other) {
            id = other.id;
        }
        return *this;
    }

    Traced(Traced&& other) noexcept : id(other.id) {
        std::cout << id_prefix() << "Called move constructor" << std::endl;
        other.id = 0;
    }

    Traced& operator=(Traced&& other) noexcept {
        std::cout << id_prefix() << "Called move assignment operator" << std::endl;
        if (this != &other) {
            id = other.id;
            other.id = 0;
        }
        return *this;
    }

    ~Traced() {
        std::cout << id_prefix() << "Called destructor" << std::endl;
        id = 0;
    }
};

Traced make_traced(int id) {
    return Traced(id);
}

Traced make_traced_named(int id) {
    Traced t(id);
    return t;
}

Traced make_traced_named_no_nrvo(bool flag) {
    Traced a(10), b(20);
    if (flag) return a;
    else return b;
}

int main() {
    // generally true statement: objects are destroyed in opposite order that they were constructed in

    // push_back vs. emplace_back
    {
        // basic example of implicit call to move constructor
        // function order:
        // constructor for initial object ->
        // move constructor for object on vector ->
        // destructor for initial object, after object on vector has been made ->
        // destructor for object on vector, when vector goes out of scope
        std::vector<Traced> vec;
        vec.reserve(10);  // just to avoid confusing outputs from reallocations!
        vec.push_back(Traced(1));

        // no moving is ever done! emplace_back skips the move/copy that is done with push_back,
        // because the object is constructed directly in the memory block of the vector.
        // function order:
        // constructs object (directly on vector, using constructor args) -> destroys object (at end of scope)
        vec.emplace_back(2);
    }

    // return value optimization (RVO)
    {
        // no move/copy is done; it is "elided", and object is constructed directly in t's memory.
        // guaranteed by standard in C++17 and above to be implemented by compiler.
        // function order:
        // constructor -> destructor
        Traced t = make_traced(3);
    }

    // named return value optimization (NRVO)
    {
        // not guaranteed by standard in C++17 and above to be implemented by compiler,
        // but is still usually done in most compliers.
        // function order:
        // constructor -> destructor
        Traced with_nrvo = make_traced_named(4);

        // fails if compiler cannot predict what will be returned,
        // such as if the branch that gets executed is uncertain.
        // function order:
        // two constructors in the function ->
        // one of them gets moved to here ->
        // both objects in function get destroyed ->
        // value here gets destroyed
        Traced without_nrvo = make_traced_named_no_nrvo(true);
    }

    return 0;
}
