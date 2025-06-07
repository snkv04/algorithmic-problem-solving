#include <iostream>
using namespace std;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    int diff = y - x;
    int bestmax = 1e6, bestf = -1;
    for (int f = 1; f <= diff; ++f) {
        if (diff % f != 0) continue;
        if (diff / f > n-1) continue;

        int first = x % f;
        if (!first) first += f;
        int last = first + (n - 1) * f;
        if (last < y) {
            int increase = y - last;
            first += increase;
            last += increase;
        }

        if (last < bestmax) {
            bestmax = last;
            bestf = f;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << bestmax << " ";
        bestmax -= bestf;
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
