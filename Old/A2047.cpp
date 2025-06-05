#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    unordered_set<int> squares;
    for (int i = 1; i * i <= 10000; i += 2) {
        squares.insert(i * i);
    }

    int sum = 0, ans = 0;
    while (n--) {
        int ai;
        cin >> ai;
        sum += ai;
        if (squares.find(sum) != squares.end()) {
            ++ans;
        }
    }
    cout << ans << '\n';
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
