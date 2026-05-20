#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<int> isprime;
vector<int> primes;

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

    vector<ll> ans = {1}; --n;
    ll bound = 1e18, idx = 0, curr = 1;
    while (true) {
        while (bound / (primes[idx] * primes[idx + 1]) >= ans.back() && n) {
            --n;
            ans.push_back(curr * primes[idx]);
            curr = ans.back();
        }
        if (!n) break;

        ++idx;
        ans.push_back(curr * primes[idx]); curr = primes[idx];
        if (!(--n)) break;
    }

    for (int i = 0; i < ans.size(); ++i) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    isprime = vector<int>(1e6 + 1, true);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= 1e6; ++i) {
        for (int j = 2 * i; j <= 1e6; j += i) {
            isprime[j] = false;
        }
    }
    for (int i = 2; i <= 1e6; ++i) {
        if (isprime[i]) {
            primes.push_back(i);
        }
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
