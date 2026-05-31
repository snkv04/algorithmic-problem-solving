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

int query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int result;
    cin >> result;
    return result;
}

void answer(int x) {
    cout << "! " << x << endl;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> segments;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        segments.push_back({l, r});
    }
    if (n == 1) {
        answer(1);
        return;
    }

    int half = query(1, n / 2);
    int lbound, rbound;
    if (half) {
        lbound = 1;
        rbound = n / 2;
    } else {
        lbound = n / 2 + 1;
        rbound = n;
    }

    sort(segments.begin(), segments.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first != b.first) {
            return a.first < b.first;
        } else {
            return a.second > b.second;
        }
    });
    int maxr = -1;
    vector<pair<int, int>> filtered;
    for (auto [l, r] : segments) {
        if (r > maxr && !(r < lbound || rbound < l)) {
            filtered.push_back({l, r});
        }
        maxr = max(maxr, r);
    }

    int ans = 0;
    for (auto [l, r] : filtered) {
        ans = max(ans, query(l, r));
    }
    answer(ans);
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
