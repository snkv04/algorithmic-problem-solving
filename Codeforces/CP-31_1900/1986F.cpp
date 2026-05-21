#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<set<int>> adj2;
vector<int> pre, low_pre, scc, sz;
stack<int> stk;
vector<bool> on_stk;
int timer, n;
ll ans;

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

void dfs(int node, int parent) {
    pre[node] = low_pre[node] = timer++;
    stk.push(node);
    on_stk[node] = true;

    for (int next : adj[node]) {
        if (next == parent) continue;

        if (pre[next] == -1) dfs(next, node);
        if (on_stk[next]) low_pre[node] = min(low_pre[node], low_pre[next]);
    }

    // postorder processing
    if (pre[node] == low_pre[node]) {
        while (stk.size()) {
            int top = stk.top();
            stk.pop();
            on_stk[top] = false;
            scc[top] = node;
            ++sz[node];

            if (top == node) break;
        }
    }
}

int dfs2(int node, int parent) {
    int subtree_size = sz[node];
    for (int next : adj2[node]) {
        if (next == parent) continue;

        int child_subtree_size = dfs2(next, node);
        ans = max(ans, 1LL * child_subtree_size * (n - child_subtree_size));
        subtree_size += child_subtree_size;
    }
    return subtree_size;
}

void solve() {
    // makes graph
    int m;
    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < n; ++i) adj[i].clear();
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // finds SCCs (or, more rigorously, 2-edge-connected components)
    timer = 0;
    pre.resize(n); fill(pre.begin(), pre.end(), -1);
    low_pre.resize(n); fill(low_pre.begin(), low_pre.end(), -1);
    scc.resize(n); fill(scc.begin(), scc.end(), -1);
    sz.resize(n); fill(sz.begin(), sz.end(), 0);
    on_stk.resize(n); fill(on_stk.begin(), on_stk.end(), false);
    dfs(0, -1);

    // checks if there are no bridges
    bool multiple_comps = false;
    for (int i = 1; i < n; ++i) if (scc[i] != scc[0]) { multiple_comps = true; break; }
    if (!multiple_comps) {
        cout << 1LL * n * (n - 1) / 2 << endl;
        return;
    }

    // builds condensed graph
    adj2.resize(n);
    for (int i = 0; i < n; ++i) adj2[i].clear();
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            if (scc[u] == scc[v]) continue;

            adj2[scc[u]].insert(scc[v]);
            adj2[scc[v]].insert(scc[u]);
        }
    }

    // finds bridge that separates the most nodes
    ans = 0;
    dfs2(0, -1);
    ans = 1LL * n * (n - 1) / 2 - ans;
    cout << ans << endl;
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
