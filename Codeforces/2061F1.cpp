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

char flip(char c) {
    return '0' + (1 ^ (c - '0'));
}

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size();

    s = flip(s[0]) + s + flip(s[n - 1]);
    n += 2;
    t = s[0] + t + s[n - 1];

    vector<pair<int, int>> segments;
    segments.push_back({0, 0});
    int balance = 0;
    for (int i = 1; i < n; ++i) {
        balance += t[i] - s[i];
        if (balance == 0) {
            segments.push_back({segments.back().second + 1, i});
        }
    }
    if (balance) {
        cout << "-1\n";
        return;
    }
    // cout << segments << endl;

    int ans = 0;
    for (auto [l, r] : segments) {
        if (l == r) continue;

        assert(s[l] != t[l]);
        assert(s[r] != t[r]);

        int changes = 0;
        for (int i = l + 1; i <= r; ++i) {
            changes += t[i] != t[i - 1];
        }
        if (changes > 1) {
            cout << "-1\n";
            return;
        }
        assert(changes == 1);

        if (s[l] == s[l - 1] || s[r] == s[r + 1]) {
            cout << "-1\n";
            return;
        }

        changes = 0;
        for (int i = l + 1; i <= r; ++i) {
            changes += s[i] != s[i - 1];
        }
        int blocks = changes + 1;
        ans += blocks / 2;

        for (int i = l; i <= r; ++i) {
            s[i] = t[i];
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
