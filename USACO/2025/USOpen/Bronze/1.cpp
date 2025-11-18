#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> chart(n, vector<char>(n, ' '));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> chart[i][j];
            if (chart[i][j] == 'L') {
                chart[j][i] = 'W';
            } else if (chart[i][j] == 'W') {
                chart[j][i] = 'L';
            } else {
                chart[j][i] = chart[i][j];
            }
        }
    }
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         cout << chart[i][j];
    //     }
    //     cout << endl;
    // }

    while (m--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        int ans = 0, cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (chart[i][l] == 'W' && chart[i][r] == 'W') {
                ans += 2 * n - 1;
                ++cnt;
            }
        }
        ans -= cnt * (cnt - 1);
        cout << ans << "\n";
    }
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
    
    return 0;
}
