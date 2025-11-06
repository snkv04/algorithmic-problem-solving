#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, i + a[i] + 2);
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}