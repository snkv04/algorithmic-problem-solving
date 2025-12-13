#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int rows, cols;
vector<string> grid;

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

struct DSU {
    int n;
    vector<int> parent;

    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        else return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
        }
    }
};

int idx(int r, int c) {
    return r * cols + c;
}

void solve() {
    ifstream cin("cave.in");
    ofstream cout("cave.out");

    cin >> rows >> cols;
    grid.resize(rows);
    for (int r = 0; r < rows; ++r) {
        cin >> grid[r];
    }

    vector<ll> dp(rows * cols, 1);
    DSU dsu(rows * cols);
    for (int r = rows - 2; r >= 1; --r) {
        for (int c = 1; c < cols - 1; ++c) {
            if (grid[r][c] == '.' && grid[r][c] == grid[r][c+1]) {
                dsu.unite(idx(r, c), idx(r, c+1));
            }
        }

        for (int c = 1; c < cols; ++c) {
            if (grid[r][c] == '.' && grid[r][c] == grid[r+1][c] && dsu.find(idx(r, c)) != dsu.find(idx(r+1, c))) {
                int above = dsu.find(idx(r, c)), below = dsu.find(idx(r+1, c));
                dp[above] = (dp[above] * dp[below]) % MOD;
                dsu.unite(above, below);
            }
        }

        unordered_set<int> seen;
        for (int c = 1; c < cols; ++c) {
            int index = idx(r, c);
            if (grid[r][c] == '.' && seen.find(dsu.find(index)) == seen.end()) {
                dp[dsu.find(index)] += 1;
                seen.insert(dsu.find(index));
            }
        }
    }

    ll ans = 1;
    unordered_set<int> seen;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int index = idx(r, c);
            if (grid[r][c] == '.' && seen.find(dsu.find(index)) == seen.end()) {
                ans = (ans * dp[dsu.find(index)]) % MOD;
                seen.insert(dsu.find(index));
            }
        }
    }
    cout << ans << "\n";
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
