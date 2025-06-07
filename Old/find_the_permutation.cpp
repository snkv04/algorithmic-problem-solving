#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    string adj[n];
    for (int i = 0; i < n; ++i) cin >> adj[i];

    int ans[n];
    for (int i = 0; i < n; ++i) {
        int below = 0;
        for (int j = 0; j < n; ++j) {
            if (j < i) {
                if (adj[i][j] == '1') ++below;
            } else if (j > i) {
                if (adj[i][j] == '0') ++below;
            } else continue;
        }
        ans[below] = i + 1;
    }

    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << '\n';
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
