#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int sums[n];
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int digit = s[i] - '0';
        sum += digit;
        sums[i] = sum;
    }
    reverse(sums, sums + n);
    // cout << "sums = ";
    // for (int i = 0; i < n; ++i) cout << sums[i] << " ";
    // cout << "\n";

    int ans[n+5];
    int lastnon0 = 0;
    sum = 0;
    for (int i = 0; i < n+5; ++i) {
        sum += i < n ? sums[i] : 0;
        int digit = sum % 10;
        sum /= 10;
        ans[i] = digit;
        if (digit != 0) lastnon0 = i;
    }

    for (int i = lastnon0; i >= 0; --i) {
        cout << ans[i];
    }
    cout << "\n";
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
