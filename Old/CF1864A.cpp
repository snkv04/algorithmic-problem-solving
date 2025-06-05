#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int x, y, n;
    cin >> x >> y >> n;
    vector<int> ans(n-1, 0);
    for (int i = 1; i <= n-1; ++i) {
        int elem = y - (i * (i + 1)) / 2;
        if (elem < x) {
            cout << "-1\n";
            return;
        }
        ans[n-1-i] = elem;
    }
    for (int i = 0; i < n-1; ++i) {
        cout << (i == 0 ? x : ans[i]) << " ";
    }
    cout << y << "\n";
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
