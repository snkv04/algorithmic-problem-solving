// must include the file with all the declarations
#include "point.h"

// the class and its functions have already been declared in point.h,
// so we only need to define the functions here,
// which is done using the scope operator.
// linker errors occur when a declaration is found, and it is used, but it's never defined.
Point::Point() {}

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point::Point(Point&& other) noexcept : x(other.x), y(other.y) {
    other.x = other.y = 0;
}

Point& Point::operator=(Point&& other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
        other.x = other.y = 0;
    }
    return *this;
}

int Point::get_x() {
    return x;
}

int Point::get_y() {
    return y;
}

// not actually a function inside Point.
// just a free function, with access to Point's private variables, due to the "friend" access modifier.
std::ostream& operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}
