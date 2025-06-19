#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    int i = 0, j = 0, mx = 1;
    while (j != n-1) {
        if (a[j+1] - a[i] <= 5) {
            ++j;
            mx = max(mx, j-i+1);
        } else {
            ++i;
        }
    }
    cout << mx << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }
}
