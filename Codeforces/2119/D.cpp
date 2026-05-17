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

void solve() {
    int n, m;
    cin >> n >> m;

    // - let g(t) = the number of valid sequences a that allow the token removal sequence t
    // - then mem[i][j] = sum of g(t) over all sequences t such that only tokens >= i (well, i + 1 due to the
    // implementation) are considered and a total of j tokens are used in t
    vector<vector<ll>> mem(n + 1, vector<ll>(n + 1, 0));
    mem[n][0] = 1;
    for (int token = n - 1; token >= 0; --token) {
        for (int used = 0; used <= n - token; ++used) {
            // we don't use token i
            mem[token][used] = mem[token + 1][used];

            // we do use token i
            if (used) {
                mem[token][used] += (token + 1) * (n - token - (used - 1)) * mem[token + 1][used - 1];
            }

            // stay under mod
            if (mem[token][used] >= m) {
                mem[token][used] %= m;
            }
        }
    }

    // iterate through all sizes of subsets of tokens
    ll sum = 0;
    for (int used = 0; used <= n; ++used) {
        sum += mem[0][used];
    }
    sum %= m;
    cout << sum << "\n";
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
