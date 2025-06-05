#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int odd = 0, even = 0;
    while (n--) {
        int ai;
        cin >> ai;
        if (ai % 2) ++odd;
        else ++even;
    }

    if (even) {
        cout << odd + 1 << '\n';
    } else {
        cout << odd - 1 << '\n';
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
