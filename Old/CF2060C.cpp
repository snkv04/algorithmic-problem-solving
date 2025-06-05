#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int p[n], d[n];
    for (int i = 0; i < 2*n; ++i) {
        if (i < n) {
            cin >> p[i];
            --p[i];
        } else {
            cin >> d[i%n];
            --d[i%n];
        }
    }

    bool visited[n];
    fill(visited, visited+n, false);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int idx = d[i], count = 0;
        while (!visited[idx]) {
            ++count;
            visited[idx] = true;
            idx = p[idx];
        }
        ans += count;
        cout <<  ans << ' ';
    }
    cout << '\n';
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
