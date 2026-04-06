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

int dfs(int node, int u, vector<int> &prev, vector<vector<int>> &adj) {
    // this is pretty much just a sneaky trick to ensure that if we are already at a node
    // adjacent to u, then we don't take a roundabout path to u. basically, if we only have
    // 4 nodes adjacent to u, then we don't want our cycle to consume 3 of them, only 2. it works
    // by moving u to the front of the adjacency list, if u is present in it
    sort(adj[node].begin(), adj[node].end(), [&](int a, int b) { return abs(a-u) < abs(b-u); });

    // goes through adjacent nodes
    for (int next : adj[node]) {
        // if we went in a cycle and can reach u again, then we're done
        if (next == u && prev[node] != u) {
            return node;
        }

        // visits other unvisited nodes
        if (prev[next] == -1 && next != u) {
            prev[next] = node;
            int res = dfs(next, u, prev, adj);
            if (res != -1) return res;
        }
    }
    return -1;
}

void solve() {
    // reads in the graph
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // iterates through possible values of node u which have degree 4
    for (int u = 0; u < n; ++u) {
        if (adj[u].size() >= 4) {
            // checks if there's a cycle; if there is, then v = the last node on the path from u
            // before reaching u again
            vector<int> prev(n, -1);
            int v = dfs(u, u, prev, adj);
            if (v != -1) {
                // adds edge (u, v) to fish graph
                vector<pair<int, int>> fish;
                fish.push_back({u, v});

                // adds all edges from path from u to v to fish graph, keeping track of the nodes
                // on the path because we care about which nodes adjacent to u have been used
                unordered_set<int> used;
                while (v != u) {
                    fish.push_back({v, prev[v]});
                    used.insert(v);
                    v = prev[v];
                }

                // gets the other 2 nodes adjacent to u
                int cnt = 0;
                for (auto v_i : adj[u]) {
                    if (used.find(v_i) == used.end()) {
                        fish.push_back({u, v_i});
                        ++cnt;
                    }

                    if (cnt == 2) {
                        break;
                    }
                }

                // prints out the fish graph
                cout << "YES\n";
                cout << fish.size() << '\n';
                for (auto [a, b] : fish) cout << a + 1 << ' ' << b + 1 << '\n';
                return;
            }
        }
    }
    cout << "NO\n";
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
