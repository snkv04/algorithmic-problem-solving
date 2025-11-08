#include <bits/stdc++.h>
using namespace std;

int sqrt(int x) {
    if (x == 0) return 0;

    int l = 1, r = x, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (m <= x / m) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return;
    }

    vector<int> dp(n+1, 1e9);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= sqrt(i); ++j) {
            if (i % j == 0) {
                dp[i] = min(dp[i], dp[j] + dp[i/j]);
            }
        }

        for (int j = 1; j < min(100, i); ++j) {
            dp[i] = min(dp[i], dp[j] + dp[i-j]);
        }

        string s = to_string(i);
        for (int idx = 1; idx < s.size(); ++idx) {
            if (s[idx] == '0') continue;

            int l = stoll(s.substr(0, idx)), r = stoll(s.substr(idx, s.size() - idx));
            // cout << "l = " << l << ", r = " << r << "\n";
            dp[i] = min(dp[i], dp[l] + dp[r]);
        }
    }
    cout << dp[n] << endl;
}

int main() {
    solve();
    return 0;
}
