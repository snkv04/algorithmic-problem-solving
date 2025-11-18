#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    map<int, int> a;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        a[ai] += 1;
    }

    int ans = 0, cnt = 0;
    for (auto e : a) {
        ans = max(ans, 1 + 2 * cnt);
        cnt += e.second >= 2;
    }
    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
