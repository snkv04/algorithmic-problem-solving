#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll gcd(ll a, ll b) {
    if (a < 0) a *= -1;
    if (b < 0) b *= -1;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

struct Frac {
    ll num, denom;

    Frac(ll n, ll d) : num(n), denom(d) {
        reduce();
    }

    Frac(ll x) : num(x), denom(1) {}

    bool operator<(const Frac &other) const {
        ll d = lcm(denom, other.denom);
        if (d < 0) d *= -1;
        ll n1 = num * (d / denom);
        ll n2 = other.num * (d / other.denom);
        return n1 < n2;
    }

    bool operator==(const Frac &other) const {
        Frac f1 = *this, f2 = other;
        f1.reduce(); f2.reduce();
        return f1.num == f2.num && f1.denom == f2.denom;
    }

    bool operator!=(const Frac &other) const {
        return !((*this) == other);
    }

    bool operator<=(const Frac &other) const {
        return *this < other || *this == other;
    }

    void reduce() {
        ll g = gcd(num, denom);
        num /= g;
        denom /= g;
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    Frac operator+(const Frac &other) {
        ll d = lcm(denom, other.denom);
        if (d < 0) d *= -1;
        ll n1 = num * (d / denom), n2 = other.num * (d / other.denom);
        Frac result(n1 + n2, d);
        result.reduce();
        return result;
    }

    Frac operator-(const Frac &other) {
        return (*this) + (Frac(-1) * other);
    }

    Frac operator*(const Frac &other) {
        Frac result(num * other.num, denom * other.denom);
        result.reduce();
        return result;
    }

    Frac operator/(const Frac &other) {
        Frac flipped(other.denom, other.num);
        return (*this) * flipped;
    }

    ll sign() {
        reduce();
        if (num == 0) return 0;
        else if (num > 0) return 1;
        else return -1;
    }
};

struct Point {
    Frac x, y;

    Point(Frac x, Frac y) : x(x), y(y) {}

    Point(ll x, ll y) : x(x), y(y) {}

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

    // effectively returns a vector, but there is a bijection between points and vectors
    Point operator-(const Point &other) {
        return Point{x - other.x, y - other.y};
    }
};

struct Hash {
    size_t operator()(const Point &p) const {
        std::array<ll, 4> arr = {p.x.num, p.x.denom, p.y.num, p.y.denom};
        ll hash = 0;
        for (ll num : arr) {
            hash ^= (hash << 6) + (hash >> 2) + 0x9e3779b9 + num;
        }
        return hash;
    }
};

Frac cross(Point &a, Point &b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    Point s, e;

    Line(ll x1, ll y1, ll x2, ll y2) : s(x1, y1), e(x2, y2) {
        if (e < s) swap(s, e);
    }

    Frac slope() {
        // assumes s.x != e.x
        Frac num = e.y - s.y, denom = e.x - s.x;
        Frac result = num / denom;
        result.reduce();
        return result;
    }

    Frac yint() {
        // y0 - m * x0
        return s.y - slope() * s.x;
    }
};

ostream& operator<<(ostream &os, Frac &f) {
    os << f.num << "/" << f.denom;
    return os;
}

ostream& operator<<(ostream &os, Point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}


ostream& operator<<(ostream &os, Line &l) {
    os << "[" << l.s << " to " << l.e << "]";
    return os;
}

void solve() {
    int n;
    cin >> n;
    vector<Line> lines;
    for (int i = 0; i < n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines.push_back(Line(x1, y1, x2, y2));
    }

    unordered_set<Point, Hash> isects;
    Frac zero(0, 1);
    for (int i = 0; i < n; ++i) {
        Line l1 = lines[i];
        for (int j = i + 1; j < n; ++j) {
            Line l2 = lines[j];

            // checking for intersection using cross products can't be done (i think) if the lines are
            // collinear, so we check for that first
            if (l1.s.x == l1.e.x && l2.s.x == l2.e.x) {
                // they are both vertical
                if (l1.s.x == l2.s.x) {
                    if (l1.s.y == l2.e.y) { // one point
                        isects.insert(Point(l1.s.x, Frac(l1.s.y)));
                        continue;
                    } else if (l1.e.y == l2.s.y) { // one point
                        isects.insert(Point(l1.s.x, l1.e.y));
                        continue;
                    } else if (max(l1.s.y, l2.s.y) <= min(l1.e.y, l2.e.y)) { // infinite points
                        cout << "-1\n";
                        return;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
            if (l1.s.x != l1.e.x && l2.s.x != l2.e.x && l1.slope() == l2.slope()) {
                // they both have the same non-vertical slope
                if (l1.yint() == l2.yint()) {
                    if (l1.s.x == l2.e.x) { // one point
                        isects.insert(Point(l1.s.x, l1.s.y));
                        continue;
                    } else if (l1.e.x == l2.s.x) { // one point
                        isects.insert(Point(l1.e.x, l1.e.y));
                        continue;
                    } else if (max(l1.s.x, l2.s.x) <= min(l1.e.x, l2.e.x)) { // infinite points
                        cout << "-1\n";
                        return;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }

            // now we know that they don't have the same slope, so we can check for intersection
            // using cross products
            // also, if they intersect, then we know for sure that there's only one intersection point
            Point ab(l1.e - l1.s), ac(l2.s - l1.s), ad(l2.e - l1.s), cd(l2.e - l2.s), ca(l1.s - l2.s), cb(l1.e - l2.s);
            ll c1 = cross(ab, ac).sign(), c2 = cross(ab, ad).sign(), c3 = cross(cd, ca).sign(), c4 = cross(cd, cb).sign();
            if (c1 * c2 <= 0 && c3 * c4 <= 0) {
                if (l1.s.x == l1.e.x) {
                    // l1 is vertical
                    Frac m = l2.slope();
                    Frac b = l2.yint();
                    Frac y = m * l1.s.x + b;
                    isects.insert(Point(l1.s.x, y));
                } else if (l2.s.x == l2.e.x) {
                    // l2 is vertical
                    Frac m = l1.slope();
                    Frac b = l1.yint();
                    Frac y = m * l2.s.x + b;
                    isects.insert(Point(l2.s.x, y));
                } else {
                    Frac m1 = l1.slope(), b1 = l1.yint(), m2 = l2.slope(), b2 = l2.yint();
                    Frac x = (b2 - b1) / (m1 - m2);
                    Frac y = m1 * x + b1;
                    isects.insert(Point(x, y));
                }
            }
        }
    }
    cout << isects.size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
