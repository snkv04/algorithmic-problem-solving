#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = 105;
int dp[MAXN][2][2];
bool vis[MAXN][2][2];
string s;
int n;

int best(int i, int diff, int nextdiff) {
    /*
    abbc
    */

    if (vis[i][diff][nextdiff]) return dp[i][diff][nextdiff];
    if (i + 1 == n/2) {
        if (diff) {
            return 1;
        } else {
            return 0;
        }
    }

    int result;
    if (!diff && !nextdiff) {
        result = best(i+1, nextdiff, s[i+2] != s[n-3-i]);
    } else if (!diff && nextdiff) {
        result = min(
            1 + best(i, 1, 1),
            best(i+1, nextdiff, s[i+2] != s[n-3-i])
        );
    } else if (diff && !nextdiff) {
        result = min(
            1 + best(i, 1, 1),
            1 + best(i+1, 1, s[i+2] != s[n-3-i])
        );
    } else {
        result = 1 + min(
            best(i+1, 0, s[i+2] != s[n-3-i]),
            best(i+1, 1, s[i+2] != s[n-3-i])
        );
    }
    dp[i][diff][nextdiff] = result;
    vis[i][diff][nextdiff] = 1;
    return result;
}

void solve() {
    cin >> s;
    n = s.size();
    if (n == 2) {
        cout << (s[0] != s[1]) << "\n";
        return;
    } else if (n == 3) {
        cout << (s[0] != s[2]) << "\n";
        return;
    }

    int diff = s[0] != s[n-1];
    int nextdiff = s[1] != s[n-2];
    cout << best(0, diff, nextdiff) << endl;
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
