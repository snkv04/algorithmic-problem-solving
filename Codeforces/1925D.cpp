#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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
    b %= MOD;
    if (e % 2) return b * mod_pow(b, e - 1) % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

ll nCr(ll n, ll r) {
    ll num = fac[n];
    ll denom = fac[r] * fac[n - r] % MOD;
    return mod_div(num, denom);
}

ll nC2(ll n) {
    return n * (n - 1) / 2 % MOD;
}

void solve() {
    /*
    - key idea:
        - when taking expected value over all x in X of g(x), and g(x) is a sum expression (subtractions count!),
        then we can rewrite as a sum of expected values, where each inner expected value corresponds to a term
        in g(x).
    - other useful ideas:
        - also, can reduce from "set of all ordered selections of pairs" to "set of all assignments of pairs to
        frequencies". why? each assignment is repeated k! times, which multiplies both the numerator and the
        denominator of the expected value by k!.
    */

    int n, m, k;
    cin >> n >> m >> k;
    vector<array<ll, 3>> edges(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> edges[i][j];
        }
    }

    fac = vector<ll>(k + 1, 1);
    for (ll i = 1; i <= k; ++i) {
        fac[i] = (i * fac[i - 1]) % MOD;
    }

    vector<ll> prob(k + 1, 0);
    for (ll f = 0; f <= k; ++f) {
        ll p = mod_div(1, nC2(n));
        ll q = (1 - p + MOD) % MOD;
        prob[f] = mod_pow(p, f) * mod_pow(q, k - f) % MOD * nCr(k, f) % MOD;
    }
    // cout << prob << endl;
    // ll sum = 0;
    // for (ll p : prob) sum = (sum + p) % MOD;
    // cout << "sum = " << sum << endl;  // should be 1

    ll sum2 = 0;
    for (ll f = 0; f <= k; ++f) {
        sum2 += nC2(f) * prob[f] % MOD;
        sum2 %= MOD;
    }
    sum2 *= m;
    sum2 %= MOD;

    ll coeff = 0;
    for (ll f = 0; f <= k; ++f) {
        coeff += f * prob[f] % MOD;
        coeff %= MOD;
    }

    ll sum1 = 0;
    for (auto [a, b, w] : edges) {
        sum1 += w * coeff % MOD;
        sum1 %= MOD;
    }
    ll ans = (sum1 + sum2) % MOD;
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
