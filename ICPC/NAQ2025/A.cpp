#include <bits/stdc++.h>
using namespace std;

void solve() {
    int r, g, b, cr, cg, cb, rg, gb;
    cin >> r >> g >> b >> cr >> cg >> cb >> rg >> gb;
    r = max(0, r - cr);
    g = max(0, g - cg);
    b = max(0, b - cb);

    int ans = 0;
    if (r > rg || b > gb) {
        cout << "-1\n";
        return;
    }
    ans += r;
    rg -= r;
    ans += b;
    gb -= b;
    if (g > rg + gb) {
        cout << "-1\n";
        return;
    }
    ans += g;
    cout << ans << "\n";
}

int main() {
    solve();

    return 0;
}