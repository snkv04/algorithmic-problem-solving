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
    return (char) ('0' + (1 ^ (c - '0')));
}

void flip(string &s, int l, int r) {
    for (int i = l; i <= r; ++i) {
        s[i] = flip(s[i]);
    }
}

vector<pair<int, int>> solve_to_0(string &s) {
    // finds longest segment in s, and if none, then makes one with an operation
    int n = s.size();
    int bestl = -1, bestr = -1, l = 0;
    vector<pair<int, int>> ops;
    for (int r = 1; r < n; ++r) {
        if (s[r] != s[r - 1]) {
            l = r;
        } else {
            if (r - l > bestr - bestl) {
                bestr = r;
                bestl = l;
            }
        }
    }
    if (bestl == -1) {
        ops.push_back(make_pair(0, 2));
        flip(s, 0, 2);
        bestl = 2;
        bestr = 3;
    }

    // propagates outward until entire string s has same char
    l = bestl;
    int r = bestr;
    while (l != 0 || r != n - 1) {
        while (l && s[l - 1] == s[l]) {
            --l;
        }
        while (r < n - 1 && s[r + 1] == s[r]) {
            ++r;
        }

        if (l == 0 && r == n - 1) {
            break;
        } else {
            ops.push_back({l, r});
            flip(s, l, r);
        }
    }
    if (s[0] == '1') {
        ops.push_back({l, r});
    }
    return ops;
}

void solve() {
    /*
    interesting idea:
    - if there's a forward and backward process, instead of implementing both, see if you can only
    implement the forward process, use it for both, then one-shot reverse the second one to get the
    backward process.
    */

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    auto ops = solve_to_0(s), backward = solve_to_0(t);
    reverse(backward.begin(), backward.end());
    ops.insert(ops.end(), backward.begin(), backward.end());
    cout << ops.size() << "\n";
    for (auto [l, r] : ops) {
        cout << l + 1 << " " << r + 1 << "\n";
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
