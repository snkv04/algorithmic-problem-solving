#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    getline(cin, s);
    int n = s.size();
    int start = 0;
    while (s[start] == '0') ++start;
    string ans(n-start, ' ');
    bool dec = false;
    bool loose = false;
    int bound = -1e9;
    for (int i = start; i < n; ++i) {
        int digit = s[i] - '0';
        if (!dec) {
            if (digit >= bound) {
                ans[i-start] = digit + '0';
                bound = digit;
            } else {
                dec = true;
                bound = digit;
                ans[i-start] = digit + '0';
            }
        } else {
            if (loose) {
                ans[i-start] = bound + '0';
                continue;
            }
            if (digit <= bound) {
                ans[i - start] = digit + '0';
                bound = digit;
            } else {
                ans[i - start] = bound + '0';
                loose = true;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    string s;
    getline(cin, s);
    while (t--) {
        solve();
    }
    return 0;
}