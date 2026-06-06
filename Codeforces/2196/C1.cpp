#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
map<int, vector<int>> cache;

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

vector<int> query(int k) {
    if (cache.count(k)) return cache[k];

    cout << "? " << k << endl;
    vector<int> path;
    int sz;
    cin >> sz;
    while (sz--) {
        int node;
        cin >> node;
        path.push_back(node);
    }
    cache[k] = path;
    return path;
}

void answer(vector<pair<int, int>> &edges) {
    cout << "! " << edges.size() << endl;
    for (auto [a, b] : edges) {
        cout << a << " " << b << endl;
    }
}

void solve() {
    int n;
    cin >> n;
    cache.clear();

    vector<int> idx(n + 2, -1);
    idx[1] = 1;
    for (int i = 2; i <= n + 1; ++i) {
        int l = idx[i - 1] + 1, r = (1 << 30);
        while (l <= r) {
            int m = (l + r) / 2;
            auto path = query(m);
            if (path.empty() || path[0] >= i) {
                idx[i] = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
    }

    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        int len = idx[i + 1] - idx[i];
        if (len > 1) {
            int curr = idx[i] + 1;
            auto edge = query(curr);
            assert(edge.size() == 2);
            edges.push_back({edge[0], edge[1]});

            while (true) {
                int next = -1, l = curr + 1, r = (1 << 30);
                while (l <= r) {
                    int m = (l + r) / 2;
                    auto path = query(m);
                    if (path.empty() || path[0] > i || (path[0] == i && path[1] > edges.back().second)) {
                        next = m;
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }

                if (next == idx[i + 1]) {
                    break;
                } else {
                    curr = next;
                    auto edge = query(curr);
                    assert(edge.size() == 2);
                    edges.push_back({edge[0], edge[1]});
                }
            }
        }
    }
    answer(edges);
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
