#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    // int n;
    // cin >> n;
    // int l[n];
    // for (int i = 0; i < n; ++i) {
    //     int num; cin >> num;
    //     --num;
    //     l[num] = i;
    // }

    // map<int, int> counts;
    // for (int i = 0; i < n; ++i) {
    //     int num;
    //     cin >> num;
    //     --num;
    //     int diff = i - l[num];
    //     if (diff < 0) diff += n;
    //     counts[diff]++;
    // }

    // int best = n;
    // for (auto &p : counts) {
    //     best = min(best, n - p.second);
    // }
    // cout << best << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
