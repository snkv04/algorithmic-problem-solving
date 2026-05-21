#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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

ll triangle(ll mx) {
    return mx * (mx + 1) / 2;
}

ll trapezoid(ll mn, ll mx) {
    return triangle(mx) - triangle(mn - 1);
}

void solve() {
    /*
    - suppose (x, z) is fixed; how many y's can we make? that's solvable in O(1)
    - then, we can iterate over z, and find the number of pairs (x, y) by noting the triangle-to-rectangle
    pattern that x has with y as x changes
    */
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll numy = c - b + 1, numx = b - a + 1;
    ll ans = 0;
    for (ll z = c; z <= d; ++z) {
        ll x_minany = z - c + 1, x_minall = z - b + 1;
        if (x_minany > b) break;

        if (x_minany < a) {
            if (x_minall <= a) {
                ans += numx * numy;
            } else {
                ans += trapezoid(a - x_minany + 1, min(b, x_minall) - x_minany + 1);
                ans += max(0LL, b - x_minall) * numy;
            }
        } else {
            ans += triangle(min(b, x_minall) - x_minany + 1);
            ans += max(0LL, b - x_minall) * numy;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
