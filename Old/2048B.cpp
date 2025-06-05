#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, k;
    cin >> n >> k;
    // if (k == 1) {
    //     for (int i = 1; i <= n; ++i) {
    //         cout << i << " ";
    //     }
    //     cout << "\n";
    //     return;
    // }

    int ans[n]; fill(ans, ans + n, -1);
    int i = 1, idx = k-1;
    while (idx <= n-1) {
        ans[idx] = i++;
        idx += k;
    }

    for (idx = 0; idx <= n-1; ++idx) {
        if (ans[idx] == -1) {
            ans[idx] = i++;
        }
    }

    for (i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
