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
    ll n, m, c;
    cin >> n >> m >> c;
    vector<vector<ll>> a(n, vector<ll>(m));
    cin >> a;
    a.insert(a.begin(), vector<ll>(m, 0));

    vector<ll> mem2(m, 0);
    for (int i = 1; i <= n; ++i) {
        vector<vector<ll>> mem(m, vector<ll>(m, 1e18));  // don't actually need to waste memory like this, but helps with visualization
        vector<ll> newmem2(m, 1e18);
        for (int k = 0; k < m; ++k) {
            for (int newj = 0; newj < m; ++newj) {
                int oldj = (newj + k) % m;

                // can come from above if not first line or (is first line and new column is 0)
                if (i > 1 || (i == 1 && newj == 0)) {
                    mem[k][oldj] = min(mem[k][oldj], mem2[newj] + k * c + a[i][oldj]);
                }

                // can come from left if new column is not 0
                if (newj) {
                    mem[k][oldj] = min(mem[k][oldj], mem[k][(oldj + m - 1) % m] + a[i][oldj]);
                }
            }
        }
        // cout << "i = " << i << ", mem = " << mem << endl;

        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                int newj = (j + m - k) % m;
                newmem2[newj] = min(newmem2[newj], mem[k][j]);
            }
        }
        mem2 = std::move(newmem2);
    }
    cout << mem2[m - 1] << endl;
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
