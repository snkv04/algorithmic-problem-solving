#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int k;
    cin >> k;
    unordered_map<int, int> mp;
    for (int i = 0; i < k; ++i) {
        int ai; cin >> ai;
        mp[ai] += 1;
    }

    for (int i = 1; i <= sqrt(k-2); ++i) {
        if ((k-2) % i) continue;

        int factor = (k-2) / i;
        if (i * i == k-2 && mp.find(i) != mp.end() && mp[i] >= 2) {
            cout << i << " " << i << '\n';
            return;
        } else if (i != factor && mp.find(i) != mp.end() && mp.find(factor) != mp.end()) {
            cout << i << ' ' << factor << '\n';
            return;
        }
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
