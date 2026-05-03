#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<pair<int, int>>> adj;
stack<int> stk, edge_stk;
vector<bool> visited;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
}

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

struct DSU {
    DSU(int n) : n(n), comp_size(n, 1) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int node1, int node2) {
        int root1 = find(node1), root2 = find(node2);
        if (root1 != root2) {
            if (comp_size[root1] >= comp_size[root2]) {
                parent[root2] = root1;
                comp_size[root1] += comp_size[root2];
            } else {
                parent[root1] = root2;
                comp_size[root2] += comp_size[root1];
            }
        }
    }

    int size(int node) {
        return comp_size[find(node)];
    }

private:
    int n;
    std::vector<int> parent, comp_size;
};

bool dfs(int node, int parent) {
    visited[node] = true;
    stk.push(node);
    for (auto [next, weight] : adj[node]) {
        if (next == parent) continue;
        
        edge_stk.push(weight);
        if (!visited[next]) {
            if (dfs(next, node)) {
                return true;
            }
        } else {
            return true;
        }
        edge_stk.pop();
    }
    stk.pop();
    return false;
}

void solve() {
    // reads in edges
    int n, m;
    cin >> n >> m;
    vector<array<int, 4>> edges(m);
    for (int i = 0; i < m; ++i) {
        edges[i][0] = i;
        for (int j = 1; j < 4; ++j) cin >> edges[i][j];
        --edges[i][1]; --edges[i][2];
    }
    sort(edges.begin(), edges.end(), [](const array<int, 4> &a, const array<int, 4> &b) {
        return a[3] > b[3];
    });

    // makes maximum-weight spanning forest
    DSU dsu(n);
    vector<bool> used(m, false);
    for (auto [idx, a, b, w] : edges) {
        if (dsu.find(a) != dsu.find(b)) {
            used[idx] = true;
            dsu.join(a, b);
        }
    }
    sort(edges.begin(), edges.end(), [](const array<int, 4> &a, const array<int, 4> &b) {
        return a[3] < b[3];
    });

    // finds edge not in forest, which will form our cycle
    int start;
    for (auto [idx, a, b, w] : edges) {
        if (!used[idx]) {
            used[idx] = true;
            start = a;  // any cycle with a will be the only cycle, because we have a forest before this
            break;
        }
    }

    // DFSes to find that cycle
    adj = vector<vector<pair<int, int>>>(n);
    for (auto [idx, a, b, w] : edges) if (used[idx]) {
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    stk = stack<int>();
    edge_stk = stack<int>();
    visited = vector<bool>(n, false);
    dfs(start, -1);

    // gets the min edge in the cycle and outputs the cycle
    int ans = 1e9;
    while (edge_stk.size()) {
        ans = min(edge_stk.top(), ans);
        edge_stk.pop();
    }
    cout << ans << " " << stk.size() << endl;
    while (stk.size()) {
        cout << stk.top() + 1 << " ";
        stk.pop();
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
