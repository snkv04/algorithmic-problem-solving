#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj, sccs;
vector<int> pre, low;
int timer;
stack<int> stk;
vector<bool> onstack;

void dfs(int node, int parent = -1) {
    pre[node] = low[node] = timer++;
    stk.push(node);
    onstack[node] = true;

    bool first_backward = true;
    for (int next : adj[node]) {
        if (next == parent && first_backward) {
            first_backward = false;
            continue;
        }

        if (pre[next] == -1) {
            dfs(next, node);
        }

        if (onstack[next]) {
            low[node] = min(low[node], low[next]);
        }
    }

    if (pre[node] == low[node]) {
        vector<int> scc;
        while (stk.size()) {
            int top = stk.top();
            stk.pop();
            onstack[top] = false;
            scc.push_back(top);

            if (top == node) {
                break;
            }
        }
        sccs.push_back(scc);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pre = vector<int>(n, -1);
    low = vector<int>(n, -1);
    timer = 0;
    onstack = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        if (pre[i] == -1) {
            dfs(i);
        }
    }

    cout << sccs.size() << "\n";
    for (auto scc : sccs) {
        cout << scc.size() << " ";
        for (int node : scc) cout << node << " ";
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
