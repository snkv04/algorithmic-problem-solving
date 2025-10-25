#include <bits/stdc++.h>
using namespace std;

void solve() {
    int pi, ui, pf, uf;
    cin >> pi >> ui;
    int n = pi + ui;
    vector<int> initial(n), initidx(n);
    for (int i = 0; i < n; ++i) {
        cin >> initial[i];
        --initial[i];
        initidx[initial[i]] = i;
    }
    cin >> pf >> uf;
    vector<int> end(n);
    for (int i = 0 ;i  < n; ++i) {
        cin >> end[i];
        --end[i];
    }

    int ans = 0;
    int r = -1;
    for (int i = 0; i < pf; ++i) {
        int idx = initidx[end[i]];
        if (idx >= pi) {
            ++ans;
            r = 1e9;
        } else {
            if (idx < r) {
                ans += 2;
                r = 1e9;
            } else {
                r = max(r, idx);
            }
        }
    }
    int l = n;
    for (int i = n-1; i >= pf; --i) {
        int idx = initidx[end[i]];
        if (idx < pi) {
            ++ans;
            l = -1;
        } else {
            if (idx > l) {
                ans += 2;
                l = -1;
            } else {
                l = min(l, idx);
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}
