#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m;
    cin >> n >> m;
    int a[n], b[m]; for (int i = 0; i < n; ++i) cin >> a[i]; for (int i = 0; i < m; ++i) cin >> b[i];
    int left[m], right[m];
    int j = 0;
    for (int i = 0; i < m; ++i) {
        while (j < n && a[j] < b[i]) {
            ++j;
        }
        left[i] = j == n ? j : j++;
    }
    j = n-1;
    for (int i = m-1; i >= 0; --i) {
        while (j >= 0 && a[j] < b[i]) {
            --j;
        }
        if (j >= 0) {
            right[i] = j--;
        } else {
            right[i] = j;
        }
    }

    if (left[m-1] < n) {
        cout << "0\n";
    } else {
        int ans = 2e9;
        for (int i = 0; i < m; ++i) {
            int l = i == 0 ? -1 : left[i-1];
            int r = i == m-1 ? n : right[i+1];
            if (l < r) {
                ans = min(ans, b[i]);
            }
        }
        cout << (ans == 2e9 ? -1 : ans) << "\n";
    }
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
