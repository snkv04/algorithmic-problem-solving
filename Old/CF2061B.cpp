#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        ++mp[ai];
    }

    vector<int> multiple;
    for (const pair<int, int> &p : mp) {
        if (p.second >= 4) {
            for (int i = 0; i < 4; ++i) cout << p.first << " ";
            cout << '\n';
            return;
        } else if (p.second >= 2) {
            multiple.push_back(p.first);
        }
    }

    if (multiple.size() >= 2) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                cout << multiple[i] << " ";
            }
        }
        cout << '\n';
        return;
    } else if (multiple.empty()) {
        cout << "-1\n";
        return;
    } else {
        mp[multiple[0]] -= 2;
        if (mp[multiple[0]] == 0) {
            mp.erase(multiple[0]);
        }

        for (const pair<int, int> &p : mp) {
            if (p.first == mp.rbegin()->first) {
                break;
            }

            const auto &next = *mp.upper_bound(p.first);
            if (next.first - p.first < 2 * multiple[0]) {
                cout << multiple[0] << ' ' << multiple[0] << ' ' << p.first << ' ' << next.first << '\n';
                return;
            }
        }
        cout << "-1\n";
        return;
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
