#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int mem[n+1];
    std::fill(mem, mem + n + 1, 0);
    int best[n+1];
    fill(best, best+n+1, -1e9);
    for (int i = 1; i <= n; ++i) {
        int color = a[i-1];
        mem[i] = max(mem[i-1], i + best[color]);
        best[color] = max(best[color], mem[i-1] - i + 1);
    }
    cout << mem[n] << '\n';
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
