#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> P = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009};

struct RollingHash {
    int n;
    string s;
    vector<vector<ll>> hashes, powers;

    void _buildpowers() {
        powers = vector<vector<ll>>(n+1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                powers[i][t] = (powers[i-1][t] * P[t]) % MOD[t];
            }
        }
    }

    void _buildhashes() {
        hashes = vector<vector<ll>>(n+1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                hashes[i][t] = (P[t] * hashes[i-1][t] + s[i-1]) % MOD[t];
            }
        }
    }

    RollingHash(string s) : s(s), n(s.size()) {
        _buildpowers();
        _buildhashes();
    }

    vector<ll> gethash(int l, int r) {
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (hashes[r][t] - (powers[r-l][t] * hashes[l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return result;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    string s(2*n, ' ');
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        s[i] = s[i+n] = (char) ('a' + ai);
    }
    string t(m, ' ');
    for (int i = 0; i < m; ++i) {
        int bi;
        cin >> bi;
        t[i] = (char) ('a' + bi);
    }
    // cout << s << endl << t << endl;

    set<pair<ll, ll>> hashes;
    for (int rev = 0; rev < 2; ++rev) {
        RollingHash h(s);
        for (int i = 0; i < n; ++i) {
            vector<ll> hash = h.gethash(i, i+m);
            hashes.insert(make_pair(hash[0], hash[1]));
        }

        reverse(s.begin(), s.end());
    }

    RollingHash h(t);
    vector<ll> hash = h.gethash(0, m);
    if (hashes.find(make_pair(hash[0], hash[1])) != hashes.end()) {
        cout << 1;
    } else {
        cout << 0;
    }
}

int main() {
    solve();
    return 0;
}