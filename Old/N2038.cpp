#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    string s;
    cin >> s;
    int a = s[0] - '0', b = s[2] - '0';
    if (a > b) {
        s[1] = '>';
    } else if (a < b) {
        s[1] = '<';
    } else {
        s[1] = '=';
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
