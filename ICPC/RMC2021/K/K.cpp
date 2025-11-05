/*
still doesn't work
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
string origteam, finalteam, prefs;
vector<set<int>> adj;
struct Edge {
    int v, c, f;
    Edge *rev;
};
const int inf = 1 << 28, MAXN = 1005;
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
    - how to do this? we want to cut off edges that go between different groups. not just that, we want to
    make sure that the two groups aren't connected at all, even if through a "?" node. so, to do this,
    connect one group to a source, and the second group to a sink. then, [...]
    */

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

int main() {
    solve();
    return 0;
}
