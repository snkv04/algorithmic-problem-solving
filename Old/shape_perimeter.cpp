#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m;
    cin >> n >> m;
    int ans = 4 * n * m;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        if (i) {
            ans -= 2 * ((m-x) + (m-y));
        }
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
