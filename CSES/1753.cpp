#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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

struct RollingHash {
    RollingHash(std::string &str) : str(str), n(str.size()) {
        _build_hashes();
        _build_powers();
    }

    // left and right are both 0-based indices, where left is inclusive and right is exclusive
    std::pair<long long, long long> get_hash(int left, int right) {
        std::array<long long, 2> result;
        for (int field = 0; field < 2; ++field) {
            result[field] = (rolling[field][right] - (
                rolling[field][left] * PRIME_POWERS[field][right - left] % MOD[field]
            ) + MOD[field]) % MOD[field];
        }
        return std::make_pair(result[0], result[1]);
    }

private:
    std::vector<long long> PRIMES = {998244353, 999999937}, MOD = {1000000007, 1000000009};
    std::vector<std::vector<long long>> PRIME_POWERS, rolling;
    std::string str;
    int n;

    void _build_hashes() {
        rolling = std::vector<std::vector<long long>>(2, std::vector<long long>(n + 1, 0));
        for (int field = 0; field < 2; ++field) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = str[i - 1];
                rolling[field][i] = (rolling[field][i - 1] * PRIMES[field] + letter_as_int) % MOD[field];
            }
        }
    }

    void _build_powers() {
        PRIME_POWERS = std::vector<std::vector<long long>>(2, std::vector<long long>(n + 1, 1));
        for (int field = 0; field < 2; ++field) {
            for (int i = 1; i <= n; ++i) {
                PRIME_POWERS[field][i] = (PRIME_POWERS[field][i - 1] * PRIMES[field]) % MOD[field];
            }
        }
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    if (m > n) {
        cout << 0 << endl;
        return;
    } else if (m == n) {
        cout << (int) (s == t) << endl;
        return;
    }

    RollingHash hs(s), ht(t);
    auto pattern_hash = ht.get_hash(0, m);
    int ans = 0;
    for (int i = 0; i <= n - m; ++i) {
        ans += hs.get_hash(i, i + m) == pattern_hash;
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
