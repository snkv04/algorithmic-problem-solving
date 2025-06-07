#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void add(map<ll, int> &mp, ll x, int cnt) {
    if (mp.find(x) != mp.end()) {
        mp[x] += cnt;
    } else {
        mp[x] = cnt;
    }
}

void remove(map<ll, int> &mp, ll x, int cnt) {
    mp[x] -= cnt;
    if (mp[x] == 0) {
        mp.erase(x);
    }
}

void solve() {
    int n, x;
    cin >> n >> x;
    map<ll, int> ms;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        add(ms, ai, 1);
    }
    // cout << "multiset = ";
    // for (auto &p : ms) cout << "(" << p.first << " = " << p.second << ") ";
    // cout << "\n";

    int mex = 0;
    while (ms.find(mex) != ms.end()) {
        if (ms[mex] > 1) {
            int moving = ms[mex] - 1;
            remove(ms, mex, moving);
            add(ms, mex + x, moving);
        }
        ++mex;
    }
    cout << mex << "\n";
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
