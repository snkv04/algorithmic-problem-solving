#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int maxpow;
vector<int> depth;
vector<vector<int>> ancestor, children;

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

void build_ancestors(int n) {
    for (int i = 1; i <= maxpow; ++i) {
        for (int node = 0; node < n; ++node) {
            int halfway = ancestor[node][i-1];
            if (halfway == -1) {
                ancestor[node][i] = -1;
            } else {
                ancestor[node][i] = ancestor[halfway][i-1];
            }
        }
    }
}

int get_ancestor(int node, int k) {
    if (k > (1 << maxpow)) return -1;

    int curr = node;
    int exp = 0;
    while (k) {
        if (k % 2) {
            curr = ancestor[curr][exp];
        }
        k /= 2;
        ++exp;
        if (curr == -1) {
            return -1;
        }
    }
    return curr;
}

void dfs(int node) {
    for (int next : children[node]) {
        depth[next] = depth[node] + 1;
        dfs(next);
    }
}

int get_lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int diff = depth[b] - depth[a];
        b = get_ancestor(b, diff);
    } else if (depth[b] < depth[a]) {
        int diff = depth[a] - depth[b];
        a = get_ancestor(a, diff);
    }

    if (a == b) {
        return a;
    }

    for (int i = maxpow; i >= 0; --i) {
        if (ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}

void solve() {
    int n, q;
    cin >> n >> q;
    maxpow = std::ceil(std::log2(n));
    ancestor = vector<vector<int>>(n, vector<int>(maxpow+1, -1));
    children = vector<vector<int>>(n);
    depth = vector<int>(n, -1);
    depth[0] = 0;
    for (int i = 1; i < n; ++i) {
        int ei;
        cin >> ei;
        --ei;
        ancestor[i][0] = ei;
        children[ei].push_back(i);
    }
    build_ancestors(n);
    dfs(0);

    while (q--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int lca = get_lca(a, b);
        cout << lca + 1 << "\n";
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
