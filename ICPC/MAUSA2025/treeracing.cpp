#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Racer {
    int idx, start;
    ll speed;

    Racer() : idx(-1) {}

    Racer(int idx, int start, ll speed) : idx(idx), start(start), speed(speed) {}
};

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<Racer> racers;
vector<bool> special;
int finish;
vector<ll> ans;
vector<vector<Racer>> reached;
int k;
vector<int> depth;

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

void dfs(int node, int parent) {
    if (racers[node].idx != -1) {
        reached[node].push_back(racers[node]);
    }

    for (int next : adj[node]) {
        if (next == parent) continue;

        dfs(next, node);
        if (reached[next].size() >= reached[node].size()) {
            swap(reached[next], reached[node]);
        }
        for (Racer r : reached[next]) {
            reached[node].push_back(r);
        }
    }

    if (special[node]) {
        // filter out racers
        sort(reached[node].begin(), reached[node].end(), [&](Racer &a, Racer &b) {
            ll timea = (depth[a.start] - depth[node]) * a.speed;
            ll timeb = (depth[b.start] - depth[node]) * b.speed;
            if (timea != timeb) {
                return timea < timeb;
            } else {
                return a.speed < b.speed;
            }
        });

        vector<Racer> newreached;
        for (int i = 0; i < min(k, (int)reached[node].size()); ++i) {
            newreached.push_back(reached[node][i]);
        }
        reached[node] = newreached;
    }
}

void getdepths(int node, int parent) {
    for (int next : adj[node]) {
        if (next == parent) continue;

        depth[next] = depth[node] + 1;
        getdepths(next, node);
    }
}

void solve() {
    int n, m;
    cin >> n >> m >> k;
    adj.resize(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    racers = vector<Racer>(n);
    for (int i = 0; i < m; ++i) {
        int p, t;
        cin >> p >> t;
        --p;
        racers[p] = Racer{i, p, t};
    }
    cin >> finish;
    --finish;
    special = vector<bool>(n, false);
    int c;
    cin >> c;
    while (c--) {
        int node;
        cin >> node;
        --node;
        special[node] = true;
    }

    depth.resize(n);
    depth[finish] = 0;
    getdepths(finish, -1);

    ans.resize(m);
    fill(ans.begin(), ans.end(), -1);
    reached.resize(n);
    dfs(finish, -1);

    for (Racer winner : reached[finish]) {
        int idx = winner.idx, start = winner.start;
        ll speed = winner.speed;
        ans[idx] = speed * depth[start];
    }

    for (ll time : ans) cout << time << "\n";
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
