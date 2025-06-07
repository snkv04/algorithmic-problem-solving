#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

int n, m;
const int MAXN = 20005;
vector<int> adj[ MAXN ];
bool visited[MAXN];
stack<int> reversed;
vector<int> adj2[MAXN];
int scc[MAXN];
vector<int> condensed[MAXN];

void dfs(int node) {
    visited[node] = true;
    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
    reversed.push(node);
}

void dfs2(int node, int start) {
    visited[node] = true;
    scc[node] = start;
    for (int next : adj2[node]) {
        if (!visited[next]) {
            dfs2(next, start);
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        adj[i].clear();
        adj2[i].clear();
        condensed[i].clear();
    }
    while (m--) {
        int s1, s2;
        cin >> s1 >> s2;
        --s1; --s2;
        adj[s1].push_back(s2);
        adj2[s2].push_back(s1);
    }

    fill(visited, visited+n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    fill(visited, visited+n, false);
    fill(scc, scc+n, -1);
    while (!reversed.empty()) {
        int top = reversed.top();
        reversed.pop();
        if (!visited[top]) {
            dfs2(top, top);
        }
    }

    int in[n], out[n];
    fill(in, in+n, 0);
    fill(out, out+n, 0);
    for (int i = 0; i < n; ++i) {
        for (int next : adj[i]) {
            if (scc[i] != scc[next]) {
                ++out[scc[i]];
                ++in[scc[next]];
            }
        }
    }

    int in0 = 0, out0 = 0;
    unordered_set<int> distinct;
    for (int i = 0; i < n; ++i) {
        distinct.insert(scc[i]);
        if (scc[i] == i && in[i] == 0) {
            ++in0;
        }
        if (scc[i] == i && out[i] == 0) {
            ++out0;
        }
    }
    // cout << "in0 = " << in0 << ", out0 = " << out0 << "\n";
    // cout << "distinct = "; for (auto &num : distinct) cout << num << " "; cout << "\n";

    if (distinct.size() == 1) {
        cout << "0\n";
    } else {
        cout << max(in0, out0) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
