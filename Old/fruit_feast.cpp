#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    ifstream cin("feast.in");
    ofstream cout("feast.out");

    int t, a, b;
    cin >> t >> a >> b;
    
    vector<bool> works(t+1);
    works[0] = true;
    for (int i = 1; i <= t; ++i) {
        if (i-a >= 0 && works[i-a]) works[i] = true;
        if (i-b >= 0 && works[i-b]) works[i] = true;
    }

    for (int i = 1; i <= t; ++i) {
        if (works[i]) {
            works[i/2] = true;
        }
    }

    for (int i = 1; i <= t; ++i) {
        if (i-a >= 0 && works[i-a]) works[i] = true;
        if (i-b >= 0 && works[i-b]) works[i] = true;
    }

    int ans = 0;
    for (int i = t; i >= 1; --i) {
        if (works[i]) {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";

    cin.close();
    cout.close();
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
