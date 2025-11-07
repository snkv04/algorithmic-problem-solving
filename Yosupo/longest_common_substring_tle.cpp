#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;
    vector<int> dp(t.size() + 1, 0);
    int ans = 0, a = 0, b = 0, c = 0, d = 0;
    for (int i = 1; i <= s.size(); ++i) {
        vector<int> newdp(t.size() + 1, 0);
        for (int j = 1; j <= t.size(); ++j) {
            if (s[i-1] == t[j-1]) {
                newdp[j] = dp[j-1] + 1;
                if (newdp[j] > ans) {
                    ans = newdp[j];
                    a = i - newdp[j];
                    b = i;
                    c = j - newdp[j];
                    d = j;
                }
            }
        }
        dp = std::move(newdp);
    }
    cout << a << " " << b << " " << c << " " << d << endl;
}

int main() {
    solve();
    return 0;
}
