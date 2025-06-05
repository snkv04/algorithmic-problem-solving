#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, k;
    cin >> n >> k;
    priority_queue<int> pq;
    while (n--) {
        int ai; cin >> ai;
        pq.push(ai);
    }
    while (pq.size() && pq.top() <= k) {
        int top = pq.top(); pq.pop();
        k -= top;
    }
    cout << k << '\n';
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
