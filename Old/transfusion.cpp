#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    ll a[n], sum = 0, sum0 = 0, sum1 = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        if (i % 2) sum1 += a[i];
        else sum0 += a[i];
    }

    if (sum % n != 0) {
        cout << "NO\n";
        return;
    }
    ll end = sum / n;
    if (sum0 != end * ((n+1) / 2) || sum1 != end * (n / 2)) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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
