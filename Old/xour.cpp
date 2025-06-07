#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    map<int, priority_queue<int>> mp;
    int a[n];
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        a[i] = ai;
        if (mp.find(ai >> 2) == mp.end()) {
            mp[ai >> 2] = priority_queue<int>();
        }
        mp[ai >> 2].push(-ai);
    }

    int ans[n];
    for (int i = 0; i < n; ++i) {
        int key = (a[i] >> 2);
        cout << -mp[key].top() << ' ';
        mp[key].pop();
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}