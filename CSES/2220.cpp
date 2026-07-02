#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
ll mem[20][10][2][2];
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

ll dfs(int idx, int digit, bool tight, bool started) {
    if (idx == 0) return 1;
    if (mem[idx][digit][tight][started] != -1) return mem[idx][digit][tight][started];

    array<bool, 10> next{};
    int bound = tight ? digits[idx - 1] : 9;
    for (int i = 0; i <= bound; ++i) {
        if (i != digits[idx] || !started) {
            next[i] = true;
        }
    }

    ll &result = mem[idx][digit][tight][started] = 0;
    for (int i = 0; i < 10; ++i) {
        if (next[i]) {
            result += dfs(idx - 1, i, tight && i == digits[idx - 1], started || i);
        }
    }
    return result;
}

ll solve(ll n) {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 2; ++k) {
                fill(mem[i][j][k], mem[i][j][k] + 2, -1);
            }
        }
    }

    digits.clear();
    for (int i = 0; i < 20; ++i) {
        digits.push_back(n % 10);
        n /= 10;
    }

    return dfs(19, 0, 1, 0);
}

void solve() {
    ll a, b;
    cin >> a >> b;
    if (a == 0 && b == 0) {
        cout << 1 << endl;
        return;
    }
    cout << solve(b) - (a >= 1 ? solve(a - 1) : 0) << endl;
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
