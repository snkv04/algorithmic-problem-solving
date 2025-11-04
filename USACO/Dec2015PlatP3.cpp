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

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (int i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

struct SegmentTree {
private:
    int n;
    vector<ll> tsum, tmin, pending;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        tsum = vector<ll>(4*n, 0);
        tmin = vector<ll>(4*n, 1e18);
        pending = vector<ll>(4*n, 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            tsum[v] = tmin[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        tsum[v] = tsum[2*v] + tsum[2*v+1];
        tmin[v] = min(tmin[2*v], tmin[2*v+1]);
    }

    void pushdown(int v, int l, int r) {
        if (pending[v] != 0) {
            tsum[v] += (r - l + 1) * pending[v];
            tmin[v] += pending[v];

            if (l != r) {
                pending[2*v] += pending[v];
                pending[2*v+1] += pending[v];
            }

            pending[v] = 0;
        }
    }

    ll _query(int v, int l, int r, int ql, int qr, char t) {
        pushdown(v, l, r);

        if (r < ql || qr < l) {
            if (t == 'S') {
                return 0;
            } else {
                return 1e18;
            }
        }
        if (ql <= l && r <= qr) {
            if (t == 'S') {
                return tsum[v];
            } else {
                return tmin[v];
            }
        }

        int m = l + (r - l) / 2;
        ll result1 = _query(2 * v, l, m, ql, qr, t);
        ll result2 = _query(2 * v + 1, m + 1, r, ql, qr, t);
        if (t == 'S') {
            return result1 + result2;
        } else {
            return min(result1, result2);
        }
    }

    ll query(int ql, int qr, char t) {
        return _query(1, 0, n - 1, ql, qr, t);
    }

    void _update(int v, int l, int r, int ql, int qr, int val) {
        pushdown(v, l, r);

        if (r < ql || qr < l) {
            return;
        }
        if (ql <= l && r <= qr) {
            pending[v] += val;
            pushdown(v, l, r);
            return;
        }

        int m = l + (r - l) / 2;
        _update(2*v, l, m, ql, qr, val);
        _update(2*v+1, m+1, r, ql, qr, val);
        tsum[v] = tsum[2*v] + tsum[2*v+1];
        tmin[v] = min(tmin[2*v], tmin[2*v+1]);
    }

    void update(int ql, int qr, int val) {
        _update(1, 0, n - 1, ql, qr, val);
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
            parent[d] = c;
            size[c] += size[d];
        }
    }
};

void solve() {
    ifstream cin("haybales.in");
    ofstream cout("haybales.out");

    int n, q;
    cin >> n >> q;
    vector<int> a(n); cin >> a;
    SegmentTree st(a);
    // print_container(st.tsum, "tsum = ");
    // print_container(st.tmin, "tmin = ");
    while (q--) {
        char t;
        cin >> t;
        if (t == 'P') {
            int a, b, c;
            cin >> a >> b >> c;
            --a; --b;
            st.update(a, b, c);
        } else {
            int a, b;
            cin >> a >> b;
            --a; --b;
            cout << st.query(a, b, t) << "\n";
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
