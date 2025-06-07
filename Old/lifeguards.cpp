#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");

    int n;
    fin >> n;
    map<int, int> mp;
    vector<pair<int, int>> segments;
    for (int i = 0; i < n; ++i) {
        int l, r;
        fin >> l >> r;
        mp[l] = 1;
        mp[r] = -1;
        segments.push_back(make_pair(l, r));
    }

    int last = 0, totalcovered = 0, cnt = 0;
    for (auto p : mp) {
        if (cnt > 0) {
            totalcovered += p.first - last;
        }

        cnt += p.second;
        last = p.first;
    }

    map<int, int> num1s;
    last = 0, cnt = 0;
    for (auto p : mp) {
        if (cnt == 1) {
            num1s[p.first] = num1s[last] + p.first - last;
        } else {
            num1s[p.first] = num1s[last];
        }
        cnt += p.second;
        last = p.first;
    }

    int ans = 0;
    for (auto segment : segments) {
        ans = max(ans, totalcovered - num1s[segment.second] + num1s[segment.first]);
    }
    fout << ans << "\n";
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
