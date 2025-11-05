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

void updatenummatchings(Dinics &d, int n, int nummatchings, int src) {
    for (Edge *edge : d.e[src]) {
        edge->c = nummatchings;
    }
    for (int i = n+1; i <= 2*n; ++i) {
        d.e[i][0]->c = nummatchings;
    }
}

void solve() {
    /*
    - if the problem were to ask us to compute the total number of maximum-cardinality matchings,
    then that would be in NP; one way would be to go through all possible matchings given the existing
    edges using backtracking (assigning the first node on the left, then the second node on the left,
    etc.), and another way would be to go through all possible matchings regardless of if there are
    edges (so, all permutations) and then check to see if the edges that are assumed to exist in the
    hypothetical matching actually exist. however, it says that the same person can't be matched to the same
    button across different matchings, which basically means that a single edge can't be used more
    than once, which lends itself more easily to a flow problem. even though this restriction seems
    like it complicates things a lot (going from finding all perfect matchings to all perfect
    matchings that also satisfy this hyper-specific condition), it actually simplifies things, because
    it puts the problem into a category of problems that can be solved (a little) more straightforwardly
    using a standard approach (max flow).
    - why not just have the edges from the source to the left partition have infinite capacity, so then
    we just push as much flow as possible and then take the answer to the the min flow across all edges
    from the source? if we do that, then we don't actually know if we're making a matching. by enforcing
    that each node on the left has incoming flow of k and each node on the right has outgoing flow of k,
    we can enforce that no node is used more than k times and then check to see that all nodes are used
    no less than k times, and then binary search on k to see the maximum number of matchings we can make
    such that all of them use different edges.

    generalizable ideas for the future:
    - in general, if we want matchings, then one additional restriction we need to place on the flow 
    network is that we need to restrict how many times each node is being used. if we want K different
    matchings (where it is imperative that no edge is used more than once), then each node (the edge
    from the src to the node) has a capacity of K, while each edge has a capacity of 1.
        - if we want to find the max K that this is true, we can't just give each node infinite capacity.
        we might not even get a matching this way. we need to binary search on K.
    - when repeatedly extracting edge-disjoint matchings, we need to be careful with how we remove edges.
    this involves checking:
        (1) both ends of the edge (is it connected to the source or sink? if so, don't remove it for the
        next matching)
        (2) the flow (if flow is 0, then wasn't used; if flow < 0, was used but is backward edge;
        if flow > 0, was used but is forward edge).
    - if we are binary searching on the maximum number of matchings we can get, then if we want the edges
    to reflect the changes from running max flow with that max nummatchings value, then it needs to be
    rerun after the binary search is over. this is because the last iteration of binary search (and therefore
    an iteration of running max flow) might have been done with a nummatchings value that is too high and
    unachievable.
    */

    int n;
    cin >> n;
    vector<string> grid(n); for (int i = 0; i < n; ++i) cin >> grid[i];
    
    // build graph connecting people to buttons
    Dinics dinics(2*n+2);
    auto person = [] (int node) { return node; };
    auto button = [&n] (int node) { return node + n; };
    int s = 0, t = 2*n+1;
    for (int i = 1; i <= n; ++i) {
        dinics.add_edge(s, person(i), 1); // capacity will get changed during binary search
        dinics.add_edge(button(i), t, 1); // capacity will get changed during binary search
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i-1][j-1] == 'Y') {
                dinics.add_edge(person(i), button(j), 1);
            }
        }
    }
    // for (int i = 0; i <= 2*n+1; ++i) {
    //     cout << "e["<<i<<"] = \n";
    //     for (Edge *e : dinics.e[i]) {
    //         cout << e << "\n";
    //     }
    // }

    // binary search to find max number of matchings where no edge is used more than once
    // using max flow
    int l = 1, r = n, k = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        
        updatenummatchings(dinics, n, m, s);
        int maxflow = dinics.run(s, t);

        // cout << "was checking " << m << ", maxflow was " << maxflow << endl;
        if (maxflow == m * n) {
            k = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    if (k == 0) {
        cout << "NO SCIENCE\n";
        return;
    }
    // cout << "k = " << k << "\n";

    // remove all irrelevant edges (as they might interfere when you're trying to get the matchings).
    // but first, rerun max flow for k
    updatenummatchings(dinics, n, k, s);
    dinics.run(s, t);
    for (int i = 0; i < 2*n+2; ++i) {
        for (Edge *edge : dinics.e[i]) {
            if (edge->f == 0) edge->c = 0;
        }
    }

    // extract each matching one-by-one
    vector<vector<int>> ans;
    for (Edge *edge : dinics.e[0]) {
        edge->c = 1;
    }
    for (int i = n+1; i <= 2*n; ++i) {
        dinics.e[i][0]->c = 1;
    }
    while (k--) {
        int maxflow = dinics.run(s, t); // resets all flow values to 0 before running
        assert(maxflow == n);
        vector<int> permutation;
        for (int i = 0; i <= 2*n+1; ++i) {
            for (Edge *edge : dinics.e[i]) {
                if (edge->f != 0 && i != s && i != t && (edge->v != s && edge->v != t)) {
                    // edge was used in matching and it should be removed
                    if (i >= n+1 && i <= 2*n) {
                        permutation.push_back(edge->v);
                    }
                    edge->c = 0;
                }
            }
        }
        ans.push_back(permutation);
    }

    // print out permutations (matchings)
    cout << ans.size() << endl;
    for (auto p : ans) {
        for (int i : p) cout << i << " ";
        cout << endl;
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
