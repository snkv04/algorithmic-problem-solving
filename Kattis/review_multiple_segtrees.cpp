#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> tree;
vector<int> r, t, depth, toidx, counts;
vector<vector<array<int, 3>>> subordinates;
vector<ll> ans;

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

struct Node {
    int v, l, r; // v is probably unnecessary, since the tree uses explicit nodes and not array indices
    ll val;
    Node *left, *right;

    Node(int v, int l, int r) : v(v), l(l), r(r), val(0), left(nullptr), right(nullptr) {}

    Node(int v, int l, int r, ll val) : v(v), l(l), r(r), val(val), left(nullptr), right(nullptr) {}
};

struct SegmentTree {
private:
    int n;
    Node root;

public:
    SegmentTree(int n) : n(n), root(1, 0, n-1) {}
    // SegmentTree(const SegmentTree &other) = delete;
    // SegmentTree(SegmentTree &&moving) = delete;

    void make_children(Node *node) {
        if (node->left == nullptr) {
            int v = node->v, l = node->l, r = node->r;
            int m = l + (r - l) / 2;
            node->left = new Node(v, l, m);
            node->right = new Node(v, m+1, r);
        }
    }

    ll _query(Node *node, int ql, int qr) {
        int l = node->l, r = node->r;
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return node->val;
        }

        make_children(node);
        return _query(node->left, ql, qr) + _query(node->right, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(&root, ql, qr);
    }

    void _update(Node *root, int idx, ll val) {
        if (root->l == root->r) {
            root->val = val;
            return;
        }

        make_children(root);
        int l = root->l, r = root->r;
        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(root->left, idx, val);
        } else {
            _update(root->right, idx, val);
        }
        root->val = root->left->val + root->right->val;
    }

    void update(int idx, ll val) {
        _update(&root, idx, val);
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

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

struct Frac {
    ll num, denom;

    Frac(ll n, ll d) : num(n), denom(d) {
        reduce();
    }

    Frac(ll x) : num(x), denom(1) {}

    bool operator<(const Frac &other) const {
        ll d = lcm(denom, other.denom);
        ll n1 = num * (d / denom), n2 = other.num * (d / other.denom);
        return n1 < n2;
    }

    bool operator==(const Frac &other) const {
        Frac f1 = *this, f2 = other;
        f1.reduce(); f2.reduce();
        return f1.num == f2.num && f1.denom == f2.denom;
    }

    bool operator!=(const Frac &other) const {
        return !((*this) == other);
    }

    bool operator<=(const Frac &other) const {
        return *this < other || *this == other;
    }

    void reduce() {
        ll g = gcd(num, denom);
        num /= g;
        denom /= g;
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    Frac operator+(const Frac &other) {
        ll d = lcm(denom, other.denom);
        ll n1 = num * (d / denom), n2 = other.num * (d / other.denom);
        Frac result(n1 + n2, d);
        result.reduce();
        return result;
    }

    Frac operator-(const Frac &other) {
        return (*this) + (Frac(-1) * other);
    }

    Frac operator*(const Frac &other) {
        Frac result(num * other.num, denom * other.denom);
        result.reduce();
        return result;
    }

    Frac operator/(const Frac &other) {
        Frac recip(other.denom, other.num);
        return (*this) * recip;
    }

    ll sign() {
        reduce();
        if (num == 0) return 0;
        else if (num > 0) return 1;
        else return -1;
    }
};

void dfs(int node) {
    for (int next : tree[node]) {
        depth[next] = depth[node] + 1;
        dfs(next);
    }
}

void dfs2(int node, vector<SegmentTree> &times) {
    for (int child : tree[node]) {
        dfs2(child, times);

        if (counts[child] > counts[node]) {
            swap(counts[node], counts[child]);
            swap(subordinates[node], subordinates[child]);
            swap(times[node], times[child]); // uses move if available, uses copy if move is unavailable
        }
        for (auto descendant : subordinates[child]) {
            subordinates[node].push_back(descendant);
            times[node].update(toidx[descendant[0]], descendant[2]);
        }
        counts[node] += counts[child];
    }

    counts[node] += 1;
    subordinates[node].push_back(array<int, 3>{node, r[node], t[node]});
    int idx = toidx[node];
    times[node].update(idx, t[node]);
    if (idx > 0) {
        ans[node] = times[node].query(0, idx-1);
    } else {
        ans[node] = 0;
    }
    // cout << "processing " << node + 1 << ", st = ";
    // for (int i = 0; i < toidx.size(); ++i) cout << times[node].query(i, i) << " ";
    // cout << endl;
}

void solve() {
    int n;
    cin >> n;
    tree.resize(n);
    r.resize(n);
    t.resize(n);
    int root = -1;
    for (int i = 0; i < n; ++i) {
        int mi;
        cin >> mi >> r[i] >> t[i];
        --mi;
        if (mi >= 0) {
            tree[mi].push_back(i);
        } else {
            root = i;
        }
    }

    depth.resize(n);
    depth[root] = 0;
    dfs(root);

    // get each person's index in sorted order, which will be the same order the segment tree follows
    vector<array<int, 3>> info;
    for (int i = 0; i < n; ++i) info.push_back(array<int, 3>({i, r[i], depth[i]}));
    sort(info.begin(), info.end(), [&](const array<int, 3> &a, const array<int, 3> &b) {
        if (a[1] != b[1]) {
            return a[1] < b[1];
        } else {
            return a[2] < b[2];
        }
    });
    toidx.resize(n);
    for (int i = 0; i < n; ++i) toidx[info[i][0]] = i;

    counts.resize(n);
    subordinates.resize(n);
    // uses the copy constructor, so define the root as a Node and not a Node*
    vector<SegmentTree> times(n, SegmentTree(n)); // segment tree over an array of times for each subordinate, for each person
    ans = vector<ll>(n);
    dfs2(root, times);
    for (ll num : ans) {
        cout << num << "\n";
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
