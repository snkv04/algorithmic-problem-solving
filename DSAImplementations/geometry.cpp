#include <bits/stdc++.h>

constexpr long double INF = 1e12, EPS = 1e-6;

struct Line;

struct Point {
    long double x, y;

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

    long double sqnorm() {
        return x * x + y * y;
    }

    long double norm() {
        return sqrt(sqnorm());
    }

    Line perp_bisector(const Point& other);
};

// most definitely a suboptimal representation, but it works
struct Line {
    long double m, b, x;  // x = INF if the line isn't vertical, and x = the line's x-intercept otherwise

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

    Line(long double x1, long double y1, long double x2, long double y2) : Line(Point{x1, y1}, Point{x2, y2}) {}

    Line(long double m, long double b, long double x) : m(m), b(b), x(x) {}

    // assumes line is not vertical
    static Line from_point_slope(long double x0, long double y0, long double m) {
        long double b = y0 - m * x0;
        return Line(m, b, INF);
    }

    // constructs vertical line
    static Line from_x_int(long double x) {
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

        long double x0 = (other.b - b) / (m - other.m);
        long double y0 = m * x0 + b;
        return Point{x0, y0};
    }
};

Line Point::perp_bisector(const Point &other) {
    if (abs(other.y - y) < EPS) {
        long double x0 = (x + other.x) / 2.0;
        return Line::from_x_int(x0);
    } else {
        long double slope;
        if (abs(other.x - x) < EPS) {
            slope = 0;
        } else {
            slope = -(other.x - x) / (other.y - y);
        }
        long double x0 = (x + other.x) / 2.0;
        long double y0 = (y + other.y) / 2.0;
        return Line::from_point_slope(x0, y0, slope);
    }
}
