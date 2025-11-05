#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

struct Edge {
    int v;
    ll c, f;
    Edge *rev;
};

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
    solution:
    - binary search on the maximum balance that we have on each sphere. the final answer is equal to the total number
    of discs minus the number of spheres times the binary-searched max balance.
    - for a given balance value B, we can check if it works as follows. we want to be able to spread B flow from each sphere
    across the edges adjacent to it, such that each edge does not get used more times than the number of discs on it. to enforce
    the idea that each edge only gets used d_i times, we can split each edge into two nodes and have an edge with capacity d_i
    connecting them. since the flow from each node doesn't actually get sent to the sphere on the other end, just to the edge
    (since the node is just placing discs on the side of the edge closer to it), we are literally, put simply, sending flow from
    the nodes TO the edges in the original graph (not through them). that's why we treat edges as nodes here. the edges get connected
    to the sink with infinite capacity, and the nodes (spheres) get connected to the edges (edges with discs) with infinite
    capacity. the thing that is bounded is the amount that each sphere puts out, which is B for all spheres. this value of B
    will not work if we can't send B flow; otherwise, it will.
    */

    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> edges;
    int discsum = 0;
    for (int i = 0; i < m; ++i) {
        int s1, s2, d;
        cin >> s1 >> s2 >> d;
        edges.push_back(array<int, 3>({s1, s2, d}));
        discsum += d;
    }

    int l = 0, r = 5e6, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;

        // Dinics d(2*n + 2*m + 2);
        // int src = 0, sink = 2*n+2*m+1;
        // auto in = [] (int idx) { return idx; };
        // auto out = [&n] (int idx) { return idx + n; };
        // for (int i = 2*n+1; i <= 2*n+m; ++i) {
        //     array<int, 3> edge = edges[i-2*n-1];
        //     int s1 = edge[0], s2 = edge[1], discs = edge[2];
        //     int l = i, r = i+m;
        //     d.add_edge(l, r, discs);
        //     d.add_edge(in(s1), l, Dinics::inf);
        //     d.add_edge(in(s2), l, Dinics::inf);
        //     d.add_edge(r, out(s1), Dinics::inf);
        //     d.add_edge(r, out(s2), Dinics::inf);
        // }
        // for (int i = 1; i <= n; ++i) {
        //     d.add_edge(src, in(i), mid);
        //     d.add_edge(out(i), sink, Dinics::inf);
        // }
        // ll flow = d.run(src, sink);

        Dinics d(n + 2*m + 2);
        int src = 0, sink = n+2*m+1;
        for (int i = n+1; i <= n+m; ++i) {
            array<int, 3> edge = edges[i-n-1];
            int s1 = edge[0], s2 = edge[1], discs = edge[2];
            int l = i, r = i+m;
            d.add_edge(l, r, discs);
            d.add_edge(s1, l, Dinics::inf);
            d.add_edge(s2, l, Dinics::inf);
            d.add_edge(r, sink, Dinics::inf);
        }
        for (int i = 1; i <= n; ++i) {
            d.add_edge(src, i, mid);
        }
        ll flow = d.run(src, sink);

        if (flow == mid * n) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << (discsum - n * ans) << endl;
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
