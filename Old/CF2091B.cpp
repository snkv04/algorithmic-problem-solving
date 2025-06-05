#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    ll minseen = 2e9, cnt = 0, ans = 0;
    while (a.size()) {
        ll ai = a.back();
        a.pop_back();
        ++cnt;
        minseen = min(minseen, ai);
        if (minseen * cnt >= x) {
            ++ans;
            minseen = 2e9;
            cnt = 0;
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
