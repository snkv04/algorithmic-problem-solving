#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e6 + 3; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<ll> fac;

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
    vector<int> a(n), b(n);
    cin >> a >> b;
    
    int doubles = 1e9;
    for (int i = 0; i < n; ++i) {
        int curr = a[i], times = 0;
        while (curr * 2 <= b[i]) {
            curr *= 2;
            times += 1;
        }
        doubles = min(doubles, times);
    }

    ll total_ops = doubles;
    vector<vector<int>> adds(doubles + 1, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        int diff = b[i] - (a[i] * (1 << doubles));
        for (int p = doubles; p >= 0; --p) {
            adds[p][i] = diff / (1 << p);
            total_ops += adds[p][i];
            diff %= (1 << p);
        }
    }

    ll ways = 1;
    for (int p = 0; p <= doubles; ++p) {
        ll before_fac = 0;
        for (int i = 0; i < n; ++i) {
            before_fac += adds[p][i];
        }
        if (before_fac >= MOD) {  // numerator is automatically divisible by MOD, since it's a factorial!
            ways = 0;
            break;
        }

        ll level_ways = fac[before_fac];
        for (int i = 0; i < n; ++i) {
            level_ways = mod_div(level_ways, fac[adds[p][i]]);  // multinomial formula
        }
        ways = (ways * level_ways) % MOD;
    }
    cout << total_ops << " " << ways << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fac = vector<ll>(MOD, 1);
    for (int i = 1; i < MOD; ++i) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
