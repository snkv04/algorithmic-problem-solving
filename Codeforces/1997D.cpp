#include <bits/stdc++.h>
using namespace std;

bool dfs(
    int node,
    long long decrease,
    vector<vector<int>> &adj,
    vector<long long> &a,
    vector<long long> &mn
) {
    long long curr = a[node] - decrease;
    if (adj[node].empty()) {
        return curr >= 0;
    } else {
        decrease += max(0LL, -curr);
        if (decrease > mn[node]) {
            return false;
        }
        
        bool valid = true;
        for (int next : adj[node]) {
            valid = valid && dfs(next, decrease, adj, a, mn);
        }
        return valid;
    }
}

bool check(
    long long m,
    vector<vector<int>> &adj,
    vector<long long> &a,
    vector<long long> &mn
) {
    bool valid = true;
    for (int next : adj[0]) {
        valid = valid && dfs(next, m - a[0], adj, a, mn);
    }
    return valid;
}

void dfs2(
    int node,
    vector<vector<int>> &adj,
    vector<long long> &a,
    vector<long long> &mn
) {
    if (adj[node].empty()) {
        mn[node] = a[node];
        return;
    }
    
    for (int next : adj[node]) {
        dfs2(next, adj, a, mn);
        mn[node] = min(mn[node], mn[next]);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        adj[p].push_back(i);
    }
    
    vector<long long> mn(n, 1e9);
    dfs2(0, adj, a, mn);
    
    long long l = a[0], r = -1, ans = -1;
    for (int i = 0; i < n; ++i) if (adj[i].empty()) r = max(r, a[0] + a[i]);
    while (l <= r) {
        long long m = l + (r - l) / 2;
        if (check(m, adj, a, mn)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
