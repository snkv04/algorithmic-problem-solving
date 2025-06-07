#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    --l, --r;
    ll a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + l);
    sort(a+l, a+r+1);
    sort(a+r+1, a+n);
    ll orig_sum = 0; for (int i = l; i <= r; ++i) orig_sum += a[i];
    int i = 0, j = r;
    ll left = orig_sum;
    while (i < l && j >= l) {
        if (a[j] > a[i]) {
            left -= a[j] - a[i];
            ++i;
            --j;
        } else {
            break;
        }
    }
    ll right = orig_sum;
    i = r+1, j = r;
    while (j >= l && i < n) {
        if (a[j] > a[i]) {
            right -= a[j] - a[i];
            ++i;
            --j;
        } else {
            break;
        }
    }
    cout << min(left, right) << '\n';
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
