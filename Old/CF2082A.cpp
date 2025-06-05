#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m;
    cin >> n >> m;
    string grid[n];
    for (int i = 0; i < n; ++i) cin >> grid[i];

    int rows = 0, cols = 0;
    for (int i = 0; i < n; ++i) {
        int acc = 0;
        for (int j = 0; j < m; ++j) {
            acc ^= grid[i][j] - '0';
        }
        if (acc) ++rows;
    }
    for (int j = 0; j < m; ++j) {
        int acc = 0;
        for (int i = 0; i < n; ++i) {
            acc ^= grid[i][j] - '0';
        }
        if (acc) ++cols;
    }
    cout << max(rows, cols) << "\n";
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
