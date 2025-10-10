#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<ll> P = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009}; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

struct Hasher {
    size_t operator()(const pair<ll, ll> &a) const {
        return (1e9 + 9) * a.first + a.second;
    }
};

struct Equals {
    bool operator()(const pair<ll, ll> &a, const pair<ll, ll> &b) const {
        return a.first == b.first && a.second == b.second;
    }
};

vector<vector<ll>> hashes;
vector<vector<ll>> ppow;

pair<ll, ll> gethash(int l, int r) {
    vector<ll> result(2, 0);
    for (int t = 0; t < 2; ++t) {
        result[t] = (hashes[r+1][t] - ((hashes[l][t] * ppow[r-l+1][t]) % MOD[t]) + MOD[t]) % MOD[t];
    }
    return make_pair(result[0], result[1]);
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    string is_good; cin >> is_good;
    int k; cin >> k;

    ppow = vector<vector<ll>>(n+1, vector<ll>(2, 1));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= n; ++i) {
            ppow[i][t] = (ppow[i-1][t] * P[t]) % MOD[t];
        }
    }

    hashes = vector<vector<ll>>(n+1, vector<ll>(2, 0));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= n; ++i) {
            hashes[i][t] = (hashes[i-1][t] * P[t] + s[i-1]) % MOD[t];
        }
    }

    unordered_set<pair<ll, ll>, Hasher, Equals> distinct;
    for (int i = 0; i < n; ++i) {
        int bad = 0;
        for (int j = i; j < n; ++j) {
            if (is_good[s[j] - 'a'] == '0') ++bad;
            if (bad > k) {
                break;
            }

            distinct.insert(gethash(i, j));
        }
    }
    cout << distinct.size() << "\n";
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
