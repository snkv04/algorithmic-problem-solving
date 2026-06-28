#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<int> da, db;
ll max_product, max_val;
stack<int> stk;

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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

void dfs(int idx, bool started, bool ltb, bool gta, ll product) {
    if (idx == 0) {
        assert(started);
        if (product > max_product) {
            max_product = product;
            ll val = 0, multiplier = 1;
            stack<int> copy = stk;
            while (copy.size()) {
                val += copy.top() * multiplier;
                copy.pop();
                multiplier *= 10;
            }
            max_val = val;
        }
        return;
    }

    int mx = ltb ? 9 : db[idx - 1];
    int mn = mx - 1;
    if (!gta) mn = max(mn, da[idx - 1]);
    assert(mx - mn + 1 <= 2);  // don't even need memoization, since tree has O(2 ^ 18) leaves

    for (int d = mn; d <= mx; ++d) {
        ll next_started = started || d;
        ll next_product = product * (next_started ? d : 1);
        stk.push(d);
        dfs(idx - 1, next_started, ltb || d < db[idx - 1], gta || d > da[idx - 1], next_product);
        stk.pop();
    }
}

void solve() {
    ll a, b;
    cin >> a >> b;

    auto build_digits = [](ll n) {
        vector<int> digits;
        for (int i = 0; i < 19; ++i) {
            digits.push_back(n % 10);
            n /= 10;
        }
        return digits;
    };
    da = build_digits(a);
    db = build_digits(b);

    max_product = -1e9;
    max_val = -1e9;
    dfs(19, false, false, false, 1);
    assert(max_product != -1e9);
    // cout << "max product = " << max_product << ", max val = " << max_val << endl;
    cout << max_val << endl;
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
