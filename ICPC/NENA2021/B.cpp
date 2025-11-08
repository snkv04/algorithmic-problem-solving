#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

vector<vector<int>> adj;
vector<int> depth;
vector<vector<int>> ancestor;
int logmaxn;

void dfs(int node, int parent) {
    if (parent != -1) {
        depth[node] = depth[parent] + 1;
    }
    ancestor[node][0] = parent;
    for (int i = 1; i <= logmaxn; ++i) {
        int halfway = ancestor[node][i-1];
        if (halfway != -1) {
            ancestor[node][i] = ancestor[halfway][i-1];
        } else {
            ancestor[node][i] = -1;
        }
    }

    for (int next : adj[node]) {
        if (next != parent) {
            dfs(next, node);
        }
    }
}

int jump(int node, int k) {
    if (k > depth[node]) return -1;

    for (int i = 0; i <= logmaxn; ++i) {
        if ((1 << i) & k) {
            node = ancestor[node][i];
        }
        // if (node == -1) return -1; // not needed because of first check
    }
    return node;
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    int diff = depth[b] - depth[a];
    b = jump(b, diff);
    if (a == b) return a;

    for (int i = logmaxn; i >= 0; --i) {
        if (ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}

int dist(int a, int b) {
    int lowest = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[lowest];
}

void solve() {
    int n;
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    logmaxn = ceil(log2(n));
    depth.resize(n);
    ancestor = vector<vector<int>>(n, vector<int>(logmaxn+1, -1));
    depth[0] = 0;
    dfs(0, -1);

    vector<int> p(n); for (int i = 0; i < n; ++i) { cin >> p[i]; --p[i]; }

    bool ans = true;
    for (int i = 0; i < n-1; ++i) {
        int a = p[i], b = p[i+1];
        if (dist(a, b) > 3) {
            ans = false;
            break;
        }
    }
    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}