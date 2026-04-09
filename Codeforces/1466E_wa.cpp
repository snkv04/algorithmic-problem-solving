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
    vector<ll> a(n);
    cin >> a;

    // goes bit-by-bit, computing the AND and XOR values for each middle element (x_j)
    // the problem with this is that it splits a product across bits, which is mathematically incorrect
    ll ans = 0;
    for (ll b = 0; b < 60; ++b) {
        // gets the possible AND and OR values, based on if x_j is 0 or 1
        vector<ll> AND(2, 0), OR(2, 0);
        OR[1] = n;
        ll multiplier = 1LL << b;
        for (int i = 0; i < n; ++i) {
            ll bit = a[i] & multiplier;
            bit = bit >> b;
            if (bit) {
                ++AND[1];
                ++OR[0];
            }
        }

        // gets the contribution for bit b, and adds it to the total
        ll contribution = 0;
        for (int j = 0; j < n; ++j) {
            ll bit = a[j] & multiplier;
            bit >>= b;
            contribution = (contribution + (AND[bit] * OR[bit])) % MOD;
        }
        multiplier %= MOD;
        ans = (ans + (contribution * multiplier % MOD * multiplier)) % MOD;
    }
    cout << ans << endl;
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
