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

ll all_ones(int n) {
    return (1LL << n) - 1;
}

ll binary_search(ll n) {
    ll l = 1, r = all_ones(n), ans = -1;
    while (l <= r) {
        ll m = (l + r) / 2;
        cout << "Q " << m << endl;
        
        int res;
        cin >> res;
        if (res) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;

    cout << 0 << endl;
    cout << "I 0" << endl;
    int res;
    cin >> res;
    if (res == 1) {
        cout << "I " << all_ones(n) << endl;
        cin >> res;
        assert(res == 2);

        ll c = binary_search(n);
        cout << "A 1 " << c << endl;
        return;
    }

    assert(res == 2);
    ll c = binary_search(n);
    int k;
    if (__builtin_popcountll(c) == 1) {
        cout << "I " << all_ones(n) << endl;
        cin >> res;
        assert(res == 3);

        cout << "Q " << all_ones(n) << endl;
        cin >> res;
        if (res) {
            k = 2;
        } else {
            k = 3;
        }
    } else {
        int lowest_bit = 0;
        while (((1LL << lowest_bit) & c) == 0) ++lowest_bit;

        cout << "I " << (1LL << lowest_bit) << endl;
        cin >> res;
        if (res == 2) {
            k = 2;
        } else {
            k = 3;
        }
    }
    cout << "A " << k << " " << c << endl;
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
