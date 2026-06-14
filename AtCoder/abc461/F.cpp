#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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
    ll n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    vector<ll> to_fac;
    map<ll, int> to_idx;
    ll rt = sqrt(n);
    for (int i = 1; i <= rt; ++i) {
        if (n % i == 0) {
            to_fac.push_back(i);
            if (!(rt * rt == n && i == rt)) {
                to_fac.push_back(n / i);
            }
        }
    }
    sort(to_fac.begin(), to_fac.end());
    for (int i = 0; i < to_fac.size(); ++i) {
        to_idx[to_fac[i]] = i;
    }
    assert(to_idx[1] == 0);
    assert(to_idx[n] == to_fac.size() - 1);

    int num_factors = to_fac.size();
    vector<vector<ll>> mem(41, vector<ll>(num_factors, 0));
    vector<vector<ll>> mem2 = mem;
    mem[0][0] = 1;
    for (auto [fac, idx] : to_idx) {
        for (int len = 40; len >= 1; --len) {
            for (int j = 0; j < num_factors; ++j) {
                ll product = to_fac[j];
                if (product % fac == 0) {
                    mem[len][j] += len * mem[len - 1][to_idx[product / fac]];
                    mem[len][j] %= MOD;
                    mem2[len][j] += len * (mem2[len - 1][to_idx[product / fac]] + fac * mem[len - 1][to_idx[product / fac]]);
                    mem2[len][j] %= MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int len = 1; len <= 40; ++len) {
        ans += mem2[len][num_factors - 1];
        ans %= MOD;
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
