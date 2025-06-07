#include <bits/stdc++.h>
using namespace std;

string s;

void solve() {
    stringstream ss(s);
    double a, b, c, d, m, t;
    ss >> a >> b >> c >> d >> m >> t;
    // cout << "here's a: |" << a << "|\n";
    double l = 0.000001, r = 1e18, ans = -1;
    for (int i = 1; i <= 100; ++i) {
        double h = (l + r) / 2.0;
        double v = m / h;
        double used = (a * v * v * v * v) + (b * v * v * v) + (c * v * v) + d * v;
        used *= h;
        if (used > t) {
            l = h;
        } else {
            ans = h;
            r = h;
        }
    }
    ans = std::trunc(100 * m / ans) / 100;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(2);

    int t;
    while (getline(cin, s)) {
        solve();
    }

    return 0;
}
