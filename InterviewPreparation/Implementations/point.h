// this is so that the header only gets included once,
// in the case that it gets indirectly included multiple times
#ifndef POINT_H
#define POINT_H

// the actual declarations begin here
#include <iostream>

class Point {
    int x, y;

public:
    Point();

    Point(int x, int y);

    Point(const Point& other);

    Point& operator=(const Point& other);

    Point(Point&& other) noexcept;

    Point& operator=(Point&& other) noexcept;

    ~Point() = default;  // definition is already done here, so no need to do it in point.cpp

    int get_x();

    int get_y();

    friend std::ostream& operator<<(std::ostream &os, const Point &point);
};

// ends off the block of code that is included
#endif
