#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXN = 205;
const ll inf = 1e18;
struct Edge {
    int v;
    ll c, f, w;
    Edge *rev;
};
vector<Edge*> e[MAXN];
ll dis[MAXN], df[MAXN], inQ[MAXN];
int n;
Edge *pre[MAXN];
#define FOR(i,a,b) for(int i=int(a);i<=int(b);++i)
#define FORD(i,a,b) for(int i=int(a);i>=int(b);--i)
#define REP(i,n) FOR(i,0,(n)-1)

void addedge(int u, int v, int cap, int revcap, int w) {
    Edge *uv = new Edge(), *vu = new Edge();
    uv->v = v; vu->v = u;
    uv->c = cap; vu->c = revcap;
    uv->w = w; vu->w = -w;
    uv->rev = vu; vu->rev = uv;
    e[u].push_back(uv);
    e[v].push_back(vu);
}

ll cancelnegativecycles() {
    ll cost = 0;
    while (1) {
        // cout << "in loop" << endl;
        queue<int> q;
        REP(i, n) {
            q.push(i);
            inQ[i] = 1;
            dis[i] = inf;
        }
        
        int pc = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            REP(i, e[u].size()) {
                Edge *uv = e[u][i];
                int v = uv->v;
                ll c = uv->c, f = uv->f, w = uv->w;
                if (f < c && dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    pre[v] = uv;
                    if (inQ[v] < 0) {
                        q.push(v);
                        inQ[v] = -inQ[v] + 1;
                    }
                }
            }
            if (inQ[u] >= n) {
                pc = u;
                break;
            }
            inQ[u] = -inQ[u];
        }

        if (pc == -1) return cost;
        memset(inQ, 0, sizeof(inQ));
        int u = pc;
        while (1) {
            int v = u;
            if (++inQ[v] == 2) {
                pc = v; break;
            }
            Edge *uv = pre[v];
            u = uv->rev->v;
        }
        ll mi = inf;
        u = pc;
        do {
            int v = u;  
            Edge *uv = pre[v];
            u = uv->rev->v;
            mi = min(mi, uv->c - uv->f);
        } while (u != pc);
        u = pc;
        do {
            int v = u;
            Edge *uv = pre[v];
            u = uv->rev->v;
            uv->f += mi; uv->rev->f -= mi;
            cost += mi * uv->w;
        } while (u != pc);
    }
}

ll mincostmaxflow(int s, int t) {
    ll flow = 0, cost = 0;
    REP(u, n) REP(i, e[u].size()) e[u][i]->f = 0;

    cost = cancelnegativecycles();
    while (1) {
        memset(df, 0, sizeof(df));
        REP(u, n) dis[u] = inf;
        df[s] = inf; dis[s] = 0;
        queue<int> q;
        memset(inQ, 0, sizeof(inQ));
        q.push(s);
        inQ[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQ[u] = 0;
            REP(i, e[u].size()) {
                Edge *uv = e[u][i];
                int v = uv->v;
                ll c = uv->c, f = uv->f, w = uv->w;
                if (f < c && dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    pre[v] = uv;
                    df[v] = min(df[u], c - f);
                    if (!inQ[v]) q.push(v);
                }
            }
        }
        
        if (dis[t] == inf || df[t] == 0) break;
        flow += df[t]; cost += df[t] * dis[t];
        int u = t;
        while (u != s) {
            int v = u;
            Edge *uv = pre[v];
            u = uv->rev->v;
            uv->f += df[t]; uv->rev->f -= df[t];
        }
    }
    return cost;
}

struct Comp {
    bool operator()(const pair<int, ll> &p1, const pair<int, ll> &p2) {
        return p1.second > p2.second;
    }
};

vector<ll> dijkstras(int start, vector<vector<pair<int, ll>>> &adj) {
    int n = adj.size();
    vector<ll> dist(n, inf);
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, Comp> pq;
    pq.push(make_pair(start, 0));
    dist[start] = 0;
    while (pq.size()) {
        auto p = pq.top();
        pq.pop();
        int node = p.first;
        // cout << "node = " << node << endl;
        ll d = p.second;
        if (d > dist[node]) continue;

        for (auto next : adj[node]) {
            int nextnode = next.first;
            ll weight = next.second;
            if (dist[nextnode] > dist[node] + weight) {
                dist[nextnode] = dist[node] + weight;
                pq.push(make_pair(nextnode, dist[nextnode]));
            }
        }
    }
    return dist;
}

void solve() {
    /*
    - for each pair (p_i, w_j), we want to find the cost of moving all instances of p_i to w_j.
    how to do this? first, dijkstra's to find the shortest path from w_j to all other w_k. then,
    to get the cost for (p_i, w_j), we iterate over all warehouses w_k and increment the cost
    by (shortest_path_from_w_j[w_k]) * (p_i present at w_k).
    - once we get that, then we just make a complete biparite graph with products on left and
    warehouses on right, and find a max-cardinality (size m), min-cost matching. that's min-cost
    max-flow, with the edges having capacity 1 and cost equal to the previously found costs.
    */

    int n, m;
    cin >> n >> m;
    vector<vector<ll>> numat(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> numat[i][j];
        }
    }
    vector<vector<pair<int, ll>>> adj(n);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            ll dist;
            cin >> dist;
            if (dist != -1) {
                adj[j].push_back(make_pair(i, dist));
            }
        }
    }
    // cout << "got adj lists" << endl;

    vector<vector<ll>> dists(n);
    for (int i = 0; i < n; ++i) {
        dists[i] = dijkstras(i, adj);
    }
    // cout << "finished shortest paths" << endl;
    // cout << "dists\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         cout << dists[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vector<vector<ll>> weights(n, vector<ll>(m, 0));
    for (int w = 0; w < n; ++w) {
        for (int p = 0; p < m; ++p) {
            for (int wk = 0; wk < n; ++wk) {
                // crucial point: the instances of product p at w_k are moving from w_k to w,
                // not from w to w_k; be careful about the directions of edges IN THE CONTEXT
                // OF THE PROBLEM
                weights[w][p] += dists[wk][w] * numat[wk][p];
            }
        }
    }
    // cout << "weights:\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cout << weights[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    ::n = n + m + 2;
    int s = n+m, t = n+m+1;
    for (int w = 0; w < n; ++w) {
        for (int p = 0; p < m; ++p) {
            int idxw = w, idxp = p + n;
            addedge(idxw, idxp, 1, 0, weights[w][p]);
        }
    }
    for (int w = 0; w < n; ++w) addedge(s, w, 1, 0, 0);
    for (int p = n; p < n+m; ++p) addedge(p, t, 1, 0, 0);

    ll ans = mincostmaxflow(s, t);
    cout << ans << endl;
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
