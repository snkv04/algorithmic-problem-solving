#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

ll sqrt(ll x) {
    if (x == 0) return 0;
    if (x < 0) throw std::runtime_error("negative input to sqrt");

    ll l = 1, r = x, ans = -1;
    while (l <= r) {
        ll m = l + (r - l) / 2;
        ll factor = x / m;
        if (m <= factor) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

// vector<ll> fact;

ll modpow(ll b, ll e) {
    if (e == 0) return 1;

    if (e % 2) {
        return (modpow(b, e - 1) * b) % MOD;
    } else {
        ll result = modpow(b, e / 2);
        return (result * result) % MOD;
    }
}

ll moddiv(ll a, ll b) {
    ll modinv = modpow(b, MOD - 2);
    return (a * modinv) % MOD;
}

ll nCr(ll n, ll r) {
    r = min(r, n - r);  // r (or n - r) is small

    ll num = 1, denom = 1;
    for (ll i = 1; i <= r; ++i) {
        num = (num * ((n + 1 - i) % MOD)) % MOD;
        denom = (denom * i) % MOD;
    }
    return moddiv(num, denom);
}

void solve() {
    /*
    - dp[i] represents the number of ways to have a sequence of length i that multiplies to factors[i]
    - the time complexity is O(sqrt(B) + d(B) * num_prime_factors(B))
    */

    ll n, a, b;
    cin >> n >> a >> b;
    a = min(a, b);
    if (b == 1) {
        cout << "1\n";
        return;
    }
    
    ll rt = sqrt(b);
    vector<ll> factors;
    for (ll i = 1; i <= rt; ++i) {
        if (b % i == 0) {
            factors.push_back(i);
            if (i * i != b) factors.push_back(b / i);
        }
    }
    sort(factors.begin(), factors.end());
    map<ll, int> toidx; for (int i = 0; i < factors.size(); ++i) toidx[factors[i]] = i;

    map<ll, int> prime_factors;
    ll b2 = b;
    for (int i = 2; i <= sqrt(b2); ++i) {
        while (b2 % i == 0) {
            b2 /= i;
            prime_factors[i] += 1;
        }
    }
    if (b2 > 1) {
        prime_factors[b2] += 1;
    }

    vector<ll> dp(factors.size(), 1);
    for (int i = 1; i < factors.size(); ++i) {
        ll f = factors[i];
        ll f2 = f;
        map<ll, int> prime_factorization;
        for (const pair<ll, int> entry : prime_factors) {
            ll p = entry.first;
            int freq = entry.second;
            for (int j = 0; j < freq; ++j) {
                if (f2 % p == 0) {
                    f2 /= p;
                    prime_factorization[p] += 1;
                } else {
                    break;
                }
            }
        }
        // print_container(prime_factorization, "prime factorization of " + to_string(f) + " = ");

        for (const pair<ll, int> entry : prime_factorization) {
            dp[i] = (dp[i] * nCr(entry.second + n - 1, n - 1)) % MOD;
        }
    }
    // print_container(dp, "dp = ");

    ll ans = 0;
    for (int i = 0; i < factors.size() && factors[i] <= a; ++i) {
        ans = (ans + dp[i] * dp[factors.size() - 1 - i]) % MOD;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
