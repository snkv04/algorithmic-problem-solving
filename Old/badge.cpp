#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

const int MAXN = 1005;
bool visited[MAXN], in_cycle[MAXN], on_stack[MAXN];
int p[MAXN], ans[MAXN];

void dfs(int node) {
    visited[node] = true;
    on_stack[node] = true;
    if (!visited[p[node]]) {
        dfs(p[node]);
    } else if (on_stack[p[node]]) {
        in_cycle[p[node]] = true;
    }
    on_stack[node] = false;
}

void dfs2(int node) {
    visited[node] = true;
    in_cycle[node] = true;
    if (!visited[p[node]]) {
        dfs2(p[node]);
    }
}

void dfs3(int node) {
    visited[node] = true;
    if (in_cycle[node]) {
        ans[node] = node+1;
        return;
    }

    if (!visited[p[node]]) {
        dfs3(p[node]);
    }
    ans[node] = ans[p[node]];
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) { cin >> p[i]; --p[i]; }
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    fill(visited, visited+n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && in_cycle[i]) {
            dfs2(i);
        }
    }

    fill(ans, ans+n, -1);
    fill(visited, visited+n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs3(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
