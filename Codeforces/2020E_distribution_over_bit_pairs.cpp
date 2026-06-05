#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
ll mem[10][10][2][2];

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
    vector<ll> a(n), p(n);
    cin >> a >> p;
    ll inv1e4 = mod_inv(1e4);

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 2; ++k)
                for (int l = 0; l < 2; ++l)
                    if (k == 0 && l == 0)
                        mem[i][j][k][l] = 1;
                    else
                        mem[i][j][k][l] = 0;
    
    for (int m = 0; m < n; ++m) {
        ll num = a[m], prob = p[m] * inv1e4 % MOD, prob_not = (1 - prob + MOD) % MOD;
        
        // makes new table based on this element of a
        ll new_mem[10][10][2][2];
        for (int i = 0; i < 10; ++i) {
            int biti = (num >> i) & 1;
            for (int j = 0; j < 10; ++j) {
                int bitj = (num >> j) & 1;
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        new_mem[i][j][k][l] = (prob_not * mem[i][j][k][l] + prob * mem[i][j][k ^ biti][l ^ bitj]) % MOD;
                    }
                }
            }
        }

        // copies table back into old memory
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                for (int k = 0; k < 2; ++k)
                    std::copy(new_mem[i][j][k], new_mem[i][j][k] + 2, mem[i][j][k]);
    }

    // even though i and j are symmetric when it comes to the probability that a pair of bits is equal to some pair of values,
    // so we can slightly optimize the code by keeping j >= i or something, there's no need for that, since the code is simpler
    // (and more similar to the math) if i and j just both iterate over every value.
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(mem[i][j][k][l] == mem[j][i][l][k]);
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            ans += (mem[i][j][1][1] * (1LL << (i + j))) % MOD;
            ans %= MOD;
        }
    }
    cout << ans << endl;
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
