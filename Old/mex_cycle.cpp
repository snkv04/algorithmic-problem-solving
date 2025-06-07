#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    --x; --y;
    int start = -1, two = -1;
    if (abs((ll) (y-x)) == 1 || abs((ll) (y-x)) == n-1) {
        start = 0;
        if (n%2) {
            two = n-1;
        }
    } else {
        if (n%2 == 0) {
            if (abs((ll)y-x)%2) {
                start = 0;
            } else {
                start = x;
                two = y;
            }
        } else {
            if ((y-x)%2 == 0) {
                start = (y+1)%n;
                two = y;
            } else {
                start = (x+1)%n;
                two = x;
            }
        }
    }

    int a[n];
    for (int i = 0; i < n; ++i) {
        a[(start+i)%n] = i%2;
    }
    if (two >= 0) {
        a[two] = 2;
    }

    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
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
