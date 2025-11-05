#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

struct Edge {
    int v;
    ll c, f;
    Edge *rev;
};

ostream& operator<<(ostream &os, Edge *e) {
    os << "(v=" << e->v << ", c=" << e->c << ", f=" << e->f << ")";
    return os;
}

struct Dinics {
    static const int inf = 1e9, MAXN=1500;
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
    - if modeling something as a graph, be VERY CAREFUL about how the nodes are indexed. in some
    graphs, the left nodes are 1-n, right nodes are n+1-2n, s=0, and t=2n+1. in this case, i made
    s=0, t=2n+1, left nodes = {1, 3, ..., 2n-1}, rightnodes = {2, 4, ..., 2n}. write these things
    down so that i keep track of them and don't induce any bugs for a reason like this.
    - also, just generally for flow problems, be careful about the start index, end index, and chosen
    capacity for each edge.
    */

    int n, k;
    cin >> n >> k;
    vector<vector<int>> grid(k, vector<int>(n));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            --grid[i][j];
        }
    }

    // validate first k rows
    vector<set<int>> colavail(n), rowavail(k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            colavail[j].insert(i);
            if (i < k) rowavail[i].insert(j);
        }
    }
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            colavail[j].erase(grid[i][j]);
            rowavail[i].erase(grid[i][j]);
        }
    }
    for (int i = 0; i < k; ++i) {
        if (rowavail[i].size()) {
            cout << "no\n";
            return;
        }
    }
    for (int j = 0; j < n; ++j) {
        if (colavail[j].size() != n-k) {
            cout << "no\n";
            return;
        }
    }
    
    // build graph connecting columns to values
    int matchings = n - k;
    Dinics dinics(2*n+2);
    int s = 0, t = 2*n+1;
    auto left = [] (int node) { return 2*node+1; };
    auto right = [] (int node) { return 2*node+2; };
    for (int i = 0; i < n; ++i) {
        dinics.add_edge(s, left(i), 1);
        dinics.add_edge(right(i), t, 1);
    }
    for (int col = 0; col < n; ++col) {
        for (int val = 0; val < n; ++val) {
            if (colavail[col].find(val) != colavail[col].end()) {
                dinics.add_edge(left(col), right(val), 1);
            }
        }
    }
    // for (int i = 0; i <= 2*n+1; ++i) {
    //     cout << "e["<<i<<"] = \n";
    //     for (Edge *e : dinics.e[i]) {
    //         cout << e << "\n";
    //     }
    // }

    // extract each matching one-by-one
    vector<vector<int>> ans;
    while (matchings--) {
        int maxflow = dinics.run(s, t); // resets all flow values to 0 before running
        assert(maxflow == n);
        vector<int> row;
        for (int i = 0; i <= 2*n+1; ++i) {
            for (Edge *edge : dinics.e[i]) {
                if (edge->f != 0 && i != s && i != t && edge->v != s && edge->v != t) {
                    // edge was used in matching and it should be removed
                    if (i >= 1 && i <= 2*n && i % 2) { // edge is coming from left and going to right
                        // cout << "column " << (i+1)/2 << " matched to " << edge->v/2 << "\n";
                        row.push_back(edge->v/2);
                    }
                    edge->c = 0;
                }
            }
        }
        ans.push_back(row);
    }

    // print out final grid
    cout << "yes\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < k) {
                cout << grid[i][j] + 1 << " ";
            } else {
                cout << ans[i-k][j] << " ";
            }
        }
        cout << "\n";
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
