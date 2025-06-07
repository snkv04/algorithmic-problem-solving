#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

int fib(vector<int> &a) {
    int result = 0;
    for (int i = 0; i <= 2; ++i) {
        if (a[i] + a[i+1] == a[i+2]) ++result;
    }
    return result;
}

void solve() {
    int n;
    vector<int> a(5, 0);
    cin >> a[0] >> a[1] >> a[3] >> a[4];
    int ans = 0;
    a[2] = a[0] + a[1];
    ans = max(ans, fib(a));
    a[2] = a[3] - a[1];
    ans = max(ans, fib(a));
    a[2] = a[4] - a[3];
    ans = max(ans, fib(a));
    cout << ans << '\n';
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
