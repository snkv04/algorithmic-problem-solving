#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    string s;
    cin >> s;
    int sum = 0, n = s.size(), twos = 0, threes = 0;
    for (int i = 0; i < n; ++i) {
        int digit = s[i] - '0';
        sum += digit;
        if (digit == 2) ++twos;
        if (digit == 3) ++threes;
    }
    
    if (sum % 9 == 0 || twos >= 9) {
        cout << "YES\n";
        return;
    }
    int diff = 9 - (sum % 9);
    set<int> possible;
    for (int i = 0; i <= twos; ++i) {
        for (int j = 0; j <= min(2, threes); ++j) {
            possible.insert((2*i + 6*j) % 9);
        }
    }
    cout << ((possible.find(diff) != possible.end()) ? "YES" : "NO") << "\n";
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
