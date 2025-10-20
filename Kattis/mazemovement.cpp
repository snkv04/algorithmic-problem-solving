#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

struct Edge {
    int v, cap, flow;
    Edge *rev;
};

vector<vector<Edge*>> e, e1;
vector<int> dep;
vector<bool> mark;
constexpr int inf = 2e9;
int n;

void add_edge(int a, int b, int c) {
    Edge *edge = new Edge{b, c, 0, nullptr};
    Edge *reverse = new Edge{a, 0, 0, edge};
    edge->rev = reverse;
    e[a].push_back(edge);
    e[b].push_back(reverse);
}

int gcd(int a, int b) {
    int A = max(a, b), B = min(a, b);
    while (B != 0) {
        int R = A % B;
        A = B;
        B = R;
    }
    return A;
}

bool bfs_level(int s, int t) {
    dep = vector<int>(n, -1);
    for (int i = 0; i < n; ++i) e1[i].clear();
    queue<int> q;
    q.push(s);
    dep[s] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        if (u == t) return 1;
        
        for (int i = 0; i < e[u].size(); ++i) {
            Edge *uv = e[u][i];
            int v = uv->v, cap = uv->cap, flow = uv->flow;
            if (flow < cap) {
                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }

                if (dep[v] == dep[u] + 1) {
                    e1[u].push_back(uv);
                }
            }
        }
    }
    return 0;
}

int dfs_flow(int u, int t, int dt) {
    if (u == t) return dt;

    int tot = 0;
    for (int i = 0; i < e1[u].size(); ++i) {
        Edge *uv = e1[u][i];
        int v = uv->v, cap = uv->cap, flow = uv->flow;
        if (!mark[v] && flow < cap) {
            int vdt = dfs_flow(v, t, min(cap-flow, dt - tot));
            if (vdt > 0) {
                uv->flow += vdt;
                uv->rev->flow -= vdt;
                tot += vdt;
            }
        }
    }

    if (tot == 0) mark[u] = 1;
    return tot;
}

int dinic(int s, int t) {
    for (int u = 0; u < n; ++u) {
        for (int i =  0; i < e[u].size(); ++i) {
            e[u][i]->flow = 0;
        }
    }
    
    int res = 0;
    while (bfs_level(s, t)) {
        mark = vector<bool>(n, 0);
        res += dfs_flow(s, t, inf);
    }
    return res;
}

void solve() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int s = 0, t = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[s]) {
            s = i;
        }
        if (a[i] > a[t]) {
            t = i;
        }
    }
    // cout << "s = " << s << ", t = " << t << "\n";

    e = vector<vector<Edge*>>(n);
    e1 = vector<vector<Edge*>>(n);
    mark = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int g = gcd(a[i], a[j]);
            if (g > 1) {
                add_edge(i, j, g);
                add_edge(j, i, g);
            }
        }
    }

    int maxflow = dinic(s, t);
    cout << maxflow << "\n";
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
