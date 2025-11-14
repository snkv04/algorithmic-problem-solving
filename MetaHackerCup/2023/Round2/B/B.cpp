#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
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
    vector<ll> P = {1000000007, 1000000009};
    vector<ll> MOD = {1000000021, 1000000033};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling, revrolling;
    vector<int> a;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 2, vector<ll>(2, 0));
        revrolling = vector<vector<ll>>(n + 2, vector<ll>(2, 0));        
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                rolling[i][t] = (rolling[i - 1][t] * P[t] + a[i]) % MOD[t];
            }
            for (int i = n; i >= 1; --i) {
                revrolling[i][t] = (revrolling[i + 1][t] * P[t] + a[i]) % MOD[t];
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
    RollingHash(const vector<int> &a) : a(a), n(a.size()) {
        this->a.insert(this->a.begin(), 0);
        _build_hashes();
        _build_powers();
    }

    // l and r are both 1-based, inclusive indices
    pair<ll, ll> get_hash(int l, int r) {
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l-1][t] * PPOW[r-l+1][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }

    pair<ll, ll> get_hash_rev(int l, int r) {
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = (revrolling[l][t] - (revrolling[r+1][t] * PPOW[r-l+1][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

struct DSU {
private:
    int n;
    vector<int> parent, size;

public:
    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        size = vector<int>(n, 1);
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            if (size[c] >= size[d]) {
                parent[d] = c;
                size[c] += size[d];
            } else {
                parent[c] = d;
                size[d] += size[c];
            }
        }
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < 2*n; ++i) {
        if (i < n) cin >> a[i];
        else cin >> b[i-n];
    }
    for (int i = 0; i < 2*n; ++i) {
        b.push_back(a[i]);
        a.push_back(b[i]);
    }
    // cout << "a = " << a << endl;
    // cout << "b = " << b << endl;

    vector<int> prefabove(3*n+1, 0), prefbelow(3*n+1, 0);
    for (int i = 1; i <= 3*n; ++i) {
        prefabove[i] = prefabove[i-1] + (a[i-1] > b[i-1]);
        prefbelow[i] = prefbelow[i-1] + (a[i-1] < b[i-1]);
    }

    RollingHash hasha(a), hashb(b);
    for (int s = 0; s < 2*n; ++s) {
        int l = s + 1, r = s + n;
        if ((r - l + 1) % 2) {
            int m = l + (r - l) / 2;
            if (a[m-1] != b[m-1]) continue;
        }

        int m1 = l + (r - l + 1) / 2 - 1, m2 = r - (r - l + 1) / 2 + 1;
        if (
            prefbelow[m1] - prefbelow[l-1] == m1 - l + 1 &&
            prefabove[r] - prefabove[m2 - 1] == r - m2 + 1 &&
            hasha.get_hash(l, r) == hashb.get_hash_rev(l, r)
        ) {
            cout << s << "\n";
            return;
        }
    }
    cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
