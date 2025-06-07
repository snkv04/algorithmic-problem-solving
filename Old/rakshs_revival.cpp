#include <bits/stdc++.h>
using namespace std;

int cnt, m, k;

void move(string &s, int idx) {
    if (idx - m >= 0) {
        cnt -= s[idx-m] - '0';
    }
    cnt += s[idx] - '0';
}

void solve() {
    int n; cin >> n >> m >> k;
    string s; cin >> s;
    cnt = 0;
    int ans = 0;
    int i = 0;
    while (i < n) {
        move(s, i);
        if (cnt == 0 && i >= m-1) {
            ++ans;
            for (int j = i; j < min(n, i+k); ++j) {
                s[j] = '1';
            }
            i += k;
            cnt = min(m, k);
        } else {
            ++i;
        }

        // cout << "i = " << i << " and s = " << s << "\n";
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}