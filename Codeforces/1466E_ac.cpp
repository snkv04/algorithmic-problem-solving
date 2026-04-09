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
    - this solution is correct because instead of splitting up the product across bits, which just absentmindedly
    dismisses the distributive property of multiplication and addition, it splits up multiple internal sums across bits
    so that we don't mess with the correctness of the multiplication
    - the core idea is that x_j can have many values, which makes it hard to precompute (sum across i of (x_j AND x_i)),
    but for a single bit x_j only has 2 values, and we can break up that previous sum into bits, so we can precompute
    (sum across i of (x_j AND x_i)) for each of the two values of x_j for each bit, then iterate through the bits of x_j
    and add up that sum for each bit to get the desired total sum.
    - when working in a modular field, you might have to mod things very frequently if many steps will exceed the
    maximum value
    */

    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    vector<ll> cnt(60, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 60; ++j) {
            cnt[j] += (a[i] & (1LL << j)) > 0;
        }
    }

    ll ans = 0;
    for (int j = 0; j < n; ++j) {
        ll AND = 0, OR = 0;
        for (int b = 0; b < 60; ++b) {
            if (a[j] & (1LL << b)) {
                AND += (1LL << b) % MOD * cnt[b] % MOD;
                OR += (1LL << b) % MOD * n % MOD;
            } else {
                OR += (1LL << b) % MOD * cnt[b] % MOD;
            }
            AND %= MOD;
            OR %= MOD;
        }
        ans += AND * OR % MOD;
        ans %= MOD;
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
