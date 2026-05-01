#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n, m;
vector<vector<int>> adj, adjT;
vector<bool> visited, visited2;
queue<int> reverse_top;

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

void dfs(int node) {
    visited[node] = true;
    for (int next : adjT[node]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
}

void dfs2(int node) {
    visited2[node] = true;
    for (int next : adj[node]) {
        if (visited[next] && !visited2[next]) {
            dfs2(next);
        }
    }
    reverse_top.push(node);
}

void solve() {
    cin >> n >> m;
    adj = vector<vector<int>>(n);
    adjT = vector<vector<int>>(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adjT[b].push_back(a);
    }

    // prune off nodes that can't reach the sink
    visited = vector<bool>(n, false);
    dfs(n - 1);
    if (!visited[0]) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    // gets topological ordering
    visited2 = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        if (visited[i] && !visited2[i]) {
            dfs2(i);
        }
    }

    vector<int> mem(n, 1);
    vector<int> next(n, -1);
    bool seen = false;
    while (reverse_top.size()) {
        int node = reverse_top.front();
        reverse_top.pop();

        pair<int, int> best({-1, 0});
        for (int next : adj[node]) {
            if (visited[next] && mem[next] > best.second) {
                best = {next, mem[next]};
            }
        }
    
        mem[node] = best.second + 1;
        next[node] = best.first;
    }

    cout << mem[0] << "\n";
    int node = 0;
    while (node != -1) {
        cout << node + 1 << " ";
        node = next[node];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
