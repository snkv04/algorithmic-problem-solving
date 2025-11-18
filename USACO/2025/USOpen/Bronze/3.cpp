#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<vector<int>> prev(26, vector<int>(n, -1)), next = prev;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (s[i] - 'a' == j) {
                prev[j][i] = i;
            } else {
                prev[j][i] = i == 0 ? -1 : prev[j][i-1];
            }
        }
    }
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            if (s[i] - 'a' == j) {
                next[j][i] = i;
            } else {
                next[j][i] = i == n-1 ? -1 : next[j][i+1];
            }
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        
        ll ans = -1;
        for (int i = 0; i < 26; ++i) {
            if (next[i][l] == -1 || next[i][l] > r) continue;
            int idx1 = next[i][l];

            for (int j = 0; j < 26; ++j) {
                if (i == j) continue;
                if (prev[j][r] == -1 || prev[j][r] < l) continue;

                int idx3 = prev[j][r];
                if (idx3 - idx1 <= 1) continue;

                int m1 = idx1 + (idx3-idx1)/2;
                int idx2 = prev[j][m1];
                if (idx2 != -1 && idx2 > idx1) {
                    ans = max(ans, (ll) (idx2 - idx1) * (idx3 - idx2));
                }
                
                int m2 = idx3 - (idx3-idx1)/2;
                idx2 = next[j][m2];
                if (idx2 != -1 && idx2 < idx3) {
                    ans = max(ans, (ll) (idx3 - idx2) * (idx2 - idx1));
                }
            }
        }
        cout << ans << "\n";
    }
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
    
    return 0;
}
