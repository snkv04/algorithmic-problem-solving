#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    sort(x.begin(), x.end());

    vector<long long> pref(n + 1, 0), prefsq(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + x[i - 1];
        prefsq[i] = prefsq[i - 1] + 1LL * x[i - 1] * x[i - 1];
    }

    long double ans = 1e18;
    for (int i = k; i <= n; ++i) {
        long double mean = (long double) (pref[i] - pref[i - k]) / k;
        long double badness = prefsq[i] - prefsq[i - k] - 2 * mean * (pref[i] - pref[i - k]) + mean * mean * k;
        ans = min(ans, badness);
    }
    cout << fixed << setprecision(12) << ans << endl;
}

int main() {
    solve();

    return 0;
}
