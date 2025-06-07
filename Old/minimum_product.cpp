#include <iostream>
using namespace std;

using ll = long long;

void solve() {
    int a, b, x, y, n;
    cin >> a >> b >> x >> y >> n;

    ll first = 1LL * (a - min(n, a-x)) * (b - min(n - min(n, a-x), b-y));
    ll second = 1LL * (b - min(n, b-y)) * (a - min(n - min(n, b-y), a-x));
    
    cout << min(first, second) << '\n';
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