#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXN = 2e5 + 5;
vector<pair<int, int>> adj[MAXN];
int n, m;
int maxpow;
vector<int> depth;
vector<bool> visited;
vector<vector<int>> ancestor, maxedge;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

struct DSU {
    int n;
    vector<int> parent;

    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
        }
    }
};

void dfs(int node) {
    visited[node] = true;
    for (pair<int, int> next : adj[node]) {
        int nextnode = next.first, weight = next.second;
        if (!visited[nextnode]) {
            depth[nextnode] = depth[node] + 1;
            ancestor[nextnode][0] = node;
            maxedge[nextnode][0] = weight;
            dfs(nextnode);
        }
    }
}

void build_lca() {
    maxpow = ceil(log2(n));
    depth = vector<int>(n, 0);
    visited = vector<bool>(n, false);    
    ancestor = vector<vector<int>>(n, vector<int>(maxpow + 1, -1));
    maxedge = vector<vector<int>>(n, vector<int>(maxpow + 1, -1));    
    depth[0] = 0;
    dfs(0);

    for (int i = 1; i <= maxpow; ++i) {
        for (int j = 0; j < n; ++j) {
            int halfway = ancestor[j][i-1];
            if (halfway != -1) {
                ancestor[j][i] = ancestor[halfway][i-1];
                if (ancestor[j][i] != -1) {
                    maxedge[j][i] = max(maxedge[j][i-1], maxedge[halfway][i-1]);
                }
            }
        }
    }
}

pair<int, int> get_ancestor(int i, int k) {
    if (k >= n) return {-1, -1e9};

    int curr = i, maxweight = -1e9;
    for (int b = 0; b <= maxpow; ++b) {
        if ((1 << b) & k) {
            maxweight = max(maxweight, maxedge[curr][b]);
            curr = ancestor[curr][b];
        }

        if (curr == -1) return {-1, -1e9};
    }
    return {curr, maxweight};
}

int max_on_path(int a, int b) {
    pair<int, int> p{-1, -1e9};
    if (depth[a] > depth[b]) {
        int diff = depth[a] - depth[b];
        p = get_ancestor(a, diff);
        a = p.first;
    }
    if (depth[b] > depth[a]) {
        int diff = depth[b] - depth[a];
        p = get_ancestor(b, diff);
        b = p.first;
    }
    if (a == b) {
        return p.second;
    }

    for (int pow = maxpow; pow >= 0; --pow) {
        if (ancestor[a][pow] != ancestor[b][pow]) {
            p.second = max({p.second, maxedge[a][pow], maxedge[b][pow]});
            a = ancestor[a][pow];
            b = ancestor[b][pow];
        }
    }
    p.second = max({p.second, maxedge[a][0], maxedge[b][0]});
    return p.second;
}

void solve() {
    /*
    - read in edges
    - construct MST, getting both the final sum and constructing the adjacency list
    - using the adjacency list, do a DFS and get the LCA info
        - the parents info as well as the max edge weight on the path to those parents
    - now, for each edge, remove max edge from MST and add that edge, then output new sum
    */

    cin >> n >> m;
    vector<vector<int>> edges(m, vector<int>(3)), byweight(m, vector<int>(3));
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        --edges[i][0];
        --edges[i][1];
        byweight[i] = edges[i];
    }
    sort(byweight.begin(), byweight.end(), [] (vector<int> &v1, vector<int> &v2) {
        return v1[2] < v2[2];
    });

    DSU dsu(n);
    ll mst = 0;
    for (int i = 0; i < m; ++i) {
        int a = byweight[i][0], b = byweight[i][1], w = byweight[i][2];
        if (dsu.find(a) != dsu.find(b)) {
            dsu.join(a, b);
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
            // cout << "adding edge (" << a << ", " << b << ") with weight " << w << "\n";
            mst += w;
        }
    }

    build_lca();
    // for (int i = 0; i < n; ++i) {
    //     cout << "i="<<i<<":\n";
    //     print_container(ancestor[i], "\t ancestor: ");
    //     print_container(maxedge[i], "\t maxedge: ");
    // }

    for (int i = 0; i < m; ++i) {
        int a = edges[i][0], b = edges[i][1], w = edges[i][2];
        cout << mst - max_on_path(a, b) + w << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
