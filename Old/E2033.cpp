#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

const int MAXN = 1e6;
int p[MAXN];
bool visited[MAXN];
vector<int> lengths;

void dfs(int node, int len) {
    visited[node] = true;
    if (!visited[p[node]]) {
        dfs(p[node], len+1);
    } else {
        lengths.push_back(len);
    }
}

void solve() {
    int n;
    cin >> n;
    fill(p, p + n, -1);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }

    fill(visited, visited + n, false);
    lengths.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, 1);
        }
    }

    int ans = 0;
    for (int len : lengths) {
        ans += (len + 1) / 2 - 1;
    }
    cout << ans << '\n';
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
