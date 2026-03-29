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

void solve() {
    /*
    - problem:
        - find the number of triples (x, y, z) such that:
            - x falls in the range [A, B]
            - y falls in the range [B, C]
            - z falls in the range [C, D]
            - sticks with lengths of x, y, and z form a triangle
    - solution:
        - observe that if x and y are fixed, then we can count the number of valid z in O(1), as it's
        just the number of z < x+y that fall into [C, D]
        - then, observe that if x is fixed, then we can find the minimum y value y_{min,any} that allows
        ANY values of z, find the minimum y value y_{min,all} that allows ALL values of z, then count the
        number of (y, z) pairs between those as a triangle (with a Gaussian sum) and the number of (y, z)
        pairs after y_{min,all} as a rectangle with a simple product
            - the only difficulty is in dealing with edge cases with regard to where y_{min,any} and
            y_{min,all} fall in relation to [B, C]
        - as a result, we can calculate the number of (y, z) in O(1) for each x, so just iterate over each
        value of x
    */

    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll numy = c - b + 1, numz = d - c + 1;
    ll ans = 0;
    for (ll x = a; x <= b; ++x) {
        ll yl = c + 1 - x, yr = d + 1 - x;
        if (yl > c) continue;
        
        if (yl >= b) {
            ll r = min(yr, c);
            ll width = r - yl + 1;
            ans += width * (width + 1) / 2;
            width = max(0LL, c - r);
            ans += width * numz;
        } else {
            if (yr < b) {
                ans += numy * numz;
            } else if (yr <= c) {
                ll width = yr - yl + 1;
                ans += width * (width + 1) / 2;
                width = (b - 1) - yl + 1;
                ans -= width * (width + 1) / 2;

                width = c - yr;
                ans += width * numz;
            } else {
                ll width = c - yl + 1;
                ans += width * (width + 1) / 2;
                width = (b - 1) - yl + 1;
                ans -= width * (width + 1) / 2;
            }
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
