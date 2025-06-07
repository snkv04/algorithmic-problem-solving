#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    bool found[n];
    fill(found, found+n, false);
    multiset<int> ms;
    for (int i = 0; i < n; ++i) {
        if (a[i] > n || (a[i] <= n && found[a[i]-1])) {
            ms.insert(a[i]);
        } else {
            found[a[i]-1] = true;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (found[i]) continue;
        int need = i+1;
        if (ms.upper_bound(need * 2) == ms.end()) {
            ans = -1;
            break;
        } else {
            ++ans;
            ms.erase(ms.upper_bound(need * 2));
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
