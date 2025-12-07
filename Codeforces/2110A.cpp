#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    
    int mneven = -1, mnodd = -1, mxeven = -1, mxodd = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2) {
            if (mnodd == -1) mnodd = i;
            mxodd = i;
        } else {
            if (mneven == -1) mneven = i;
            mxeven = i;
        }
    }
    
    auto left = [](int idx) { return idx; };
    auto right = [&](int idx) { return n - 1 - idx; };
    int ans = min(
        mneven == -1 ? 1e9 : (left(mneven) + right(mxeven)),
        mnodd == -1 ? 1e9 : (left(mnodd) + right(mxodd))
    );
    cout << ans << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
