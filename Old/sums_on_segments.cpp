#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int a[n];
    int diffidx = -1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] != -1 && a[i] != 1) {
            diffidx = i;
        }
    }

    if (diffidx != -1) {
        set<int> ans;
        int curr = 0, curr2 = 0;
        ans.insert(0);
        int maxonlyleft = 0, minonlyleft = 0, maxonlyright = 0, minonlyright = 0;
        for (int i = 0; i < diffidx; ++i) {
            curr = max(a[i], a[i] + curr);
            maxonlyleft = max(maxonlyleft, curr);

            curr2 = min(a[i], a[i] + curr2);
            minonlyleft = min(minonlyleft, curr2);
        }
        curr = 0; curr2 = 0;
        for (int i = diffidx + 1; i < n; ++i) {
            curr = max(a[i], a[i] + curr);
            maxonlyleft = max(maxonlyleft, curr);

            curr2 = min(a[i], a[i] + curr2);
            minonlyleft = min(minonlyleft, curr2);
        }

        for (int i = minonlyleft; i <= maxonlyleft; ++i) ans.insert(i);
        for (int i = minonlyright; i <= maxonlyright; ++i) ans.insert(i);

        int minleft = 0, maxleft = 0, minright = 0, maxright = 0;
        curr = 0;
        for (int i = diffidx-1; i >= 0; --i) {
            curr += a[i];
            minleft = min(minleft, curr);
            maxleft = max(maxleft, curr);
        }
        curr = 0;
        for (int i = diffidx + 1; i < n; ++i) {
            curr += a[i];
            minright = min(minright, curr);
            maxright = max(maxright, curr);
        }

        int low = min(min(minleft, minright), minleft + minright) + a[diffidx];
        int high = max(max(maxleft, maxright), maxleft + maxright) + a[diffidx];
        for (int i = low; i <= high; ++i) ans.insert(i);
        ans.insert(a[diffidx]); // should already exist

        cout << ans.size() << "\n";
        for (int num : ans) {
            cout << num << " ";
        }
        cout << "\n";
    } else {
        // cout << "NOT FOUND\n";
        set<int> ans;
        int curr = 0, curr2 = 0;
        ans.insert(0);
        int mn = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            curr = max(a[i], a[i] + curr);
            mx = max(mx, curr);

            curr2 = min(a[i], a[i] + curr2);
            mn = min(mn, curr2);
        }
        // cout << "mn = " << mn << ", mx = " << mx << "\n";

        for (int i = mn; i <= mx; ++i) ans.insert(i);

        cout << ans.size() << "\n";
        for (int num : ans) {
            cout << num << " ";
        }
        cout << "\n";
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
