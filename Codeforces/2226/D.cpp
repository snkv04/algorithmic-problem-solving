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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<int> odds, evens;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2) {
            odds.push_back(a[i]);
        } else {
            evens.push_back(a[i]);
        }
    }

    int evenmin = 1e9, evenmax = -1e9, oddmin = 1e9, oddmax = -1e9;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2) {
            oddmin = min(oddmin, a[i]);
            oddmax = max(oddmax, a[i]);
        } else {
            evenmin = min(evenmin, a[i]);
            evenmax = max(evenmax, a[i]);
        }
    }

    int max_seen = -1e9;  // the worst-case inversion
    for (int odd : odds) {
        if (odd < max_seen) {
            if (evenmax <= max_seen && evenmin >= odd) {
                cout << "NO\n";
                return;
            }
        }
        max_seen = max(max_seen, odd);
    }
    max_seen = -1e9;
    for (int even : evens) {
        if (even < max_seen) {
            if (oddmax <= max_seen && oddmin >= even) {
                cout << "NO\n";
                return;
            }
        }
        max_seen = max(max_seen, even);
    }
    cout << "YES\n";
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
