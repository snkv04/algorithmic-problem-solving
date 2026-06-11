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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<int> next(n, -1);
    stack<int> stk;
    for (int i = 0; i < n; ++i) {
        while (stk.size() && a[i] > a[stk.top()]) {
            next[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    vector<int> prev(n, -1);
    stk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (stk.size() && a[i] > a[stk.top()]) {
            prev[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    vector<int> sorted_indices(n);
    for (int i = 0; i < n; ++i) sorted_indices[i] = i;
    sort(sorted_indices.begin(), sorted_indices.end(), [&](int i, int j) {
        return a[i] < a[j];
    });

    vector<int> mem(n, 1);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int idx = sorted_indices[i];
        ans = max(ans, mem[idx]);

        if (prev[idx] != -1) {
            mem[prev[idx]] = max(mem[prev[idx]], mem[idx] + 1);
        }
        if (next[idx] != -1) {
            mem[next[idx]] = max(mem[next[idx]], mem[idx] + 1);
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
