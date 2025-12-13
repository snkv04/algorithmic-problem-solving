#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Edge {
    int a, b, w;

    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n;
vector<vector<int>> adj;
vector<vector<pair<int, int>>> adj2;
vector<priority_queue<Edge>> bestinsubtree;
vector<set<int>> nodesinsubtree;
vector<int> ans;
vector<int> depth;
vector<pair<int, int>> edges;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

struct DSU {
private:
    int n;
    vector<int> parent, size;

public:
    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        size = vector<int>(n, 1);
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            if (size[c] >= size[d]) {
                parent[d] = c;
                size[c] += size[d];
            } else {
                parent[c] = d;
                size[d] += size[c];
            }
        }
    }
};

void dfs(int node, int parent) {
    for (int next : adj[node]) {
        if (next == parent) continue;

        depth[next] = depth[node] + 1;
        dfs(next, node);

        // merge nodes in subtree
        if (nodesinsubtree[next].size() > nodesinsubtree[node].size()) {
            swap(nodesinsubtree[node], nodesinsubtree[next]);
        }
        for (int n : nodesinsubtree[next]) {
            nodesinsubtree[node].insert(n);
        }

        // merge best edges
        if (bestinsubtree[next].size() > bestinsubtree[node].size()) {
            swap(bestinsubtree[node], bestinsubtree[next]);
        }
        while (bestinsubtree[next].size()) {
            Edge e = bestinsubtree[next].top();
            bestinsubtree[next].pop();
            bestinsubtree[node].push(e);
        }
    }

    // push all edges in second graph adjacent to subtree's root
    for (auto e : adj2[node]) {
        bestinsubtree[node].push(Edge{node, e.first, e.second});
    }

    // remove all edges with both ends in the subtree
    while (
        bestinsubtree[node].size() &&
        nodesinsubtree[node].find(bestinsubtree[node].top().a) != nodesinsubtree[node].end() &&
        nodesinsubtree[node].find(bestinsubtree[node].top().b) != nodesinsubtree[node].end()
    ) {
        bestinsubtree[node].pop();
    }

    // update answer for subtree's root
    if (bestinsubtree[node].size()) {
        ans[node] = bestinsubtree[node].top().w;
    }
}

void solve() {
    ifstream cin("disrupt.in");
    ofstream cout("disrupt.out");

    int m;
    cin >> n >> m;
    adj.resize(n);
    adj2.resize(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back(make_pair(a, b));
    }
    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj2[a].push_back(make_pair(b, w));
        adj2[b].push_back(make_pair(a, w));
    }

    ans = vector<int>(n, -1);
    nodesinsubtree.resize(n); for (int i = 0; i < n; ++i) nodesinsubtree[i].insert(i);
    bestinsubtree.resize(n);
    depth = vector<int>(n, 0);
    dfs(0, -1);

    for (auto &e : edges) {
        int a = e.first, b = e.second;
        if (depth[a] < depth[b]) swap(a, b);
        cout << ans[a] << endl;
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
