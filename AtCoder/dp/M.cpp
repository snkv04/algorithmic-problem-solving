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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;

    // mem[i][j] := number of ways to distribute j candies to the first i children
    // the "i" dimension is optimized away to save space
    // side note: prefix sums in modular fields are cooked
    vector<ll> mem(k + 1, 0), pref(k + 1, 1);
    mem[0] = 1;
    auto range_sum = [&](int l, int r, vector<ll> &pref) {
        ll result = pref[r] - (l == 0 ? 0 : pref[l - 1]);
        if (result < 0) result += MOD;
        return result;
    };
    for (int i = 1; i <= n; ++i) {
        vector<ll> new_mem(k + 1, 0), new_pref(k + 1, 0);
        for (int j = 0; j <= k; ++j) {
            int max_here = min(j, a[i - 1]);
            new_mem[j] = range_sum(j - max_here, j, pref);
            new_mem[j] %= MOD;
            new_pref[j] = (j == 0 ? 0 : new_pref[j - 1]) + new_mem[j];
            new_pref[j] %= MOD;
        }
        mem = std::move(new_mem);
        pref = std::move(new_pref);
    }
    cout << mem[k] << endl;
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
