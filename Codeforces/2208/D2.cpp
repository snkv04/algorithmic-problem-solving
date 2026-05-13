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

void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[node] = true;
    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next, adj, visited);
        }
    }
}

void solve() {
    // reads in input
    int n;
    cin >> n;
    vector<vector<bool>> s(n, vector<bool>(n, false));
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; ++i) {
        string si;
        cin >> si;
        for (int j = 0; j < n; ++j) {
            s[i][j] = si[j] == '1';
            if (s[i][j]) {
                cnt[i] += 1;
            }
        }
    }

    // sorts nodes by reachability count
    vector<int> sorted(n);
    for (int i = 0; i < n; ++i) sorted[i] = i;
    sort(sorted.begin(), sorted.end(), [&](int a, int b) {
        return cnt[a] > cnt[b];
    });

    // builds tree
    vector<vector<int>> adj(n);
    int edge_count = 0;
    vector<int> processed(n, false);
    for (int i = 0; i < n; ++i) {
        int u = sorted[i];
        fill(processed.begin(), processed.end(), false);
        for (int j = i + 1; j < n; ++j) {
            int v = sorted[j];
            if (s[u][v] && !processed[v]) {
                processed[v] = true;
                adj[u].push_back(v);
                ++edge_count;

                // critical piece!
                if (edge_count >= n) {
                    cout << "no\n";
                    return;
                }

                for (int k = j + 1; k < n; ++k) {
                    int w = sorted[k];
                    if (s[v][w]) {
                        processed[w] = true;
                    }
                }
            }
        }
    }

    // checks that the given reachability matrix is correct, by:
    // (1) checking that the edges form an undirected tree
    // (1.1) checking that the number of edges is correct
    // (1.2) checking that the graph is connected
    // (2) making a reachability matrix based on the constructed tree
    bool num_edges_valid = edge_count == n - 1;
    bool connected_valid = true;
    DSU dsu(n);
    for (int i = 0; i < n; ++i) for (int j : adj[i]) dsu.join(i, j);
    if (dsu.size(0) != n) connected_valid = false;
    bool reachability_valid = true;
    vector<vector<bool>> r(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n, false);
        dfs(i, adj, visited);
        for (int j = 0; j < n; ++j) {
            if (visited[j]) {
                r[i][j] = true;
            }
        }
    }
    for (int i = 0; i < n && reachability_valid; ++i) {
        for (int j = 0; j < n; ++j) {
            if (r[i][j] != s[i][j]) {
                reachability_valid = false;
                break;
            }
        }
    }

    // prints out tree if valid
    if (num_edges_valid && connected_valid && reachability_valid) {
        cout << "yes\n";
        for (int i = 0; i < n; ++i) {
            for (int j : adj[i]) {
                cout << i + 1 << " " << j + 1 << "\n";
            }
        }
    } else {
        cout << "no\n";
    }
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
