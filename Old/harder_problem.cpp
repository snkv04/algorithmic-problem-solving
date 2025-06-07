#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    set<int> unused; for (int i = 1; i <= n; ++i) unused.insert(i);
    int a[n]; for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (unused.find(a[i]) != unused.end()) {
            unused.erase(a[i]);
        }
    }

    if (!unused.empty()) {
        bool done[n+1]; fill(done, done+n+1, false);
        for (int i = 0; i < n; ++i) {
            if (done[a[i]]) {
                cout << *unused.begin() << " ";
                unused.erase(unused.begin());
            } else {
                done[a[i]] = true;
                cout << a[i] << " ";
            }
        }
        cout << '\n';
    } else {
        for (int i = 0; i < n; ++i) cout << a[i] << " ";
        cout << '\n';
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
