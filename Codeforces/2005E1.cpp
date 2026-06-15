#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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
    int l, n, m;
    cin >> l >> n >> m;
    vector<int> a(l);
    cin >> a;
    vector<vector<int>> grid(n, vector<int>(m));
    cin >> grid;

    vector<vector<int>> last(n + 1, vector<int>(m + 1, 0));
    for (int i = l - 1; i >= 0; --i) {
        vector<vector<int>> curr(n + 1, vector<int>(m + 1, 0));
        for (int r = n - 1; r >= 0; --r) {
            for (int c = m - 1; c >= 0; --c) {
                curr[r][c] = curr[r + 1][c] + curr[r][c + 1] - curr[r + 1][c + 1];
                if (grid[r][c] == a[i] && last[r + 1][c + 1] == 0) {
                    curr[r][c] += 1;
                }
            }
        }
        last = std::move(curr);
    }
    cout << (last[0][0] > 0 ? "T" : "N") << "\n";
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
