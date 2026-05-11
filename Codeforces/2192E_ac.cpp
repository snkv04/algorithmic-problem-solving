#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

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

void dfs(
    int node,
    vector<vector<pair<int, int>>> &adj,
    vector<bool> &crossed,
    vector<int> &color,
    vector<int> &a
) {
    while (adj[node].size()) {
        auto [next, idx] = adj[node].back();
        adj[node].pop_back();
        if (crossed[idx]) continue;

        crossed[idx] = true;
        // literally just orients edge to go along with traversal,
        // because the traversal ensures that each node has an equal number
        // of edges traversed in the inward direction and edges traversed in the outward direction
        if (node == a[idx]) color[idx] = 0; else color[idx] = 1;
        dfs(next, adj, crossed, color, a);
    }
}

void solve() {
    // reads in values
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;
    vector<int> freq(n, 0);
    for (int i = 0; i < n; ++i) { --a[i]; --b[i]; ++freq[a[i]]; ++freq[b[i]]; }

    // checks frequencies
    for (int i = 0; i < n; ++i) {
        if (freq[i] & 1) {
            cout << "-1\n";
            return;
        }
    }

    // sets up undirected graph, where each node (value) is guaranteed to have even degree,
    // because it appears an even number of times and gets one adjacent edge per appearance
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) continue;

        adj[a[i]].push_back(make_pair(b[i], i));
        adj[b[i]].push_back(make_pair(a[i], i));
    }

    // marks all edges (indices, since we have one edge per index) as flip / no flip
    vector<bool> crossed(n, false);
    vector<int> color(n, -1);
    for (int i = 0; i < n; ++i) {
        dfs(i, adj, crossed, color, a);
    }

    // collects the flipped indices
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) continue;
        if (color[i]) ans.push_back(i + 1);
    }
    cout << ans.size() << "\n";
    for (int idx : ans) cout << idx << " ";
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
