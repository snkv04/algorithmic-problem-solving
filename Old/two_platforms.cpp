#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    int x[n];
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sort(x, x+n);
    for (int i = 0; i < n; ++i) {
        int no;
        cin >> no;
    }

    int left[n], right[n];
    fill(left, left+n, 0); fill(right, right+n, 0);
    deque<int> d;
    for (int i = 0; i < n; ++i) {
        d.push_front(x[i]);
        while (!d.empty() && d.back() < x[i] - k) {
            d.pop_back();
        }
        if (i > 0) left[i] = left[i-1];
        left[i] = max(left[i], (int) d.size());
    }
    while (!d.empty()) d.pop_back();
    for (int i = n-1; i >= 0; --i) {
        d.push_front(x[i]);
        while (!d.empty() && d.back() > x[i] + k) {
            d.pop_back();
        }
        if (i < n-1) right[i] = right[i+1];
        right[i] = max(right[i], (int) d.size());
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int curr = left[i];
        if (i < n-1) curr += right[i+1];
        ans = max(ans, curr);
    }
    cout << ans << '\n';
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
