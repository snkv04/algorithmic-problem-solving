#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    vector<int> a[2];
    for (int i = 0; i < 2*n; ++i) {
        int num; cin >> num;
        a[i/n].push_back(num);
    }

    int sum = 0, bestmin = -1e9;
    for (int i = 0; i < n; ++i) {
        sum += max(a[0][i], a[1][i]);
        bestmin = max(bestmin, min(a[0][i], a[1][i]));
    }
    sum += bestmin;
    cout << sum << '\n';
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
