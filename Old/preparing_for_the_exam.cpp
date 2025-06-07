#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int a[m]; for (int i = 0; i < m; ++i) cin >> a[i];
    unordered_set<int> missing;
    for (int i = 1; i <= n; ++i) missing.insert(i);
    for (int i = 0; i < k; ++i) {
        int qi;
        cin >> qi;
        missing.erase(qi);
    }

    if (missing.size() > 1) {
        for (int i = 0; i < m; ++i) cout << 0;
        cout << '\n';
    } else if (missing.empty()) {
        for (int i = 0; i < m; ++i) cout << 1;
        cout << '\n';
    } else {
        for (int i = 0; i < m; ++i) {
            cout << (a[i] == *missing.begin() ? 1 : 0);
        }
        cout << '\n';
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
