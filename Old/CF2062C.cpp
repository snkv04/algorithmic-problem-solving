#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    ll ans = 0;
    vector<ll> a;
    for (int i = 0; i < n; ++i) {
        ll ai;
        cin >> ai;
        ans += ai;
        a.push_back(ai);
    }

    while (a.size() > 1) {
        vector<ll> newvec;
        ll sum = 0;
        for (int i = 1; i < a.size(); ++i) {
            newvec.push_back(a[i]-a[i-1]);
            sum += a[i] - a[i-1];
        }
        a = newvec;
        ans = max(ans, max(sum, -1 * sum));
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
