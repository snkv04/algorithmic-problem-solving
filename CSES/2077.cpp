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

/** @return the block-cut tree of a graph */
vector<vector<int>> biconnected_components(
    vector<vector<int>> &g,
    vector<bool> &is_cutpoint, // same size as g
    vector<int> &id // same size as g, but IDs themselves might go higher, so allocate 3*n if doing operations on BCT
) {
    int n = (int)g.size();

    vector<vector<int>> comps; // holds the actual BCCs
    vector<int> stk;
    vector<int> num(n);
    vector<int> low(n);

    is_cutpoint.resize(n);
    id.resize(n);

    // Finds the biconnected components
    function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
        num[node] = low[node] = ++timer;
        stk.push_back(node);
        for (int son : g[node]) {
            if (son == parent) { continue; }
            if (num[son]) {
                low[node] = min(low[node], num[son]);
            } else {
                dfs(son, node, timer);
                low[node] = min(low[node], low[son]);
                if (low[son] >= num[node]) {
                    is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
                    comps.push_back({node});
                    while (comps.back().back() != son) {
                        comps.back().push_back(stk.back());
                        stk.pop_back();
                    }
                }
            }
        }
    };

    int timer = 0;
    dfs(0, -1, timer);

    // Build the block-cut tree
    function<vector<vector<int>>()> build_tree = [&]() {
        vector<vector<int>> t(1);
        int node_id = 0;
        for (int node = 0; node < n; node++) {
            if (is_cutpoint[node]) {
                id[node] = node_id++;
                t.push_back({});
            }
        }

        for (auto &comp : comps) {
            int node = node_id++;
            t.push_back({});
            for (int u : comp)
                if (!is_cutpoint[u]) {
                    id[u] = node;
                } else {
                    t[node].push_back(id[u]);
                    t[id[u]].push_back(node);
                }
        }
        return t;
    };

    return build_tree();
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> is_articulation_point(n, false);
    vector<int> id(n, -1);
    auto _ = biconnected_components(adj, is_articulation_point, id);

    vector<int> ans;
    for (int i = 0; i < n; ++i) if (is_articulation_point[i]) ans.push_back(i + 1);

    cout << ans.size() << endl;
    for (auto node : ans) {
        cout << node << ' ';
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
