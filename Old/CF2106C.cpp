#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, k;
    cin >> n >> k;
    int a[n], b[n];
    for (int i = 0; i < 2*n; ++i) {
        if (i < n) cin >> a[i];
        else cin >> b[i%n];
    }

    int x = -1;
    int mn = 1e9, mx = -1e9;
    for (int i = 0; i < n; ++i) {
        mn = min(a[i], mn);
        mx = max(a[i], mx);
        if (b[i] != -1) {
            if (x == -1) {
                x = a[i] + b[i];
            } else if (a[i] + b[i] != x) {
                cout << "0\n";
                return;
            }
        }
    }
    int upper = mn + k, lower = mx;

    if (x != -1) {
        cout << (x >= lower && x <= upper ? 1 : 0) << "\n";
    } else {
        int upper = mn + k, lower = mx;
        cout << upper - lower + 1 << "\n";
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
