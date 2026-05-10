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
std::ostream& operator<<(std::ostream &os, const std::set<T> &c) {
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

void dfs(int node, vector<ll> &path, vector<set<int>> &adj, vector<ll> &sz) {
    path[node] += sz[node];
    for (int next : adj[node]) {
        path[next] = path[node];
        dfs(next, path, adj, sz);
    }
}

void dfs2(
    int node,
    vector<ll> &root_path,
    vector<ll> &best_leaf_path,
    vector<set<int>> &adj, 
    vector<ll> &sz,
    ll &ans
) {
    multiset<ll> children = {0};
    for (int next : adj[node]) {
        dfs2(next, root_path, best_leaf_path, adj, sz, ans);
        children.insert(best_leaf_path[next]);
    }

    ll best1 = *children.rbegin(), best2 = 0;
    if (children.size() >= 2) {
        auto it = children.rbegin();
        ++it;
        best2 = *it;
    }
    ans = max(
        ans,
        root_path[node] + best1 + best2
    );

    best_leaf_path[node] = sz[node] + *children.rbegin();
}

void solve() {
    int n, h;
    cin >> n >> h;
    vector<int> a(n);
    cin >> a;

    // compresses heights
    map<int, int> compressed;
    compressed[h] = -1;
    for (int ai : a) compressed[ai] = -1;
    int idx = 0;
    for (auto it = compressed.begin(); it != compressed.end(); ++it) {
        it->second = idx++;
    }

    // gets height of each compressed slice
    vector<int> heights(idx);
    int last = 0;
    for (auto [k, v] : compressed) {
        heights[v] = k - last;
        last = k;
    }
    // cout << heights << endl;

    // merges blocks horizontally
    // i is x, j is compressed y
    auto flatten = [&](int i, int j) { return i * idx + j; };
    vector<ll> sz(n * idx + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < idx; ++j) {
            sz[flatten(i, j)] = heights[j];
        }
    }
    vector<vector<int>> rep(n, vector<int>(idx, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = idx - 1; j >= 0; --j) {
            if (j <= compressed[a[i]]) {
                break;
            }

            if (i != 0 && j > compressed[a[i - 1]]) {
                rep[i][j] = rep[i - 1][j];
                sz[rep[i][j]] += heights[j];
            } else {
                rep[i][j] = flatten(i, j);
            }
        }
    }
    // for (int i = 0; i < n; ++i) {
    //     cout << "rep[" << i << "] = " << rep[i] << endl;
    // }
    // cout << "sz = " << sz << "\n";

    // builds tree, using "ground" node at top
    int ground = n * idx;
    vector<set<int>> adj(n * idx + 1);
    for (int i = 0; i < n; ++i) {
        if (rep[i][idx - 1] == flatten(i, idx - 1)) {
            adj[ground].insert(flatten(i, idx - 1));
        }
    }
    for (int j = 0; j < idx - 1; ++j) {
        for (int i = 0; i < n; ++i) {
            if (compressed[a[i]] >= j) {
                continue;
            }

            if (rep[i][j] == flatten(i, j)) {
                adj[rep[i][j + 1]].insert(flatten(i, j));
            }
        }
    }
    // for (int i = 0; i <= ground; ++i) {
    //     cout << "adj[" << i << "] = " << adj[i] << endl;
    // }

    // computes weighted lengths of paths to root
    vector<ll> root_path(n * idx + 1, 0);
    dfs(ground, root_path, adj, sz);

    // gets answer by, for each node, picking two best paths to leaves
    vector<ll> best_leaf_path(n * idx + 1, 0);
    ll ans = 0;
    dfs2(ground, root_path, best_leaf_path, adj, sz, ans);
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
