#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<ll> P = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009};

struct Quadruplet {
    pair<ll, ll> f, s;

    bool operator==(const Quadruplet &other) const {
        if (f.first != other.f.first) return false;
        if (f.second != other.f.second) return false;
        if (s.first != other.s.first) return false;
        return s.second == other.s.second;
    }
};

struct Hasher {
    size_t operator()(const Quadruplet &q) const {
        ll first = (1e9 + 9) * q.f.second + q.f.first;
        ll second = (1e9 + 9) * q.s.second + q.s.first;
        return (first + 0x9e3779b9) ^ second;
    }
};

vector<vector<vector<ll>>> hashes;
vector<vector<ll>> powers;
vector<vector<Quadruplet>> prefsufhashes;

void build_powers(int highest) {
    powers = vector<vector<ll>>(highest+1, vector<ll>(2, 1));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= highest; ++i) {
            powers[i][t] = (powers[i-1][t] * P[t]) % MOD[t];
        }
    }
}

void build_hashes(int idx, const string &s) {
    hashes[idx] = vector<vector<ll>>(s.size() + 1, vector<ll>(2, 0));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= s.size(); ++i) {
            hashes[idx][i][t] = (hashes[idx][i-1][t] * P[t] + static_cast<int>(s[i-1])) % MOD[t];
        }
    }
}

pair<ll, ll> get_hash(int idx, int l, int r) {
    if (l > r) return make_pair(0, 0);

    pair<ll, ll> hash;
    hash.first = hashes[idx][r+1][0] - ((hashes[idx][l][0] * powers[r-l+1][0]) % MOD[0]);
    if (hash.first < 0) hash.first += MOD[0];
    hash.second = hashes[idx][r+1][1] - ((hashes[idx][l][1] * powers[r-l+1][1]) % MOD[1]);
    if (hash.second < 0) hash.second += MOD[1];
    return hash;
}

void solve() {
    int n;
    cin >> n;

    vector<string> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i].size();
    }
    build_powers(sum);

    unordered_map<Quadruplet, ll, Hasher> prefsuf;
    hashes.resize(n);
    prefsufhashes.resize(n);
    for (int i = 0; i < n; ++i) {
        int len = a[i].size();
        build_hashes(i, a[i]);
        
        prefsufhashes[i] = vector<Quadruplet>(len);
        for (int j = 0; j < len; ++j) {
            Quadruplet q = {get_hash(i, 0, j-1), get_hash(i, j+1, len-1)};
            prefsufhashes[i][j] = q;
            prefsuf[q] += 1;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        int ans = 0;
        int len = a[i].size();
        for (int j = 0; j < a[i].size(); ++j) {
            ans += prefsuf[prefsufhashes[i][j]] - 1;
        }
        cout << ans << "\n";
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
