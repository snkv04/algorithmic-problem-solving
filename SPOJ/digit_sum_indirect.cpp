#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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

ll fast_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return fast_pow(b, e - 1) * b;
    else return fast_pow(b * b, e / 2);
}

ll solve(ll n) {
    ll mem[17][10][2];
    for (int i = 0; i <= 16; ++i) {
        for (int j = 0; j < 10; ++j) {
            fill(mem[i][j], mem[i][j] + 2, 0);
        }
    }
    mem[16][0][0] = 1;

    vector<int> digits;
    ll copy = n;
    for (int i = 0; i <= 16; ++i) {
        digits.push_back(copy % 10);
        copy /= 10;
    }

    ll ans = 0;
    for (int i = 15; i >= 0; --i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                mem[i][j][1] += mem[i + 1][k][1];
            }

            if (j < digits[i]) {
                for (int k = 0; k < 10; ++k) {
                    mem[i][j][1] += mem[i + 1][k][0];
                }
            } else if (j == digits[i]) {
                mem[i][j][0] += mem[i + 1][digits[i + 1]][0];
            }

            ans += mem[i][j][0] * j * (n % fast_pow(10, i) + 1);
            ans += mem[i][j][1] * j * fast_pow(10, i);
        }
    }
    return ans;
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
