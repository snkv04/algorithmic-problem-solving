#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

vector<vector<int>> mem;
string a, b;

int recurse(int i, int j) {
    if (i == 0 && j == 0) return 0;
    if (mem[i][j] < 1e9) return mem[i][j];

    int val = 1e9;
    if (i > 0) val = min(val, recurse(i-1, j) + 1);
    if (j > 0) val = min(val, recurse(i, j-1) + 1);
    if (i > 0 && j > 0) val = min(val, recurse(i-1, j-1) + (a[i-1] == b[j-1] ? 0 : 1));
    mem[i][j] = val;
    return val;
}

void solve() {
    cin >> a >> b;
    int n = a.size(), m = b.size();
    mem.resize(n+1);
    for (int i = 0; i <= n; ++i) {
        mem[i].resize(m+1);
        fill(mem[i].begin(), mem[i].end(), 1e9);
    }

    // mem[0][0] = 0;
    int ans = recurse(n, m);
    cout << ans << '\n';
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
