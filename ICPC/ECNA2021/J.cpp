#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    
    vector<int> a(n+1, -1);
    for (int i = 0; i < n; ++i) cin >> a[i];

    ll ansarea = -1, ansl = -1, ansr = -1;
    stack<pair<int, ll>> stk;
    for (int i = 0; i <= n; ++i) {
        int height = a[i];
        int idx = i;
        while (stk.size() && stk.top().second > height) {
            ll area = stk.top().second * (i - stk.top().first);
            idx = stk.top().first;
            stk.pop();
            if ((area > ansarea) || (area == ansarea && idx + 1 < ansl)) {
                ansarea = area;
                ansl = idx + 1;
                ansr = i;
            }
        }
        stk.push(make_pair(idx, height));
    }
    cout << ansl << " " << ansr << " " << ansarea << endl;
}

int main() {
    solve();
    return 0;
}
