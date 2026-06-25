#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<pair<int, int>> deltas = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

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

pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
    return {a.first + b.first, a.second + b.second};
}

int count_pairs(set<pair<int, int>> &edges, map<pair<int, int>, int> &color, int n, int m) {
    int pairs = 0;
    set<pair<pair<int, int>, pair<int, int>>> used;
    for (auto p : edges) {
        for (auto d : deltas) {
            auto new_p = p + d;
            auto [new_x, new_y] = new_p;
            if (new_x < 1 || new_x > n || new_y < 1 || new_y > m) {
                continue;
            } else if (used.count({p, new_p})) {
                continue;
            } else {
                int c;
                if (edges.count(new_p)) {
                    c = color[new_p];
                } else {
                    c = 0;
                }
                pairs += color[p] != c;

                // might as well insert both; makes the "checking if used" logic straightforward
                used.insert({p, new_p});
                used.insert({new_p, p});
            }
        }
    }
    return pairs % 2;
}

int count_black_cells(set<pair<int, int>> &edges, map<pair<int, int>, int> &color) {
    int cnt = 0;
    for (auto e : edges) {
        cnt += color[e];
    }
    return cnt % 2;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    map<pair<int, int>, int> color;
    for (int i = 0; i < k; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        color[{x, y}] = c;
    }

    if (2LL * (n - 2) + 2LL * (m - 2) > k) {
        ll exp = 1LL * n * m - k - 1;
        ll ans = mod_pow(2, exp);
        cout << ans << endl;
    } else {
        set<pair<int, int>> edges;
        for (int y = 2; y < m; ++y) {
            edges.insert({1, y});
            edges.insert({n, y});
        }
        for (int x = 2; x < n; ++x) {
            edges.insert({x, 1});
            edges.insert({x, m});
        }

        bool all_in = true;
        for (auto p : edges) {
            if (color.count(p) == 0) {
                all_in = false;
                break;
            }
        }

        if (!all_in) {
            cout << mod_pow(2, 1LL * n * m - k - 1) << endl;
        } else {
            int mode = 1;
            int pair_parity;
            if (mode) {
                pair_parity = count_black_cells(edges, color);
            } else {
                pair_parity = count_pairs(edges, color, n, m);
            }

            if (pair_parity) {
                cout << 0 << endl;
            } else {
                ll exp = 1LL * n * m - k;
                ll ans = mod_pow(2, exp);
                cout << ans << endl;
            }
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
