#include <iostream>
using namespace std;

using ll = long long;

void solve() {
    int n, k, pb, ps;
    cin >> n >> k >> pb >> ps;
    int p[n+1], a[n+1];
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ll mxb = 0;
    int steps = min(n, k);
    ll sum = 0;
    for (int i = 1; i <= steps; ++i) {
        sum += a[pb];
        ll remaining = k-i;
        ll total = sum + remaining * a[pb];
        mxb = max(mxb, total);
        pb = p[pb];
    }

    ll mxs = 0;
    sum = 0;
    for (int i = 1; i <= steps; ++i) {
        sum += a[ps];
        ll remaining = k-i;
        ll total = sum + remaining * a[ps];
        mxs = max(mxs, total);
        ps = p[ps];
    }

    if (mxs == mxb) {
        cout << "Draw\n";
    } else if (mxb > mxs) {
        cout << "Bodya\n";
    } else {
        cout << "Sasha\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}