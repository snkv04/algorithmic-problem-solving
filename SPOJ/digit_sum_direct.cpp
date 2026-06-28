#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
ll mem[17][136][2];
vector<int> digits;

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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

ll dfs(int idx, int sum, bool less) {
    if (idx == 0) return sum;
    if (mem[idx][sum][less] != -1) return mem[idx][sum][less];

    ll result = 0;
    if (less) {
        for (int digit = 0; digit < 10; ++digit) {
            result += dfs(idx - 1, sum + digit, true);
        }
    } else {
        for (int digit = 0; digit < digits[idx - 1]; ++digit) {
            result += dfs(idx - 1, sum + digit, true);
        }
        result += dfs(idx - 1, sum + digits[idx - 1], false);
    }
    return mem[idx][sum][less] = result;
}

ll solve(ll n) {
    // - recursion can always be visualized with a tree, and DP is just memoized recursion
    // - each (i, j, k) is a node in the recursion tree
    // - each leaf holds the sum of digits on the path from the root to that leaf
    // - then, mem[i][j][k] = the sum of the leaves in the subtree of node (i, j, k)
    for (int i = 0; i <= 16; ++i) {
        for (int j = 0; j <= 135; ++j) {
            fill(mem[i][j], mem[i][j] + 2, -1);
        }
    }
    
    ll copy = n;
    digits.clear();
    for (int i = 0; i < 16; ++i) {
        digits.push_back(copy % 10);
        copy /= 10;
    }

    // - last digit, sum = 0, tight = true
    // - we start here because this is the root of the recursion tree, at the most significant digit
    return dfs(16, 0, 0);
}

void solve() {
    ll a, b;
    cin >> a >> b;
    cout << solve(b) - (a <= 1 ? 0 : solve(a - 1)) << endl;
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
