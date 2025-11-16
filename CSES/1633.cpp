#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<int> dp(7, 0);
    dp[6] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 6; ++j) {
            dp[j] = dp[j+1];
        }
        dp[6] = 0;
        for (int j = 1; j <= 6; ++j) {
            dp[6] = (dp[6] + dp[6-j]) % MOD;
        }
    }
    cout << dp[6] << '\n';

    return 0;
}
