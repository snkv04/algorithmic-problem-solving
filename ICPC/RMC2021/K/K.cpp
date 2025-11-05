#include <bits/stdc++.h>
using namespace std;

int n, m;
string origteam, finalteam, prefs;
vector<set<int>> adj;
struct Edge {
    int v, c, f;
    Edge *rev;
};
const int inf = 1 << 28, MAXN = 2005;
vector<Edge*> e[MAXN], e1[MAXN];
int dep[MAXN];
bool mark[MAXN];
vector<bool> issue;

bool bfs_level(int s, int t) {
    fill(dep, dep+n+2, -1);
    for (int u = 0; u < n+2; ++u) {
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
            int v = uv->v, c = uv->c, f = uv->f;
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

int dfs_flow(int u, int t, int dt) {
    if (u == t) return dt;
    int tot = 0;
    for (int i = 0; i < e1[u].size(); ++i) {
        Edge *uv = e1[u][i];
        int v = uv->v, c = uv->c, f = uv->f;
        if (!mark[v] && f < c) {
            int vdt = dfs_flow(v, t, min(c-f, dt-tot));
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

int dinic(int s, int t) {
    for (int u = 0; u < n; ++u) {
        for (int i = 0; i < e[u].size(); ++i) {
            e[u][i]->f = 0;
        }
    }

    int res = 0;
    while (bfs_level(s, t)) {
        fill(mark, mark+n+2, false);
        res += dfs_flow(s, t, inf);
    }
    return res;
}

void add_edge(int u, int v, int c) {
    Edge *edge = new Edge{v, c, 0, nullptr};
    Edge *rev = new Edge{u, 0, 0, edge};
    edge->rev = rev;
    e[u].push_back(edge);
    e[v].push_back(rev);
    // cout << "added edge from " << u << " to " << v << " with " << c << " capacity\n";
}

//

void dfs(int node, vector<bool> &vis, set<int> &S) {
    vis[node] = true;
    S.insert(node);
    for (Edge *edge : e[node]) {
        if (issue[edge->v] && edge->f < edge->c && !vis[edge->v]) {
            dfs(edge->v, vis, S);
        }
    }
}

void setteams(int node, vector<bool> &vis) {
    vis[node] = true;
    for (int next : adj[node]) {
        if (!vis[next] && finalteam[next] != 'X') {
            if (finalteam[next] == '?') {
                finalteam[next] = finalteam[node] == 'A' ? 'B' : 'A';
            }
            setteams(next, vis);
        }
    }
}

void old() {
    cin >> n >> m;
    cin >> origteam >> prefs;
    issue = vector<bool>(n+2, false);

    // fill in edges
    adj = vector<set<int>>(n);
    fill(e, e+n+2, vector<Edge*>());
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].insert(b);
        adj[b].insert(a);
        if (prefs[a] != '?' && prefs[a] == prefs[b]) {
            add_edge(a, b, 1);
            add_edge(b, a, 1);
            issue[a] = issue[b] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!issue[i]) continue;

        if (origteam[i] == 'A') {
            add_edge(n, i, 1);
        } else {
            add_edge(i, n+1, 1);
        }
    }
    int maxflow = dinic(n, n+1);
    // for (int i = 0; i < n+2; ++i) {
    //     cout << "edges[" << i << "]:\n";
    //     for (Edge *edge : e[i]) {
    //         cout << "\tto " << edge->v << " with c="<<edge->c << " and f="<<edge->f << "\n";
    //     }
    // }
    // cout << "max flow = " << maxflow << endl;

    // get min cut in issue graph
    vector<bool> vis(n+2, false);
    set<int> S;
    dfs(n, vis, S); // dfs from source
    // cout << "S: "; for (int v : S) cout << v << " "; cout << endl;
    S.erase(n);

    // get vertex cover in issue graph
    set<int> as, at, bs, bt;
    for (int i = 0; i < n; ++i) {
        if (issue[i] == false) continue;

        if (origteam[i] == 'A') {
            if (S.find(i) != S.end()) {
                as.insert(i);
            } else {
                at.insert(i);
            }
        } else if (origteam[i] == 'B') {
            if (S.find(i) != S.end()) {
                bs.insert(i);
            } else {
                bt.insert(i);
            }
        }
    }

    // remove vertex cover nodes
    set<int> cover;
    if (at.size() + bs.size() <= as.size() + bt.size()) {
        for (int i : at) if (issue[i]) cover.insert(i);
        for (int i : bs) if (issue[i]) cover.insert(i);
    } else {
        for (int i : as) if (issue[i]) cover.insert(i);
        for (int i : bt) if (issue[i]) cover.insert(i);
    }
    // cout << "cover: "; for (int v : cover) cout << v << " "; cout << endl;
    // cout << "cover size = " << cover.size() << endl;
    for (int i = 0; i < n; ++i) {
        if (cover.find(i) != cover.end()) {
            adj[i].clear();
        } else {
            set<int> newadj;
            for (int j : adj[i]) {
                if (cover.find(j) == cover.end()) {
                    newadj.insert(j);
                }
            }
            adj[i] = newadj;
        }
    }

    // construct teams by filling in all nodes with a preference of "?"
    finalteam = string(n, '?');
    for (int i = 0; i < n; ++i) {
        if (cover.find(i) != cover.end()) {
            finalteam[i] = 'X';
        } else {
            if (prefs[i] != '?') {
                finalteam[i] = prefs[i];
            }
        }
    }
    vis = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        if (finalteam[i] != '?' && finalteam[i] != 'X' && !vis[i]) {
            setteams(i, vis);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (finalteam[i] == '?') {
            finalteam[i] = 'A';
            setteams(i, vis);
        }
    }
    cout << finalteam << endl;

    // // checking my own output
    // string finalteam = "AABBABBAAAAABBABBAABBAAABBBBAAABBBBABBAAAAAABABBBBAABABAAABBBBABBABABAABAAAABABAABAABAAAABABABAAAAAAXBBXXXXAXXXABXXXAXXXXAXBXXBBBXBAXABAXXXAXXXBXXBAXXAXXBBBXXXXAXXAXXXXXXAXAXXBXXBXXXXBAAXXAXAXXXXXXXXB";
    // while (m--) {
    //     int a, b;
    //     cin >> a >> b;
    //     if (finalteam[a] != 'X' && finalteam[a] == finalteam[b]) {
    //         cout << "ERROR: index " << a << " is " << finalteam[a] << " while index " << b << " is also " << finalteam[b] << endl;
    //     }
    // }
}

//

void solve() {
    /*
    - a "problematic edge" is one which, under the new team configuration (which we want to construct),
    connects two nodes who are on the same team. our goal in this problem is to remove the minimum number
    of vertices such that, by also removing the edges adjacent to those vertices, it is possible to assign
    teams to the remaining vertices without having any problematic edges.
        - my previous attempts were wrong becaues it only looked at problematic edges that were present
        assuming that the preferences (outside of "?") were the new team assignments, and then removed
        the minimum vertices to get rid of all such edges. however, in a case like:
            - player 1 is on team B and wants to be on A
            - player 2 is on team A and doesn't have a preference
            - player 3 is on team B and wants to be on B
            - 1 has a rivalry with 2, and 2 has a rivalry with 3
        no problematic edges would be returned, but we clearly need to remove at least one vertex.

    - we could partition the vertices by their current teams, A and B. however, all edges will be going
    between A and B. no information is gained. we could partition the vertices by their preferred teams,
    A, B, and ?. then, what we want after removing vertices is for there to be no edges such that they
    connect two nodes with the same team (after ?s get filled in), but edges between nodes that prefer
    different teams are perfectly fine. however, it's hard to apply a standard algorithm for this. another
    partition is to group nodes by must switch, must not switch, and ?. in this partition, we want to remove
    nodes so that in the resulting graph, edges within the same group are fine but edges that cross groups
    are not fine. we can do this by finding a min cut, and that's the reason why this partition is good.
    - how to do this? we want to cut off edges that go between different groups BY DELETING VERTICES.
    not just that, we want to make sure that the two groups aren't connected at all, even if through
    a "?" node. so, to do this, connect one group to a source, and the second group to a sink (so the
    third group is connected to neither). those edges should have infinite capacity. the undirected edges
    given in the input are also placed into the flow graph with infinite capacity. however, the edges
    going from each vertex's "in" copy to its "out" copy are finite, so that the cut only consists of
    these edges. this way, we know which vertices to effectively remove.

    solution:
    - our goal is to remove some nodes so that the remaining ones can be assigned teams with no edges
    being in the same team.
    - we can reframe this so that our goal is to remove some nodes so that the remaining ones can be
    assigned teams with no edges crossing from the (must change) and (must not change) group. all this
    does is change where the edges aren't allowed to be.
    - we also want to remove the minimum number of nodes. this is similar to the minimum cut problem,
    with a slight difference. in the context of maxflow, minimum cut always refers to choosing some
    groups S and T so that all edges crossing between S and T have minimum capacity sum. if we want to
    change it so that we are cutting vertices and not edges, we can force it to be the case that all
    edges in between S and T are those corresponding to vertices (meaning we split vertices into 2 nodes
    and the edges between them are the only ones present in the cut). we do this by making all of those
    edges have finite capacity and all others have infinite capacity.
        - why does this work? if all flow must cross through finite-capacity edges to get to the sink,
        then the maxflow can only be finite. therefore, the minimum cut is finite. therefore, the only
        edges involved in the minimum cut are finite, which are the ones we chose to be finite. we just
        have to make sure that all flow must go through the finite-capacity edges.
    - therefore, the reframing of the graph is as follows: split each node into: one that takes all
    incoming edges and one that sends out all outgoing edges. connect the source to all "in" nodes
    in one group, and connecting all "out" nodes in the other group to the sink (some nodes are never
    connected to the source or the sink directly). those edges have infinite weight. also, all edges
    in the original graph should be added to the new graph, except it's undirected so both sides get
    added. these also have infinite capacity. now, the "in" nodes are connected to the "out" nodes
    with capacity 1.
    - this way, the minimum cut literally determines the minimum number of vertices to remove so that
    the source nodes are separate from the sink nodes. once we have this, then we know which vertices
    to cut, because their in() nodes are reachable while their out() nodes aren't.
    - those we cut have a final team of "X". the nodes that are reachable (in S) and aren't cut mean
    that they were in the first group, so their team doesn't change. the nodes that aren't cut and
    aren't reachable are in the second group, so their team does change.

    generalizable ideas for the future:
    - infinite capacity edges can't be in the min cut, while finite capacity edges can.
    - the standard edge-disjoint paths problem can be solved with max flow, since we just want to enforce
    the restriction that each edge is used once. for vertex-disjoint paths, we want to make each vertex
    get used once, so we make every possible flow path pass through an edge representing each vertex, and
    enforce the restriction through its capacity. the situation here is similar. for cutting the minimum
    number of edges to separate one group from another, we literally just find a minimum cut. for cutting
    the minimum number of vertices to separate one group from another, we force all paths to go through
    edges that connect one copy of each vertex to its other copy, and then enforce a restriction on those
    edges, while all other edges are left with infinite capacity. in simplest terms, this problem is a
    "min vertex cut" problem.
        - in general, max flow is used for "most that we can push from A to B" problems, while min cut is
        used for "minimum that we need to remove to separate A from B" problems.
        - in a bipartite graph (which isn't the case for this problem, because even though the original
        graph in this problem is bipartite, the network flow graph that we formulate it as in order to
        find the min cut is not bipartite), the min cut gives you a vertex cover for free. each of the
        edges in the min cut correspond to a vertex, so all of those vertices (A_T U B_S) can be removed,
        which means that no flow is pushed from s to t. since src connects to A and B connects to sink,
        if nothing connects src to sink, then nothing connects A to B, which (in the bipartite graph)
        means that all edges have been removed.
    - even though we are given a bipartite graph, which is deceiving, we can reformulate the graph as
    one set that we want to disconnect from another set, and then the problem is just min cut.
        - if the two sets unioned DID equal the full set of vertices, then we could do a bipartite graph
        vertex cover (which is derived from a min cut anyway, so actually this general solution works
        anyway). it doesn't, though, so we have to do the min cut solution.
    - when using this dinics implementation, make sure to update the n from dinics with the proper value
    (which might take into consideration the doubling of nodes or adding a src and sink).
    */

    // old();

    int n, m;
    cin >> n >> m >> origteam >> prefs;
    int s = 0, t = 2*n+1;
    ::n = 2 * n + 2;
    auto in = [] (int node) { return 2*node-1; };
    auto out = [] (int node) { return 2*node; };
    while (m--) {
        int i, j;
        cin >> i >> j;
        add_edge(out(i), in(j), inf);
        add_edge(out(j), in(i), inf);
    }
    for (int i = 1; i <= n; ++i) {
        if (prefs[i-1] != '?') {
            if (origteam[i-1] == prefs[i-1]) {
                add_edge(s, in(i), inf);
            } else {
                add_edge(out(i), t, inf);
            }
        }
        add_edge(in(i), out(i), 1); // we are cutting vertices, so these edges are finite-capacity, while the others aren't
    }
    int maxflow = dinic(s, t);
    // cout << "maxflow = " << maxflow << endl;

    // get all reachable nodes (the set S)
    vector<bool> inS(2*n+1, false);
    stack<int> stk;
    stk.push(s);
    while (stk.size()) {
        int node = stk.top();
        stk.pop();
        if (inS[node]) continue; // already visited
        inS[node] = true;
        for (Edge *edge : e[node]) {
            if (!inS[edge->v] && edge->f < edge->c) {
                stk.push(edge->v);
            }
        }
    }
    // cout << "in S: "; for (int i = 1; i <= 2*n; ++i) if (inS[i]) cout << i << " "; cout << endl;

    finalteam = string(n, ' ');
    for (int i = 1; i <= n; ++i) {
        if (inS[in(i)] && !inS[out(i)]) {
            // vertex was cut off (removed)
            finalteam[i-1] = 'X';
        } else {
            if (inS[in(i)]) {
                finalteam[i-1] = origteam[i-1];
            } else {
                finalteam[i-1] = origteam[i-1] == 'A' ? 'B' : 'A';
            }
        }
    }
    cout << finalteam << endl;
}

int main() {
    solve();
    return 0;
}
