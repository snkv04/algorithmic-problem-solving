#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, a+n);

    for (int i = n-1; i >= 0; i -= 2) {
        if (a[i] != a[i-1]) {
            int need = a[i];
            bool foundstart = false;
            int j = i-1;
            while (j >= 0) {
                if (need == a[j]) {
                    foundstart = true;
                    break;
                }
                a[j] = need;
                --need;
                --j;
            }

            if (!foundstart) {
                cout << "no\n";
                return;
            }
        }
    }
    cout << "yes\n";
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
