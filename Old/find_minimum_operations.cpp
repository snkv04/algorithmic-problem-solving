#include <iostream>
// #include <vector>
// #include <string>
// #include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    if (k == 1 || k > n) {
        cout << n << '\n';
        return;
    }

    int ans = 0;
    while (n > 0) {
        ans += n % k;
        n /= k;
    }
    cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
