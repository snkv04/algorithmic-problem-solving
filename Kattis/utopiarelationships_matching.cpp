#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1005;
int nx, ny, e[MAXN][MAXN], cx[MAXN], vy[MAXN];

int path(int u) {
    for (int v = 0; v < ny; ++v) {
        if (e[u][v] && !vy[v]) {
            vy[v] = 1;
            if (cx[v] == -1 || path(cx[v])) {
                cx[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int maximum_match() {
    int match = 0;
    for (int i = 0; i < ny; ++i) cx[i] = -1;
    for (int i = 0; i < nx; ++i) {
        memset(vy, 0, sizeof(vy));
        match += path(i);
    }
    return match;
}

void solve() {
    /*
    - we can clearly make the observation that a graph that can be broken down into cliques have a solution.
    going even simpler, if a graph can be decomposed into node-disjoint cycles, then there is a solution,
    as we can ignore all other edges and evenly distribute flow among those edges in the cycles.
    - our goal is basically to separate the graph into cycles, where a single edge between nodes is counted
    as a cycle. why is this a good idea?
    first of all, it's clear that if this is possible, then we can construct a solution to the problem: each
    node has a vertex to the left and to the right, so it just pushes and receives 5000 flow to each. in the
    case that nodes A and B are the only two nodes in a cycle, this same exact logic applies, and the edge
    just ends up summing to 10000 in both directions.
    now, how do we show that there aren't any graphs with solutions to the problem that can't be broken into
    cycles like this? this is the same claim we wanted to prove during the contest. we can show that if a
    graph has a solution to the problem, then it can be partitioned into node-disjoint cycles. a high-level
    (not rigorous) proof: for a node i, if it distributes 3000 flow to node j, then both node i and node j
    need to distribute 7000 flow elsewhere. regardless of if node j puts that 7000 flow onto 1 node, 2 nodes,
    or k nodes, that unbalance of flow will propagate through the nodes it connects to. at the end, it needs
    to connect back to node i, whose remaining flow to distribute will match that of the node at the end
    of the chain. this circular chain might involve other nodes, but there's never a dead end, so it can be
    simplified into a cycle.
    - now, how to actually find if a graph can be decomposed into cycles like this? split each node into a
    "left" version of the node and a "right" version of the node. in a cycle, each node has two adjacent
    nodes, so this can be seen as the node's left side matching to another node's right side and the node's
    right side matching to another node's left side. so, we can just check to see if there's a perfect
    matching on this new (bipartite) graph, and if there is, then each edge just needs to have 5000 flow added
    to both directions of that edge.

    generalizable ideas:
    - cycles can be found by checking for perfect matchings in the corresponding bipartite graph with
    duplicated vertices
        - in general, a cycle needs at least 3 vertices in an undirected graph and 2 vertices in a directed
        graph. but if we make the undirected graph into a directed one, then 2 vertices is fine, and in the
        context of this problem, making that transformation is acceptable. in fact, to be technical, if we
        only look at the directed graph (which, again, is acceptable for this problem, since a single edge
        between two nodes can constitute both of those nodes' outward flow, and the INITIAL goal isn't to
        create length>=3-cycles in the undirected graph), when there are only 2 nodes in the undirected
        original graph, there are 4 nodes in the directed bipartite graph (because R_i can be thought to have
        an implicit edge to L_i); regardless, this is unimportant, since 2 vertices is enough in a directed
        graph.
    - find the simplest possible condition that, based on some examples, seems to match the condition in
    the problem, and see if they can be proven to be equivalent.
    */

    int n, m;
    cin >> n >> m;
    nx = ny = n;
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        e[a][b] = e[b][a] = 1;
    }

    int maxmatch = maximum_match();
    if (maxmatch != n) {
        cout << "-1\n";
        return;
    }

    vector<vector<int>> adj(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cx[j] == i) {
                adj[i][j] += 5000;
                adj[j][i] += 5000;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
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
