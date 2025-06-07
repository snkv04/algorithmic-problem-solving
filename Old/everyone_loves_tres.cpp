#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    if (n == 1 || n == 3) cout << "-1\n";
    else {
        for (int i = 1; i <= n-2; ++i) {
            if (i == n-3) {
                if (n % 2) {
                    cout << 6;
                } else {
                    cout << 3;
                }
            } else {
                cout << 3;
            }
        }
        cout << "66\n";
    }
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
