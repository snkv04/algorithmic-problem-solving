#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    ll x, y; cin >> x >> y;
    int a[n];
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a, a + n);

    ll ans = 0;
    ll mindiff = sum - y, maxdiff = sum - x;
    for (int i = 0; i < n; ++i) {
        ll minrest = mindiff - a[i], maxrest = maxdiff - a[i];
        int left = 0, right = i-1, leftidx = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (a[mid] < minrest) {
                leftidx = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        left = 0; right = i-1;
        int rightidx = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (a[mid] <= maxrest) {
                rightidx = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        ans += rightidx - leftidx;
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
