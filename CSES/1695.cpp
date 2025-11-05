#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

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
        vector<ll> result(2);
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
            parent[d] = c;
            size[c] += size[d];
        }
    }
};

struct Edge {
    int v;
    ll c, f;
    Edge *rev;
};

struct Dinics {
    static const int inf = 1e9, MAXN=1005;
    int n;
    vector<Edge*> e[MAXN], e1[MAXN];
    int dep[MAXN];
    bool mark[MAXN];

    Dinics(int n) : n(n) {}
    
    bool bfs_level(int s, int t) {
        fill(dep, dep+n, -1);
        for (int u = 0; u < n; ++u) {
            e1[u].clear();
        }
        queue<int> q;
        q.push(s);
        dep[s] = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            if (u == t) return 1;

            for (int i = 0; i < e[u].size(); ++i) {
                Edge *uv = e[u][i];
                int v = uv->v;
                ll c = uv->c, f = uv->f;
                if (f < c) {
                    if (dep[v] == -1) {
                        dep[v] = dep[u] + 1;
                        q.push(v);
                    }
                    if (dep[v] == dep[u]+ 1) {
                        e1[u].push_back(uv);
                    }
                }
            }
        }
        return 0;
    }

    ll dfs_flow(int u, int t, ll dt) {
        if (u == t) return dt;
        ll tot = 0;
        for (int i = 0; i < e1[u].size(); ++i) {
            Edge *uv = e1[u][i];
            int v = uv->v;
            ll c = uv->c, f = uv->f;
            if (!mark[v] && f < c) {
                ll vdt = dfs_flow(v, t, min(c-f, dt-tot));
                if (vdt > 0) {
                    uv->f += vdt;
                    uv->rev->f -= vdt;
                    tot += vdt;
                }
            }
        }
        
        if (tot == 0) mark[u] = 1;
        return tot;
    }

    ll run(int s, int t) {
        for (int u = 0; u < n; ++u) {
            for (int i = 0; i < e[u].size(); ++i) {
                e[u][i]->f = 0;
            }
        }

        ll res = 0;
        while (bfs_level(s, t)) {
            fill(mark, mark+n, false);
            res += dfs_flow(s, t, inf);
        }
        return res;
    }

    void add_edge(int u, int v, ll c) {
        Edge *edge = new Edge{v, c, 0, nullptr};
        Edge *rev = new Edge{u, 0, 0, edge};
        edge->rev = rev;
        e[u].push_back(edge);
        e[v].push_back(rev);
    }
};

void solve() {
    /*
    generalizable ideas for the future:
    - why split each node into one that deals with all incoming edges and one that deals with all
    outgoing edges? that might just be convention for undirected graphs, so that the forward and
    backward edge don't literally go back and forth between the same node. if we want to restrict
    the number of times a vertex is used, then that's another reason, but that doesn't apply here.
    - if we want to cut off nodes in C from nodes in D, then our source gets connected to C and our
    sink gets connected to D. in this problem, C is just {1} and D is just {N}.
    - the ONLY way to get to out(node) is through in(node). we make sure of that. in this case, the
    edges from in(node) to out(node) are infinite capacity, so if one is reachable then the other always
    is. in other problems, these edges can be finite capacity, so in(node) is reachable while out(node)
    isn't. however, one (possibly) important observation is that if out(node) is reachable, then it
    can only have come from in(node). this is common sense, but it's worth noting.
        - as a result, in the final edge check in this problem where we want to see if edge (u, v)
        goes from in S to out of S, we can just use in() (and not out()) for both u and v.
    */

    int n, m;
    cin >> n >> m;

    auto in = [] (int node) { return 2*node-1; };
    auto out = [] (int node) { return 2*node; };
    int s = 0, t = 2*n+1;
    Dinics dinics(2*n+2);
    for (int i = 1; i <= n; ++i) {
        dinics.add_edge(in(i), out(i), Dinics::inf);
    }
    dinics.add_edge(s, in(1), Dinics::inf);
    dinics.add_edge(out(n), t, Dinics::inf);

    vector<pair<int, int>> edges;
    while (m--) {
        int u, v;
        cin >> u >> v;
        dinics.add_edge(out(u), in(v), 1);
        dinics.add_edge(out(v), in(u), 1);
        edges.push_back(make_pair(u, v));
    }
    dinics.run(s, t);

    // find all reachable nodes (which we call set S)
    set<int> S;
    S.insert(0);
    stack<int> stk;
    stk.push(0);
    while (stk.size()) {
        int node = stk.top();
        stk.pop();
        S.insert(node);
        
        for (Edge *edge : dinics.e[node]) {
            if (S.find(edge->v) == S.end() && edge->f < edge->c) {
                stk.push(edge->v);
            }
        }
    }
    S.erase(0);
    // print_container(S, "S = ");

    // get all edges going between S and T
    vector<pair<int, int>> ans;
    for (auto e : edges) {
        if (
            S.find(in(e.first)) != S.end() && S.find(in(e.second)) == S.end() ||
            S.find(in(e.second)) != S.end() && S.find(in(e.first)) == S.end()
        ) {
            ans.push_back(e);
        }
    }
    cout << ans.size() << "\n";
    for (auto e : ans) cout << e.first << " " << e.second << "\n";
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
