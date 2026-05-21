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
    if (e % 2) return b * mod_pow(b, e - 1) % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

map<int, int> get_freqs(vector<int> &a) {
    map<int, int> freq;
    for (int a_i : a) freq[a_i] += 1;
    return freq;
}

set<int> get_primes(vector<int> &a) {
    vector<bool> is_prime(1e6 + 1, true);
    is_prime[1] = false;
    for (int d = 2; d <= 1e6; ++d) for (int i = 2 * d; i <= 1e6; i += d) is_prime[i] = false;

    set<int> primes;
    for (int a_i : a) if (is_prime[a_i]) primes.insert(a_i);
    return primes;
}

pair<vector<ll>, vector<ll>> precompute_factorials(int n) {
    vector<ll> fac(n + 1, 1);
    for (int i = 2; i <= n; ++i) fac[i] = (fac[i - 1] * i) % MOD;

    vector<ll> inv_fac(n + 1, 1);
    inv_fac[n] = mod_inv(fac[n]);
    for (int i = n - 1; i >= 1; --i) inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % MOD;

    return make_pair(fac, inv_fac);
}

void solve() {
    /*
    - useful ideas for the future:
        - if we are summing up or multiplying up a bunch of terms, check to see if there's a common term that
        can be taken out to simplify the brunt of the computation
        - if we want to distribute k selections across n objects, we can use an O(n*k) DP to keep track of the
        property we care about, so that mem[i][j] is the property from considering the first i objects and having
        selected k of them. this even works if k doesn't have to be the same across all subsets (e.g., if we want
        some properties for all subsets of size 1, 3, or 6). this can be used for computing combinations (though
        DP is obv slower than O(1) with factorials), probabilities, or summing up p(s) across all subsets s, where
        p(s) is just some property of that subset s.
    */

    // reads in the input
    int n;
    cin >> n;
    vector<int> a(2 * n);
    cin >> a;

    // precomputes frequencies and gets primes
    map<int, int> freq = get_freqs(a);
    set<int> primes = get_primes(a);
    if (primes.size() < n) {
        cout << "0\n";
        return;
    }

    // precomputes factorials and finds desired sum
    auto [fac, inv_fac] = precompute_factorials(n);
    vector<vector<ll>> mem(primes.size() + 1, vector<ll>(n + 1, 0));
    mem[0][0] = 1;  // i don't think this is mathematically correct, but it works for the sake of setting up mem[1][0]
    int idx = 1;
    for (auto it = primes.begin(); it != primes.end(); ++it) {
        int prime = *it;
        
        mem[idx][0] = inv_fac[freq[prime]] * mem[idx - 1][0] % MOD;
        for (int j = 1; j <= n; ++j) {
            // we do use the prime in the set
            mem[idx][j] += (inv_fac[freq[prime] - 1]) * mem[idx - 1][j - 1] % MOD;
            mem[idx][j] %= MOD;

            // we don't use the prime in the set
            mem[idx][j] += inv_fac[freq[prime]] * mem[idx - 1][j] % MOD;
            mem[idx][j] %= MOD;
        }

        ++idx;
    }

    // multiplies desired sum with constant to get answer
    set<int> composites; for (int a_i : a) if (!primes.count(a_i)) composites.insert(a_i);
    ll constant = fac[n];
    for (int c : composites) constant = (constant * inv_fac[freq[c]]) % MOD;

    ll ans = constant * mem[primes.size()][n] % MOD;
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
