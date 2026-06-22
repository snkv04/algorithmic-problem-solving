#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    multiset<int> boxes;
    for (int i = 0; i < m; ++i) {
        int a_i;
        cin >> a_i;
        boxes.insert(a_i);
    }
    vector<pair<int, int>> gifts(n);
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        k -= y;
        z -= y;
        gifts[i] = {z, x};
    }
    sort(gifts.begin(), gifts.end());
    
    int ans = 0;
    vector<bool> used(n, false);
    for (int i = n - 1; i >= 0; --i) {
        if (boxes.lower_bound(gifts[i].second) != boxes.end()) {
            ++ans;
            used[i] = true;
            boxes.erase(boxes.lower_bound(gifts[i].second));
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (!used[i] && k >= gifts[i].first) {
            ++ans;
            k -= gifts[i].first;
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
