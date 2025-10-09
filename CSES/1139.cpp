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

vector<int> color;
vector<vector<int>> adj;
vector<int> ans;

set<int> dfs(int node, int parent) {
    set<int> colors = {color[node]};
    for (int next : adj[node]) {
        if (next == parent) continue;

        set<int> child_colors = dfs(next, node);
        if (colors.size() < child_colors.size()) {
            std::swap(colors, child_colors);
        }
        for (int color : child_colors) {
            colors.insert(color);
        }
    }
    ans[node] = colors.size();
    return colors;
}

void solve() {
    /*
    - there are N colors (one per node)
    - each color gets moved/copied at most O(log(N)) times
        - this is the main difference from not using small-to-large merging; if not using it,
        then each color gets moved/copied at most O(N) times
    - the complexity of each copy is O(log(N)) (if using ordered set)
    - therefore, O(N * log^2(N))
    - an interesting thing about analyzing the complexity for this algorithm is that instead of
    considering the number of times that a merge occurs, we're looking at the number of times that
    an element gets moved across all merges. that makes it easier to find the time complexity
    */

    int n;
    cin >> n;

    color.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> color[i];
    }

    adj.resize(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ans.resize(n);
    dfs(0, -1);
    for (int num : ans) cout << num << " ";
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
