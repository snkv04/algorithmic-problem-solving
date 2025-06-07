#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j > 0) {
            if ((s[j] - 1) > s[j-1]) {
                swap(s[j], s[j-1]);
                --j;
                --s[j];
            } else {
                break;
            }
        }
    }

    cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
