#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;
    for (int i = max(a,b); i <= a*b; ++i) {
        if (i%a == i%b) {
            cout << i << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
