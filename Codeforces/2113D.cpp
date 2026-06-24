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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    int amn = 1e9, amx = -1e9, bmn = 1e9;
    for (int i = 0; i < n; ++i) {
        amn = min(amn, a[i]);
        amx = max(amx, a[i]);
        bmn = min(bmn, b[i]);
    }
    if (amx < bmn) {
        cout << 0 << endl;
        return;
    }
    if (b[0] < amn) {
        cout << n << endl;
        return;
    }

    vector<int> pre_a(n), pre_a_2(n), pre_b(n), suf_a(n);
    int mn = 1e9, mn2 = 1e9;
    for (int i = 0; i < n; ++i) {
        if (a[i] < mn) {
            mn2 = mn;
            mn = a[i];
        } else if (a[i] < mn2) {
            mn2 = a[i];
        }
        pre_a[i] = mn;
        pre_a_2[i] = mn2;

        pre_b[i] = min(i == 0 ? (int) 1e9 : pre_b[i - 1], b[i]);
        suf_a[n - 1 - i] = max(i == 0 ? (int) -1e9 : suf_a[n - i], a[n - 1 - i]);
    }

    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        int new_mn;
        if (suf_a[i + 1] < pre_a[i]) {
            new_mn = pre_a[i];  // don't swap cards
        } else {
            new_mn = min(pre_a_2[i], suf_a[i + 1]);  // swap cards
        }

        if (new_mn > pre_b[n - 1 - i]) {
            ans = i + 1;
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
