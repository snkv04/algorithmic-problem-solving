#include <bits/stdc++.h>
#include "fraction.cpp"
using namespace std;
using ll = long long;
using ld = long double;

constexpr ld INF = 1e12, EPS = 1e-6;

struct Line;

struct Point {
    ld x, y;

    bool operator<(const Point &other) const {
        if (x != other.x) {
            return x < other.x;
        } else {
            return y < other.y;
        }
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    // effectively returns a vector, but there is an isomorphism between points and vectors
    Point operator-(const Point &other) {
        return Point{x - other.x, y - other.y};
    }

    ld sqnorm() {
        return x * x + y * y;
    }

    ld norm() {
        return sqrt(sqnorm());
    }

    Line perp_bisector(const Point& other);
};

struct Line {
    ld m, b, x;  // x = INF if the line isn't vertical, and x = the line's x-intercept otherwise

    Line(const Point &start, const Point &end) {
        if (abs(end.x - start.x) < EPS) {
            m = b = INF;
            x = start.x;
        } else {
            x = INF;
            m = (end.y - start.y) / (end.x - start.x);
            b = start.y - m * start.x;
        }
    }

    Line(ld x1, ld y1, ld x2, ld y2) : Line(Point{x1, y1}, Point{x2, y2}) {}

    Line(ld m, ld b, ld x) : m(m), b(b), x(x) {}

    // assumes line is not vertical
    static Line from_point_slope(ld x0, ld y0, ld m) {
        ld b = y0 - m * x0;
        return Line(m, b, INF);
    }

    // constructs vertical line
    static Line from_x_int(ld x) {
        return Line(INF, INF, x);
    }

    // assumes they don't have the same slope
    Point intersection(const Line &other) {
        if (x != INF) {
            return Point{x, other.m * x + other.b};
        }
        if (other.x != INF) {
            return Point{other.x, m * other.x + b};
        }

        ld x0 = (other.b - b) / (m - other.m);
        ld y0 = m * x0 + b;
        return Point{x0, y0};
    }
};

Line Point::perp_bisector(const Point &other) {
    if (abs(other.y - y) < EPS) {
        ld x0 = (x + other.x) / 2.0;
        return Line::from_x_int(x0);
    } else {
        ld slope;
        if (abs(other.x - x) < EPS) {
            slope = 0;
        } else {
            slope = -(other.x - x) / (other.y - y);
        }
        ld x0 = (x + other.x) / 2.0;
        ld y0 = (y + other.y) / 2.0;
        return Line::from_point_slope(x0, y0, slope);
    }
}
