#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];

    int first = -1, last = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] != 0) {
            first = i;
            break;
        }
    }
    for (int i = n-1; i >= 0; --i) {
        if (a[i] != 0) {
            last = i;
            break;
        }
    }

    if (first == -1) cout << "0\n";
    else {
        for (int i = first; i <= last; ++i) {
            if (a[i] == 0) {
                cout << "2\n";
                return;
            }
        }
        cout << "1\n";
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
