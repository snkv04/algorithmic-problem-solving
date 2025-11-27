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

public:
    SegmentTree(int n) : n(n) {
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return -1e9;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return max(
            _query(2 * v, l, m, ql, qr),
            _query(2 * v + 1, m + 1, r, ql, qr)
        );
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
        t[v] = max(t[2 * v], t[2 * v + 1]);
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
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
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
    vector<int> a(n);
    cin >> a;

    // - mem[i] is the length of the LIS whose last element equal to i
    // - first off, we perform coordinate compression, to map all element values to something in [0, n-1]
    // - note that for any value v, there is some set of indices I such that for all i in I, a[i] = v.
    // when we update mem[v], it will be due to processing some index i in I. now, when we process some i
    // in I to update mem[v], we set mem[v] := 1 + max(mem[w]) where w < v and all mem[w] have only been
    // processed for indices j where j < i.
    // - this can be done by processing all elements from left to right, and for each element, only looking
    // at values that are less than the current element's values that have already been processed.
    set<int> distinct; for (int num : a) distinct.insert(num);
    int counter = 0;
    map<int, int> compressed; for (int num : distinct) compressed[num] = counter++;

    SegmentTree mem(counter);
    for (int i = 0; i < n; ++i) {
        int val = compressed[a[i]];
        int lis = 1;
        if (val != 0) {
            lis = 1 + mem.query(0, val-1);
        }
        mem.update(val, lis);
    }
    cout << mem.query(0, counter-1) << "\n";
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
