#include <iostream>
using namespace std;

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n-2; ++i) {
        cout << i << " " << i << '\n';
    }
    for (int i = n-1; i <= n; ++i) {
        cout << i << ' ' << n << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
