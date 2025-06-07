#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n, d;
    cin >> n >> d;
    set<int> ans;
    ans.insert(1);
    if (n >= 3 || d % 3 == 0) ans.insert(3);
    if ((n >= 6) || (d == 9) || (n >= 3 && d % 3 == 0)) ans.insert(9);
    if (d==5) ans.insert(5);
    if (n >= 3 || d==7) ans.insert(7);
    for (int num : ans) cout << num << " ";
    cout << "\n";
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
