#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

ll overlap(ll l1, ll r1, ll l2, ll r2) {
    ll left = max(l1, l2), right = min(r1, r2);
    return max(0LL, right - left + 1);
}

void solve() {
    ll k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;
    ll ans = 0;
    ll base = k;
    k = 1;
    while (true) {
        ll lefty = (l2 + k - 1) / k, righty = r2 / k;
        // cout << "k = " << k << ", left y = " << lefty << ", right y = " << righty << "\n";
        // cout << "left x = " << l1 << ", right x = " << r1 << '\n';
        ans += overlap(l1, r1, lefty, righty);

        if (1e18 / k < base) {
            break;
        }
        k *= base;
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
