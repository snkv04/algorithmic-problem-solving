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

int get_mask(int num, vector<int> &primes) {
    map<int, int> pf;
    for (int prime : primes) {
        while (num % prime == 0) {
            pf[prime] += 1;
            num /= prime;
        }
    }
    if (num != 1) pf[num] += 1;

    int mask = 0;
    for (int i = 0; i < primes.size(); ++i) {
        if (pf.count(primes[i]) && pf[primes[i]] % 2) {
            mask += 1 << i;
        }
    }
    return mask;
}

map<int, ll> get_mem_slow(vector<int> &a, vector<int> &primes) {
    map<int, ll> mem;
    for (int a_i : a) {
        int mask = get_mask(a_i, primes);
        map<int, ll> new_mem = mem;
        for (auto [k, v] : mem) {
            new_mem[k ^ mask] += v;
        }

        mem = std::move(new_mem);
        mem[mask] += 1;
        for (auto &[k, v] : mem) {
            v %= MOD;
        }
    }
    return mem;
}

map<int, ll> get_mem_fast(vector<int> &a, vector<int> &primes) {
    map<int, int> freq;
    for (int a_i : a) freq[a_i] += 1;

    map<int, ll> mem;
    for (auto [num, frequency] : freq) {
        ll odd_subsets = mod_pow(2, frequency - 1);
        ll even_subsets = (odd_subsets + MOD - 1) % MOD;
        int mask = get_mask(num, primes);

        map<int, ll> new_mem = mem;
        for (auto [k, v] : mem) {
            new_mem[k] += (v * even_subsets) % MOD;
            new_mem[k] %= MOD;

            new_mem[k ^ mask] += (v * odd_subsets) % MOD;
            new_mem[k ^ mask] %= MOD;
        }

        new_mem[0] += even_subsets;
        new_mem[0] %= MOD;
        new_mem[mask] += odd_subsets;
        new_mem[mask] %= MOD;

        mem = std::move(new_mem);
    }
    return mem;
}

void solve() {
    /*
    - uses same optimization as my solution to https://codeforces.com/problemset/problem/1829/H,
    namely an optimization that one-shots all instances of the same element by getting its frequency
    and calculating number of subsets that way; here, though, it's a little different, because we want
    the number of subsets of even size and the number of subsets of odd size separately
    */

    vector<int> is_prime(71, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= 70; ++i) {
        for (int j = 2 * i; j <= 70; j += i) {
            is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= 70; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // map<int, ll> mem = get_mem_slow(a, primes);
    map<int, ll> mem = get_mem_fast(a, primes);
    cout << (mem.count(0) ? mem[0] : 0) << endl;
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
