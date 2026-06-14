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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<ll> pre(n, 0);
    for (int i = 0; i < n; ++i) {
        pre[i] = (i == 0 ? 0 : pre[i - 1]) + a[i];
    }
    auto range_sum = [&](int l, int r) {
        return pre[r] - (l == 0 ? 0 : pre[l - 1]);
    };

    // mem[i][j] = maximum value that the first player can get on the segment [i, j] if both
    // players play optimally
    vector<vector<ll>> mem(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) if (n % 2) mem[i][i] = a[i];
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            int j = i + len - 1;
            if (len % 2 == n % 2) {
                mem[i][j] = max(
                    a[i] + mem[i + 1][j],
                    a[j] + mem[i][j - 1]
                );
            } else {
                ll if_left = a[i] + (range_sum(i + 1, j) - mem[i + 1][j]);
                ll if_right = a[j] + (range_sum(i, j - 1) - mem[i][j - 1]);
                if (if_left >= if_right) {
                    mem[i][j] = mem[i + 1][j];
                } else {
                    mem[i][j] = mem[i][j - 1];
                }
            }
        }
    }
    cout << mem[0][n - 1] << endl;
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
