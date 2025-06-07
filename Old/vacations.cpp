#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> mem(n+1, vector<int>(3, 1e9)); // rest=0, gym=1, writing=2
    for (int i = 0; i <= 2; ++i) mem[0][i] = 0;
    for (int i = 1; i <= n; ++i) {
        int ai; cin >> ai;
        if (ai / 2) {
            mem[i][1] = min(mem[i-1][0], mem[i-1][2]);
        }
        if (ai % 2) {
            mem[i][2] = min(mem[i-1][0], mem[i-1][1]);
        }
        mem[i][0] = min(mem[i-1][0], min(mem[i-1][1], mem[i-1][2])) + 1;
    }

    cout << min(mem[n][0], min(mem[n][1], mem[n][2])) << '\n';
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
