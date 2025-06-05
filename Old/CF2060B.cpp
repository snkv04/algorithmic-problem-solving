#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m;
    cin >> n >> m;

    int mp[n*m];
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int card;
            cin >> card;
            mp[card] = i;
        }
    }
    // cout << "mp = ";
    // for (int i = 0; i < n*m; ++i) cout << mp[i] << " ";
    // cout << "\n";

    bool works = true;
    for (int i = 0; i < n && works; ++i) {
        for (int j = i; j + n < n*m; j += n) {
            if (mp[j] != mp[j+n]) {
                works = false;
                break;
            }
        }
    }

    if (!works) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < n; ++i) {
            cout << mp[i] << " ";
        }
        cout << "\n";
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
