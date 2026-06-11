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

vector<vector<ll>> precompute_nCr_factorials(int n) {
    vector<ll> fac(n + 1, 1);
    for (int i = 1; i <= n; ++i) fac[i] = (fac[i - 1] * i) % MOD;
    vector<ll> inv(n + 1, 1);
    inv[n] = mod_inv(fac[n]); for (int i = n - 1; i >= 0; --i) inv[i] = (inv[i + 1] * (i + 1)) % MOD;

    vector<vector<ll>> nCr(n + 1, vector<ll>(n + 1, 0));
    for (int total = 0; total <= n; ++total) {
        for (int choosing = 0; choosing <= total; ++choosing) {
            nCr[total][choosing] = fac[total] * inv[choosing] % MOD * inv[total - choosing] % MOD;
        }
    }
    return nCr;
}

vector<vector<ll>> precompute_nCr_dp(int n) {
    vector<vector<ll>> nCr(n + 1, vector<ll>(n + 1, 0));
    for (int i = 0; i <= n; ++i) nCr[i][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]) % MOD;
        }
    }
    return nCr;
}

vector<vector<ll>> precompute_nCr(int n) {
    int mode = 1;
    switch (mode) {
        case 0:
            return precompute_nCr_factorials(n);
        case 1:
            return precompute_nCr_dp(n);
        default:
            throw std::runtime_error("no");
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(10);
    cin >> a;
    if (std::accumulate(a.begin(), a.end(), 0) > n || a[0] == n) {
        cout << 0 << endl;
        return;
    }

    auto nCr = precompute_nCr(n);
    // cout << nCr << endl;

    vector<ll> mem(n + 1, 0);
    mem[0] = 1;
    for (int i = 9; i >= 0; --i) {
        vector<vector<ll>> mem2(n + 1, vector<ll>(n + 1, 0));
        if (i) {
            for (int j = a[i]; j <= n; ++j) {
                for (int k = a[i]; k <= j; ++k) {
                    mem2[j][k] = nCr[j][k] * mem[j - k] % MOD;
                }
            }
        } else {
            for (int j = a[i] + 1; j <= n; ++j) {
                for (int k = a[i]; k <= j; ++k) {
                    mem2[j][k] = nCr[j - 1][k] * mem[j - k] % MOD;
                }
            }
        }

        for (int j = 0; j <= n; ++j) {
            mem[j] = std::accumulate(mem2[j].begin(), mem2[j].end(), 0LL) % MOD;
        }
    }
    cout << std::accumulate(mem.begin(), mem.end(), 0LL) % MOD << endl;
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
