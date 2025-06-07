#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    // cout << "grid:\n";
    // for (int i = 0; i < n; ++i) cout << grid[i] << '\n';

    vector<vector<vector<int>>> down(n, vector<vector<int>>(n, vector<int>(4, 0))),
        right(n, vector<vector<int>>(n, vector<int>(4, 0)));
    for (int i = 1; i < n; ++i) {
        if (grid[i][0] == 'H') break;
        else down[i][0][0] = 1;
    }
    for (int j = 1; j < n; ++j) {
        if (grid[0][j] == 'H') break;
        else right[0][j][0] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int turns = 1; turns <= 3; ++turns) {
                if (grid[i][j] == 'H') continue;
                else {
                    if (i > 0) {
                        down[i][j][turns] += down[i-1][j][turns];
                        down[i][j][turns] += right[i-1][j][turns-1];
                    }
                    if (j > 0) {
                        right[i][j][turns] += right[i][j-1][turns];
                        right[i][j][turns] += down[i][j-1][turns-1];
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= k; ++i) ans += down[n-1][n-1][i] + right[n-1][n-1][i];
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
