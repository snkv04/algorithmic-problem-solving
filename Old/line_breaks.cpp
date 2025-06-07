#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, m;
    cin >> n >> m;
    string s[n]; for (int i = 0; i < n; ++i) cin >> s[i];
    int ans = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
        if (sum + s[i].size() <= m) {
            ans = i+1;
            sum += s[i].size();
        } else {
            break;
        }
    }
    cout << ans << "\n";
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
