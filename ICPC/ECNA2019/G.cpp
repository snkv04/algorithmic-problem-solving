#include <bits/stdc++.h>
using namespace std;
using ll = long long;

set<int> used;
vector<ll> x;
int ans = 0;

void dfs(int l, int r, ll low, ll high) {
    if (high < low) return;
    if (l > r) return;

    // cout << l << " " << r << " " << low << " " << high << endl;
    int m = l + (r - l) / 2;
    ll val = x[m];
    if (val >= low && val <= high && !used.count(val)) {
        ++ans;
    }
    used.insert(val);

    dfs(l, m - 1, low, min(high, val - 1));
    dfs(m + 1, r, max(low, val + 1), high);
}

int main() {
    int n, m, a, c, x0;
    cin >> n >> m >> a >> c >> x0;

    x.push_back(x0);
    while (x.size() <= n) {
        x.push_back(((ll) a * x.back() + c) % (ll) m);
    }

    dfs(1, n, -1e18, 1e18);
    cout << ans << endl;
}
