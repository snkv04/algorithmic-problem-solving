#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    multiset<int> target = {0, 1, 0, 3, 2, 0, 2, 5};

    int n;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        if (target.find(ai) != target.end()) target.erase(target.find(ai));
        if (target.empty() && ans == 0) ans = i + 1;
    }

    cout << ans << "\n";
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
