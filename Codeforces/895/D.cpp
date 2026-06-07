#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<ll> fac, inv_fac;

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

ll multinomial(vector<int> &counts) {
    int sum = 0;
    ll res = 1;
    for (int c : counts) {
        sum += c;
        res *= inv_fac[c];
        if (res >= MOD) res %= MOD;
    }

    if (!sum) {
        return 0;
    } else {
        res *= fac[sum];
        if (res >= MOD) res %= MOD;
        return res;
    }
}

vector<int> to_vec(string &s) {
    int n = s.size();
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = s[i] - 'a';
    }
    return res;
}

void solve() {
    string s;
    cin >> s;
    vector<int> a = to_vec(s);
    cin >> s;
    vector<int> b = to_vec(s);
    int n = s.size();

    fac = vector<ll>(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv_fac = vector<ll>(n + 1, 1);
    inv_fac[n] = mod_inv(fac[n]);
    for (int i = n - 1; i >= 1; --i) {
        inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % MOD;
    }

    int idx = 0;
    while (a[idx] == b[idx]) ++idx;
    assert(idx < n);

    ll ans = 0;
    vector<int> cnt(26, 0);
    for (int i = n - 1; i > idx; --i) {
        // in each value of j, we only update a couple elements of cnt (and multinomial() depends only on cnt),
        // so we can just compute the base output of multinomial() once,
        // and modify that result in O(1) for each value of j
        ll base_ways = multinomial(cnt);

        for (int j = a[i] + 1; j < 26; ++j) {
            if (cnt[j]) {
                // --cnt[j];
                // ++cnt[a[i]];

                // ans += multinomial(cnt);
                // if (ans >= MOD) ans %= MOD;

                // --cnt[a[i]];
                // ++cnt[j];

                ll new_ways = base_ways * fac[cnt[j]] % MOD * inv_fac[cnt[j] - 1] % MOD * fac[cnt[a[i]]] % MOD * inv_fac[cnt[a[i]] + 1] % MOD;
                ans += new_ways;
                if (ans >= MOD) ans %= MOD;
            }
        }
        ++cnt[a[i]];
    }

    int lower = a[idx], upper = b[idx];
    ++cnt[a[idx]];
    while (true) {
        ll base_ways = multinomial(cnt);
        int sum = std::accumulate(cnt.begin(), cnt.end(), 0);
        for (int i = lower + 1; i < upper; ++i) {
            if (cnt[i]) {
                // --cnt[i];

                // ans += multinomial(cnt);
                // if (ans >= MOD) ans %= MOD;

                // ++cnt[i];

                ll new_ways = base_ways * fac[cnt[i]] % MOD * inv_fac[cnt[i] - 1] % MOD * inv_fac[sum] % MOD * fac[sum - 1] % MOD;
                ans += new_ways;
                if (ans >= MOD) ans %= MOD;
            }
        }

        if (cnt[upper] && idx + 1 < n) {
            --cnt[upper];
            ++idx;
            lower = -1;
            upper = b[idx];
        } else {
            break;
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
