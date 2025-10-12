#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<ll> P = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009};
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<ll>> rolling;
vector<vector<ll>> PPOW;

void buildpowers() {
    PPOW = vector<vector<ll>>(1e6+1, vector<ll>(2, 1));
    for (int i = 1; i <= 1e6; ++i) {
        for (int t = 0; t < 2; ++t) {
            PPOW[i][t] = (PPOW[i-1][t] * P[t]) % MOD[t];
        }
    }
}

void buildhash(string &s) {
    int n = s.size();
    rolling = vector<vector<ll>>(n+1, vector<ll>(2, 0));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= n; ++i) {
            rolling[i][t] = (rolling[i-1][t] * P[t] + static_cast<int>(s[i-1])) % MOD[t];
        }
    }
}

pair<ll, ll> gethash(int l, int r) {
    vector<ll> result(2);
    for (int t = 0; t < 2; ++t) {
        result[t] = (rolling[r+1][t] - ((rolling[l][t] * PPOW[r-l+1][t]) % MOD[t]) + MOD[t]) % MOD[t];
    }
    return make_pair(result[0], result[1]);
}

void solve() {
    /*
    generalizable ideas for the future:
    - when writing the gethash function, make sure to actually use powers of the primes, not
    just the primes themselves lol
    - after getting the prefixes that are also suffixes, we can actually optimize the search
    for the largest one using binary search, and the reason for this is simple: if S is a substring
    of T, then substrings of S are substrings of T, and if S isn't a substring of T, then superstrings
    of S are also not superstrings of T
    */

    string s;
    cin >> s;
    buildpowers();
    buildhash(s);

    vector<int> matching;
    int n = s.size();
    for (int i = 0; i < n-2; ++i) {
        if (gethash(0, i) == gethash(n-i-1, n-1)) {
            matching.push_back(i + 1);
        }
    }

    int l = 0, r = matching.size() - 1, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        int length = matching[m];
        bool works = false;
        for (int i = 1; i + length - 1 <= n - 2; ++i) {
            if (gethash(i, i + length - 1) == gethash(0, length - 1)) {
                works = true;
                break;
            }
        }

        if (works) {
            ans = length;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    if (ans == -1) {
        cout << "Just a legend\n";
    } else {
        cout << s.substr(0, ans) << "\n";
    }
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
