#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /**
     * since perfect squares are the only integers with an odd number of divisors,
     * every number except perfect squares will be on after all the operations. so,
     * we can binary search on the least number n which has at least k lightbulbs
     * left on.
     */

    ll k;
    cin >> k;
    ll l = 1, r = 1e18 + 1e9, ans = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll squares = (ll) sqrt(mid);
        if (mid - squares >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
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
