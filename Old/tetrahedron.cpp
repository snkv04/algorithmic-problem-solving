#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    ll currd = 1, currother = 0;
    for (int i = 1; i <= n; ++i) {
        int newd = (3 * currother) % MOD;
        int newother = (2 * currother + currd) % MOD;
        currd = newd;
        currother = newother;
    }
    cout << currd << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
