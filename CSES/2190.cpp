#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

ll cross(pair<ll, ll> p1, pair<ll, ll> p2) {
    return p1.first * p2.second - p1.second * p2.first;
}

pair<ll, ll> operator-(const pair<ll, ll> p1, const pair<ll, ll> p2) {
    return make_pair(p1.first - p2.first, p1.second - p2.second);
}

ll sign(ll x) {
    if (!x) return 0;
    if (x > 0) return 1;
    return -1;
}

bool intersect(pair<ll, ll> p1, pair<ll, ll> p2, pair<ll, ll> p3, pair<ll, ll> p4) {
    if (
        max(p1.first, p2.first) < min(p3.first, p4.first) ||
        max(p3.first, p4.first) < min(p1.first, p2.first) ||
        max(p1.second, p2.second) < min(p3.second, p4.second) ||
        max(p3.second, p4.second) < min(p1.second, p2.second)
    ) {
        return false;
    }

    pair<ll, ll> v1 = p3 - p1, v2 = p4 - p1, v3 = p1 - p3, v4 = p2 - p3;
    pair<ll, ll> line1 = p2 - p1, line2 = p4 - p3;
    if (
        sign(cross(line1, v1)) * sign(cross(line1, v2)) == 1 ||
        sign(cross(line2, v3)) * sign(cross(line2, v4)) == 1
    ) {
        return false;
    } else {
        return true;
    }
}

void solve() {
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    pair<ll, ll> p1 = {x1, y1}, p2 = {x2, y2}, p3 = {x3, y3}, p4 = {x4, y4};
    cout << (intersect(p1, p2, p3, p4) ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
