#include <bits/stdc++.h>
using namespace std;

int n, a, b;
vector<vector<pair<int, int>>> adj;
set<int> tob;

void dfs_recursive(int node, int parent, int sum) {
    if (node != b) tob.insert(sum);

    for (auto edge : adj[node]) {
        int to = edge.first, weight = edge.second;
        if (to != parent) {
            dfs_recursive(to, node, sum ^ weight);
        }
    }
}

bool dfs2_recursive(int node, int parent, int sum) {
    if (tob.find(sum) != tob.end()) {
        return true;
    }

    for (auto edge : adj[node]) {
        int to = edge.first, weight = edge.second;
        if (to != parent && to != b) {
            if (dfs2_recursive(to, node, sum ^ weight)) {
                return true;
            }
        }
    }
    return false;
}

void dfs_iterative() {
    stack<array<int, 3>> stk;
    stk.push({b, -1, 0});
    while (stk.size()) {
        auto arr = stk.top();
        stk.pop();
        int node = arr[0], parent = arr[1], sum = arr[2];
        
        if (node != b) {
            tob.insert(sum);
        }

        for (auto edge : adj[node]) {
            int to = edge.first, weight = edge.second;
            if (to != parent) {
                stk.push({to, node, sum ^ weight});
            }
        }
    }
}

bool dfs2_iterative() {
    stack<array<int, 3>> stk;
    stk.push({a, -1, 0});
    while (stk.size()) {
        auto arr = stk.top();
        stk.pop();
        int node = arr[0], parent = arr[1], sum = arr[2];
        if (tob.find(sum) != tob.end()) {
            return true;
        }

        for (auto edge : adj[node]) {
            int to = edge.first, weight = edge.second;
            if (to != parent && to != b) {
                stk.push({to, node, sum ^ weight});
            }
        }
    }
    return false;
}

void solve() {
    cin >> n >> a >> b;
    --a; --b;
    adj.clear();
    adj.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // both the recursive and iterative versions work; the problem was using std::unordered_set instead of std::set
    tob.clear();
    dfs_iterative();
    if (tob.find(0) != tob.end()) {
        cout << "YES\n";
    } else if (dfs2_iterative()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
