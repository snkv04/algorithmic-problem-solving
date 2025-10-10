#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<ll> p = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009};
vector<vector<ll>> ppow;

vector<vector<ll>> get_hashes(string s) {
    int n = s.size();
    vector<vector<ll>> result(2*n+1, vector<ll>(2, 0));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= 2*n; ++i) {
            int as_int = s[(i-1)%n];
            result[i][t] = (result[i-1][t] * p[t] + as_int) % MOD[t];
        }
    }
    return result;
}

// pair<ll, ll> operator-(const pair<ll, ll> &a, const pair<ll, ll> &b) {
//     return make_pair(a.first - b.first, a.second - b.second);
// }

pair<ll, ll> get_hash(vector<vector<ll>> &rolling, int l, int r) {
    ++r;
    array<ll, 2> result;
    for (int t = 0; t < 2; ++t) {
        result[t] = (rolling[r][t] - ((rolling[l][t] * ppow[r-l][t]) % MOD[t]) + MOD[t]) % MOD[t];
    }
    return result;
}

void solve() {
    int n;
    cin >> n;

    ppow = vector<vector<ll>>(1e6+1, vector<ll>(2, 1));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= 1e6; ++i) {
            ppow[i][t] = (ppow[i-1][t] * p[t]) % MOD[t];
        }
    }

    set<pair<ll, ll>> hashes;
    while (n--) {
        string s;
        cin >> s;
        int len = s.size();

        vector<vector<ll>> rolling;
        for (int dir = 0; dir < 2; ++dir) {
            reverse(s.begin(), s.end());
            rolling = get_hashes(s);
            for (int i = 0; i < len; ++i) {
                int l = i, r = i + len - 1; // inclusive, inclusive for 0-based indices
                pair<ll, ll> hash = get_hash(rolling, l, r);
                if (hashes.find(hash) != hashes.end()) {
                    cout << "Yes\n";
                    return;
                }
            }
        }
        
        pair<ll, ll> full_hash = get_hash(rolling, 0, len-1);
        hashes.insert(full_hash);
    }
    cout << "No\n";
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
