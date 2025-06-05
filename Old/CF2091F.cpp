#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m, d;
    cin >> n >> m >> d;
    string grid[n];
    for (int i = 0; i < n; ++i) cin >> grid[i];
    int dj = -1, l = 0, r = d;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (mid * mid <= d * d - 1) {
            dj = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    // cout << "d = " << d << ", dj = " << dj << "\n";

    ll mem[n][m][2], prefsums[n][m][2];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fill(mem[i][j], mem[i][j]+2, 0);
            fill(prefsums[i][j], prefsums[i][j]+2, 0);
        }
    }
    ll ans = 0;
    for (int i = n-1; i >= 0; --i) {
        for (int k = 0; k < 2; ++k) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'X') {
                    if (k == 0) {
                        if (i == n-1) mem[i][j][k] = 1;
                        else {
                            int left = j - dj - 1, right = min((int) (j + dj), m-1);
                            mem[i][j][k] = prefsums[i+1][right][0] + prefsums[i+1][right][1];
                            if (left >= 0) {
                                mem[i][j][k] -= prefsums[i+1][left][0] + prefsums[i+1][left][1];
                                mem[i][j][k] += 2 * MOD;
                            }
                        }
                    } else {
                        int left = j-d-1, right = min(j + d, m-1);
                        mem[i][j][k] = prefsums[i][right][0];
                        if (left >= 0) {
                            mem[i][j][k] -= prefsums[i][left][0];
                            mem[i][j][k] += MOD;
                        }
                        mem[i][j][k] -= mem[i][j][0];
                        mem[i][j][k] += MOD;
                    }
                }
                mem[i][j][k] %= MOD;

                int last = j == 0 ? 0 : prefsums[i][j-1][k];
                prefsums[i][j][k] = (last + mem[i][j][k]) % MOD;

                if (i == 0) {
                    ans = (ans + mem[i][j][k]) % MOD;
                }
            }
        }
    }
    cout << (ans % MOD) << "\n";
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
