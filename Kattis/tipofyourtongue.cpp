#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
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

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    map<pair<ll, ll>, int> pre, suf;
    map<pair<pair<ll, ll>, pair<ll, ll>>, int> both;
    // map<string, int> _pre, _suf;
    // map<pair<string, string>, int> _both;
    while (n--) {
        string s;
        cin >> s;
        RollingHash hash(s);
        int len = s.size();
        for (int i = 1; i <= len; ++i) {
            pair<ll, ll> prefix = hash.get_hash(0, i), suffix = hash.get_hash(len-i, len);
            pre[prefix] += 1;
            suf[suffix] += 1;
            both[make_pair(prefix, suffix)] += 1;

            // _pre[s.substr(0, i)] += 1;
            // _suf[s.substr(len-i, len)] += 1;
            // _both[make_pair(s.substr(0, i), s.substr(len-i, len))] += 1;
        }
    }
    // print_container(_pre, "_pre = ");
    // print_container(_suf, "_suf = ");
    // print_container(_both, "_both = ");
    while (q--) {
        string type, p, s;
        cin >> type >> p >> s;
        RollingHash prerolling(p), sufrolling(s);
        pair<ll, ll> prehash = prerolling.get_hash(0, p.size()), sufhash = sufrolling.get_hash(0, s.size());
        if (type == "AND") {
            if (both.find(make_pair(prehash, sufhash)) == both.end()) {
                cout << "0\n";
            } else {
                cout << both[make_pair(prehash, sufhash)] << "\n";
            }
        } else if (type == "OR") {
            int A = pre.find(prehash) == pre.end() ? 0 : pre[prehash];
            int B = suf.find(sufhash) == suf.end() ? 0 : suf[sufhash];
            int AnB = both.find(make_pair(prehash, sufhash)) == both.end() ? 0 : both[make_pair(prehash, sufhash)];
            cout << A + B - AnB << "\n";
        } else {
            int A = pre.find(prehash) == pre.end() ? 0 : pre[prehash];
            int B = suf.find(sufhash) == suf.end() ? 0 : suf[sufhash];
            int AnB = both.find(make_pair(prehash, sufhash)) == both.end() ? 0 : both[make_pair(prehash, sufhash)];
            cout << A + B - 2 * AnB << "\n";
        }
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
