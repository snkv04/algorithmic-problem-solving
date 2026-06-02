#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    while (b) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ll left = i == 0 ? 1 : gcd(a[i], a[i - 1]);
        ll right = i == n - 1 ? 1 : gcd(a[i], a[i + 1]);
        ll after = lcm(left, right);
        if (after < a[i]) {
            ++ans;
            a[i] = after;
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
