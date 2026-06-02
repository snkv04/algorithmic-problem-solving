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

struct LCA {
    // assumes that adj is a tree
    LCA(const std::vector<std::vector<int>> &adj, int root) :
            n(adj.size()),
            MAX_POW(1 + std::ceil(std::log2(n))),
            adj(adj),
            depth(n, 0), 
            ancestor(MAX_POW + 1, std::vector<int>(n, -1)) {
        dfs(root, -1);
    }

    void dfs(int node, int parent) {
        ancestor[0][node] = parent;
        for (int i = 1; i <= MAX_POW; ++i) {
            int halfway = ancestor[i-1][node];
            if (halfway != -1) {
                ancestor[i][node] = ancestor[i-1][halfway];
            }
        }

        for (int next : adj[node]) {
            if (next == parent) continue;

            depth[next] = depth[node] + 1;
            dfs(next, node);
        }
    }

    int jump(int node, int height) {
        if (height > depth[node]) return -1;

        for (int i = 0; i <= MAX_POW; ++i) {
            if ((1 << i) & height) {
                node = ancestor[i][node];
            }
        }
        return node;
    }

    int lca(int node1, int node2) {
        if (depth[node1] > depth[node2]) std::swap(node1, node2);
        int diff = depth[node2] - depth[node1];
        node2 = jump(node2, diff);
        if (node1 == node2) return node1;

        for (int i = MAX_POW; i >= 0; --i) {
            if (ancestor[i][node1] != ancestor[i][node2]) {
                node1 = ancestor[i][node1];
                node2 = ancestor[i][node2];
            }
        }
        return ancestor[0][node1];
    }

private:
    int n;
    const int MAX_POW;
    const std::vector<std::vector<int>> &adj;
    std::vector<int> depth;
    std::vector<std::vector<int>> ancestor;
};

void solve() {
    // records the inputs
    int n;
    cin >> n;
    vector<int> w(n);
    cin >> w;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // gets the nodes for each value
    map<int, vector<int>> nodes;
    for (int i = 0; i < n; ++i) {
        nodes[w[i]].push_back(i);
    }

    // gets the LCA of the nodes with each value
    LCA lca(adj, 0);
    map<int, int> lcas;
    for (auto [k, v] : nodes) {
        int ancestor = v[0];
        for (int node : v) {
            ancestor = lca.lca(node, ancestor);
        }
        lcas[k] = ancestor;
    }

    // for each value, look at all nodes for the value below;
    // if there's any node that doesn't kill all nodes of the current value,
    // then we pick that and we win
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        auto nextit = it;
        ++nextit;
        if (nextit == nodes.rend()) break;

        int ancestor = lcas[it->first];
        for (int node : nextit->second) {
            if (lca.lca(ancestor, node) != node) {
                cout << node + 1 << "\n";
                return;
            }
        }
    }
    cout << "0\n";
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
