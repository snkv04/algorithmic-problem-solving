#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    ll x;
    cin >> n >> x;
    ll t[n];
    for (int i = 0; i < n; ++i) cin >> t[i];

    map<ll, int> sumcounts;
    for (int mask = 0; mask < (1 << ((n+1)/2)); ++mask) {
        ll sum = 0;
        for (int j = n/2; j < n; ++j) {
            if ((1 << (j-n/2)) & mask) {
                sum += t[j];
            }
        }
        sumcounts[sum] += 1;
    }
    // cout << "pairs:\n";
    // for (const auto &pair : sumcounts) {
    //     cout << pair.first << " " << pair.second << '\n';
    // }

    ll ans = 0;
    for (int mask = 0; mask < (1 << (n/2)); ++mask) {
        ll sum = 0;
        for (int j = 0; j < n/2; ++j) {
            if (mask & (1 << j)) sum += t[j];
        }
        ans += sumcounts[x-sum];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
