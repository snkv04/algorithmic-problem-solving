#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; char c;
    cin >> n >> c;
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    // cout << "reverse s = " << s << '\n';
    int last = 1e9, best = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (s[i%n] == 'g') {
            last = i;
        }

        if (s[i%n] == c) {
            best = max(best, i - last);
        }
    }
    cout << best << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}