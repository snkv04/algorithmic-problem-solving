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
    int m;
    cin >> m;
    vector<vector<int>> a(2, vector<int>(m));
    cin >> a;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i || j) {
                a[i][j] += 1;
            }
        }
    }

    multiset<int> second_cw, second_ccw;
    vector<vector<int>> idx_cw(2, vector<int>(m)), idx_ccw(2, vector<int>(m));
    second_cw.insert(-1e9); second_ccw.insert(-1e9);
    int idx = 0;
    for (int i = 0; i < m; ++i) {
        second_cw.insert(a[0][i] - idx);
        idx_cw[0][i] = idx++;
    }
    for (int i = m - 1; i >= 0; --i) {
        second_cw.insert(a[1][i] - idx);
        idx_cw[1][i] = idx++;
    }
    idx = 2;
    for (int i = 1; i < m; ++i) {
        second_ccw.insert(a[1][i] - idx);
        idx_ccw[1][i] = idx++;
    }
    for (int i = m - 1; i >= 0; --i) {
        second_ccw.insert(a[0][i] - idx);
        idx_ccw[0][i] = idx++;
    }

    int ans = 2e9, first = 0, first_idx = 0, second_cw_shift = 0, second_ccw_shift = 0;
    auto remove = [&](int i, int j, multiset<int> &vals, vector<vector<int>> &idx) {  // just using this for bounds checking
        if (j >= m) return;
        vals.erase(vals.find(a[i][j] - idx[i][j]));
    };
    for (int j = 0; j < m; ++j) {
        if (j % 2 == 0) {
            ans = min(ans, max(first, *second_cw.rbegin() - second_cw_shift));

            for (int i = 0; i < 2; ++i) for (int k = j; k < j + 2; ++k) remove(i, k, second_cw, idx_cw);
            second_cw_shift += 2;

            first = max(first, a[0][j] - (first_idx++));
            first = max(first, a[1][j] - (first_idx++));
        } else {
            ans = min(ans, max(first, *second_ccw.rbegin() - second_ccw_shift));

            for (int i = 0; i < 2; ++i) for (int k = j; k < j + 2; ++k) remove(i, k, second_ccw, idx_ccw);
            second_ccw_shift += 2;

            first = max(first, a[1][j] - (first_idx++));
            first = max(first, a[0][j] - (first_idx++));
        }
    }
    ans += 2 * m - 1;
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
