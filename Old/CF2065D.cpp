#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

bool cmp(ll a, ll b) {
    return a > b;
}

void solve() {
    int n, m;
    cin >> n >> m;
    ll total = 0;
    vector<ll> sums;
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j < m; ++j) {
            ll ai;
            cin >> ai;
            total += ai * (m - j);
            sum += ai;
        }
        sums.push_back(sum);
    }
    sort(sums.begin(), sums.end(), cmp);
    for (int i = 0; i < n; ++i) {
        total += sums[i] * ((n-1 - i) * m);
    }
    cout << total << '\n';
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
