#include <bits/stdc++.h>
using namespace std;

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

bool bfs_level(int s, int t) {
    dep = vector<int>(n, -1);
    e1 = vector<vector<Edge*>>(n);
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
    /*
    - what's an intuitive solution using flow? construct the graph with directed edges (each undirected
    edge (a, b) places an edge from a->b and b->a) with capacity 10000, add edges with capacity 10000
    from a source to each node, add edges with capacity 10000 from each node to the sink, and run max-flow.
    what's the problem with this? imagine that all of the nodes are lined up vertically, and the source goes
    to each and each goes to the sink. then it's possible that the flow just skips all of the graph's edges
    and directly goes from the source to each node then to the sink.
    how to avoid this problem? make two lines of vertices. one contains a version of each node with all their
    outgoing edges (lined up on the left), and another contains a version of each node with all their incoming
    edges (lined up on the right). source goes to left line, sink comes from right line; this forces the flow
    to go through the edges. since each node on the left has an incoming flow of 10000 and each on the right
    has an outgoing of 10000, if we can get a maxflow of 10000*n, then one of the conditions in the problem
    (every node pushes out 10000) is met.
    the other condition, namely that every edge must flow the same in both directions, needs to also be met.
    it isn't stated in the problem, but every node must also have an inflow of 10000, because if its adjacent
    edges have an outflow sum of 10000 but every edge flows the same in both directions, then its inflow sum
    is equal. however, does this guarantee that every edge flows the same in both directions? the answer is
    that it doesn't matter at all. if we can get the flow condition (i.e., maxflow == 10,000 * n), then we
    can just take every edge, cut its flow in half, and assign half the flow forward and half of it backward.
    this maintains both conditions; its inflow and outflow both decrease by 5000 and increase by 5000, so the
    condition of 10000 is met, and the condition of each edge in the original graph having equal flow in
    both directions is met because the two directed edges a->b and b->a that form the original edge (a, b)
    both have equal forward and backward flow. most of the time, the maxflow will result in the edges looking
    like a matching (every edge either having 10,000 flow or 0), but it doesn't matter if this happens or not.

    generalizable ideas:
    - can make an undirected graph into a flow graph by duplicating every vertex and adding the two directed
    edges (both directions of the undirected edge) only from the left group to the right group
        - in other contexts and this one, can separate out nodes into one copy only used for incoming edges
        and one copy only used for outgoing edges, where the former has a single outgoing and the latter has
        a single incoming
    - if every node has equal inflow and outflow, where all the edges are bidirectional (so flow can go either
    way), then it is guaranteed that we can make every edge also have equal flow both directions; for each edge
    (i, j), we just have to take the original flow i->j and split it evenly in both directions and then do the
    same for the flow in the j->i direction. this maintains the condition that every node has equal inflow and
    outflow.
    */

    int num_nodes, m;
    cin >> num_nodes >> m;
    n = 2 * num_nodes + 2;
    e.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b + num_nodes, 10000);
        add_edge(b, a + num_nodes, 10000);
    }
    for (int i = 1; i <= num_nodes; ++i) {
        add_edge(0, i, 10000);
        add_edge(i+num_nodes, n-1, 10000);
    }

    int maxflow = dinic(0, n-1);
    // cout << "maxflow = " << maxflow << "\n";
    if (maxflow != 10000 * num_nodes) {
        cout << "-1\n";
        return;
    }

    vector<vector<int>> adj(num_nodes+1, vector<int>(num_nodes+1, 0));
    for (int i = 1; i <= num_nodes; ++i) {
        for (Edge *edge : e[i]) {
            int j = edge->v;
            int flow = edge->flow;
            if (flow > 0) {
                adj[i][j-num_nodes] += edge->flow / 2;
                adj[j-num_nodes][i] += edge->flow / 2;
            }
        }
    }
    
    for (int i = 1; i <= num_nodes; ++i) {
        for (int j = 1; j <= num_nodes; ++j) {
            cout << adj[i][j] << " ";
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
