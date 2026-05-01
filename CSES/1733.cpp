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
    long long get_hash(int left, int right) {
        long long result;
        result = (rolling[right] - (
            rolling[left] * PRIME_POWERS[right - left] % MOD
        ) + MOD) % MOD;
        return result;
    }

private:
    long long PRIME = 998244353, MOD = 1000000007;
    std::vector<long long> PRIME_POWERS, rolling;
    std::string str;
    int n;

    void _build_hashes() {
        rolling = std::vector<long long>(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int letter_as_int = str[i - 1];
            rolling[i] = (rolling[i - 1] * PRIME + letter_as_int) % MOD;
        }
    }

    void _build_powers() {
        PRIME_POWERS = std::vector<long long>(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            PRIME_POWERS[i] = (PRIME_POWERS[i - 1] * PRIME) % MOD;
        }
    }
};

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    RollingHash h(s);

    vector<vector<int>> multiples(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            multiples[i].push_back(j);
        }
    }

    // - optimizes harmonic series by skipping multiples of smaller prefixes that were already checked
    // - also optimized the hashing by only using one hash instead of a pair (though the collision
    // probability is greater)
    vector<bool> processed(n + 1, false);
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (processed[i]) continue;

        bool valid = true;
        for (int j = i; j < n && valid; j += i) {
            if (n - j >= i) {
                valid = valid && (h.get_hash(0, i) == h.get_hash(j, j + i));
            } else {
                int length = n - j;
                valid = valid && (h.get_hash(0, length) == h.get_hash(j, j + length));
            }
        }

        if (valid) {
            for (int &m : multiples[i]) {
                if (!processed[m]) {
                    processed[m] = true;
                    ans.push_back(m);
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    for (int &sz : ans) cout << sz << " ";
    cout << "\n";
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
