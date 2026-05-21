#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<int> a(1e5);

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

int next(int num) {
    if (num % 2) return num + 1;
    else return num / 2;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.begin() + n);

    map<int, pair<int, int>> cost;
    for (int i = 0; i < n; ++i) {
        int a_i = a[i];

        if (i == 0) {
            if (a_i == 1) {
                cost[1] = {1, 0};
                cost[2] = {1, 1};
            } else {
                int ops = 0;
                while (true) {
                    cost[a_i] = {1, ops};
                    if (a_i == 1) break;
                    a_i = next(a_i);
                    ++ops;
                }
            }
        } else {
            if (a_i == 1) {
                if (cost.count(1)) {
                    cost[1].first += 1;
                }
                if (cost.count(2)) {
                    cost[2].first += 1;
                    cost[2].second += 1;
                }
            } else {
                int ops = 0;
                while (true) {
                    if (cost.count(a_i)) {
                        cost[a_i].first += 1;
                        cost[a_i].second += ops;
                    }
                    if (a_i == 1) break;
                    a_i = next(a_i);
                    ++ops;
                }
            }
        }
    }

    int ans = 1e9;
    for (auto [k, v] : cost) {
        auto [cnt, ops] = v;
        if (cnt == n) {
            ans = min(ans, ops);
        }
    }
    cout << ans << "\n";
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
