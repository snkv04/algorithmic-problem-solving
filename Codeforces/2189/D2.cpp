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

void solve() {
    int n, c;
    cin >> n >> c;
    string s;
    cin >> s; s = '-' + s;
    if (s[1] == '0' || s[n] == '0') {
        cout << "-1\n";
        return;
    }
    s[1] = s[n] = '1';

    ll ways = 1;
    vector<int> evens, odds;
    if (s[2] == '?') s[2] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[i] != '?') {
            ll factor = (s[i] == '1') ? 2 : (i - 1);
            c = c / gcd(c, factor);
            ways = (ways * factor) % MOD;
        } else {
            if ((i - 1) % 2) {
                odds.push_back(i - 1);
            } else {
                evens.push_back(2);
            }
        }
    }
    if (c == 1) {
        cout << "-1\n";
        return;
    }
    if (odds.empty() && evens.empty()) {
        cout << ways << "\n";
        return;
    }

    if ((c & (c - 1)) != 0) {
        for (int i = 0; i < odds.size() + evens.size(); ++i) {
            ways = (ways * 2) % MOD;
        }
        cout << ways << "\n";
    } else {
        int p = __builtin_popcount(c - 1); assert((1 << p) == c);
        if (evens.size() >= p) {
            cout << "-1\n";
        } else {
            while (evens.size()) {
                ways = (ways * evens.back()) % MOD;
                --p;
                evens.pop_back();
            }

            // make as many odds into 2 as possible, and take largest while doing this
            while (p - 1 >= 1 && odds.size()) {
                ways = (ways * 2) % MOD;
                --p;
                odds.pop_back();
            }
            while (odds.size()) {
                ways = (ways * odds.back()) % MOD;
                odds.pop_back();
            }
            cout << ways << "\n";
        }
    }
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
