#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int balance = 0, side = 1;
    vector<int> colors;
    set<int> sides;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') ++balance;
        else --balance;

        if (balance > 0) side = 1;
        else if (balance < 0) side = 2;
        colors.push_back(side);
        sides.insert(side);
    }

    if (balance == 0) {
        if (sides.size() == 1) fill(colors.begin(), colors.end(), 1);

        cout << sides.size() << '\n';
        for (int i = 0; i < n; ++i) {
            cout << colors[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }
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
