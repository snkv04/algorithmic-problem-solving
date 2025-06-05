#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    ll a[n], b[n];
    for (int i = 0; i < 2*n; ++i) {
        if (i < n) {
            cin >> a[i];
        } else {
            cin >> b[i-n];
        }
    }

    ll idx = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] < b[i]) {
            if (idx == -1) {
                idx = i;
            } else {
                cout << "NO\n";
                return;
            }
        }
    }
    if (idx == -1) {
        cout << "YES\n";
        return;
    }

    bool works = true;
    for (int i = 0; i < n; ++i) {
        if (i != idx && a[i] - b[i] < b[idx] - a[idx]) {
            works = false;
        }
    }
    cout << (works ? "YES" : "NO") << '\n';
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
