#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXN = 2e5 + 5, LOGMAXN = 18;
vector<pair<int, int>> adj[MAXN];
int n, m, q;
vector<int> depth;
int anc[MAXN][LOGMAXN+1], maxonpath[MAXN][LOGMAXN+1];

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
    for (int i = 1; i <= LOGMAXN; ++i) {
        int halfway = anc[node][i-1];
        if (halfway == -1) {
            anc[node][i] = -1;
            maxonpath[node][i] = maxonpath[node][i-1];
        } else {
            anc[node][i] = anc[halfway][i-1];
            maxonpath[node][i] = max(maxonpath[node][i-1], maxonpath[halfway][i-1]);
        }
    }

    // cout << "on node " << node << endl;
    for (auto next : adj[node]) {
        if (next.first == parent) continue;

        depth[next.first] = depth[node] + 1;
        anc[next.first][0] = node;
        maxonpath[next.first][0] = next.second;

        dfs(next.first, node);
    }
}

void build_lca() {
    depth = vector<int>(n, -1);
    depth[n-1] = 0;
    for (int i = 0; i < n; ++i) {
        fill(anc[i], anc[i] + LOGMAXN + 1, -1);
        fill(maxonpath[i], maxonpath[i] + LOGMAXN + 1, 0);
    }
    dfs(n-1, -1);
}

pair<int, int> jump(int node, int k) {
    if (k > depth[node]) return make_pair(-1, 0);

    int mx = 0;
    for (int i = 0; i <= LOGMAXN; ++i) {
        if ((1 << i) & k) {
            mx = max(mx, maxonpath[node][i]);
            node = anc[node][i];
        }
    }
    return make_pair(node, mx);
}

int getmax(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    int diff = depth[b] - depth[a];
    auto p = jump(b, diff);
    b = p.first;
    int mx = p.second;
    if (a == b) return mx;

    for (int i = LOGMAXN; i >= 0; --i) {
        if (anc[a][i] != anc[b][i]) {
            mx = max({mx, maxonpath[a][i], maxonpath[b][i]});
            a = anc[a][i];
            b = anc[b][i];
        }
    }
    mx = max({mx, maxonpath[a][0], maxonpath[b][0]});
    return mx;
}

void solve() {
    /*
    generalizable ideas for the future:
    - when representing objects in the situation in the problem, try representing it while showing
    all possible properties of that object. in this problem, it seems like we might be able to
    binary search on the edges for each query, but that's O(q * n * log(m)). however, if we draw
    out the graph such that the edges also show the time they were added (where the time is just
    based on the order in which they were added), then it becomes clear this is a "min of max on
    path across all paths" problem.
    - can join all the trees into a forest with edges of weight inf to a superroot node, so that if
    the LCA of two nodes is that superroot node, then they are not connected
    - what's the difference between setting the edge weights to [0, m-1] at the beginning and adding
    1 to the edge weights at the end, and setting the edge weights to [1, m] at the beginning? well,
    if every possible edge weight is properly transformed, then it's fine. however, there is an edge
    case that is not properly dealt with: a and b are equal. in that case, the output from getmax()
    is 0, but there is a difference between "max on path is 0 because there are no edges" and "max on
    path is 0 because the max edge weight is 0". so, we incorrectly apply the undo transformation at
    the end on both cases, when it should only be done on the second edge case. more generally, if
    we make some transformation to something at the beginning and undo it at the end, make sure that
    all possible inputs to the undoing went through the initial transformation. also, generally, if
    the same number can represent two different states, then make sure that both are dealt with properly.
    */

    cin >> n >> m >> q;
    ++n;
    DSU dsu(n);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (dsu.find(a) != dsu.find(b)) {
            dsu.join(a, b);
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        }
    }
    for (int i = 0; i < n-1; ++i) {
        if (dsu.find(n-1) != dsu.find(i)) {
            dsu.join(i, n-1);
            adj[i].push_back({n-1, 1e9});
            adj[n-1].push_back({i, 1e9});
        }
    }
    
    build_lca();

    while (q--) {
        int a, b;
        cin >> a >> b;
        --a; --b;

        int maxweight = getmax(a, b);
        cout << (maxweight == 1e9 ? -1 : maxweight) << endl;
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
