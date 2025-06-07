#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void add(map<int, int> &mp, int x) {
    if (mp.find(x) != mp.end()) {
        ++mp[x];
    } else {
        mp[x] = 1;
    }
}

void remove(map<int, int> &mp, int x) {
    --mp[x];
    if (mp[x] == 0) {
        mp.erase(x);
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    map<int, int> vals;
    while (n--) {
        int ai;
        cin >> ai;
        add(vals, ai);
    }

    map<int, int> counts;
    for (const auto& p : vals) {
        add(counts, p.second);
    }
    int distinct = vals.size();

    while (k > 0 && !(counts.size() == 1 && (*counts.rbegin()).second == 1)) {
        int mincount = counts.begin()->first;
        if (mincount <= k) {
            --distinct;
            int maxcount = counts.rbegin()->first;
            remove(counts, mincount);
            remove(counts, maxcount);
            add(counts, mincount + maxcount);
            k -= mincount;
        } else {
            break;
        }
    }
    cout << distinct << "\n";
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
