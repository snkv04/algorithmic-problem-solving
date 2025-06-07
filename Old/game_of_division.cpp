#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, k;
    cin >> n >> k;
    int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> counts[k];
    for (int i = 0; i < n; ++i) {
        counts[a[i]%k].push_back(i+1);
    }

    for (int i = 0; i < k; ++i) {
        if (counts[i].size() == 1) {
            cout << "YES\n" << counts[i][0] << "\n";
            return;
        }
    }
    cout << "NO\n";
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
