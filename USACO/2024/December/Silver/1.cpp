#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    vector<ll> pref(n), suf(n);
    for (int i = 0; i < n; ++i) {
        pref[i] = a[i] + (i == 0 ? 0 : pref[i-1]);
    }
    for (int i = n-1; i >= 0; --i) {
        suf[i] = a[i] + (i == n-1 ? 0 : suf[i+1]);
    }

    int e = n/2-1;
    ll elsie = 0;
    for (int i = 0; i <= e; ++i) {
        ll curr = 0;
        if (i) {
            curr += pref[i-1];
        }
        if (i != e) {
            curr += suf[n-1-(e-1-i)];
        }
        elsie = max(curr, elsie);
    }
    cout << pref[n-1] - elsie << " " << elsie << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
