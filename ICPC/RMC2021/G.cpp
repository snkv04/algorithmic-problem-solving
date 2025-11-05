#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ld min(ld a, ld b) {
    if (a < b) return a;
    return b;
}

int main() {
    int dL, dW, G, L;
    cin >> dL >> dW >> G >> L;
    vector<vector<ld>> dp(101, vector<ld>(101, 0));
    dp[0][0] = 1;
    ld ev = 0;
    for (int t = 0; t < 100; t++) {
        for (int w = 0; w < 100; w++) {
            //cout << dp[t][w];
            dp[t + 1][w] += dp[t][w] * L / 100;
            ld pprize = min(100, dW * w + dL * (t - w)) / 100.0;
            //cout << "(" << pprize << ") ";
            dp[t + 1][w + 1] += dp[t][w] * (100 - L) / 100 * (1 - pprize);
            ev += (t + 1) * dp[t][w] * (100 - L) / 100 * pprize;
        }
        //cout << endl;
    }
    for (int w = 0; w < 100; w++) {
        ev += dp[100][w] * (100.0 + 100.0 / (100 - L));
    }
    cout << fixed << setprecision(12) << ev * 100 / G << endl;
}