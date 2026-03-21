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

void dfs(int node, int parent, vector<vector<int>> &adj, vector<int> &dist) {
    for (int next : adj[node]) {
        if (next == parent) continue;

        dist[next] = dist[node] + 1;
        dfs(next, node, adj, dist);
    }
}

int get_furthest(vector<int> &dist) {
    int idx = -1, max_dist = -1;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] > max_dist) {
            idx = i;
            max_dist = dist[i];
        }
    }
    return idx;
}

map<int, vector<int>> dist_to_map(vector<int> &dist) {
    map<int, vector<int>> mp;
    for (int i = 0; i < dist.size(); ++i) {
        mp[dist[i]].push_back(i);
    }
    return mp;
}

void solve() {
    // constructs tree
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // finds distances from arbitrary node (0)
    vector<int> dist(n, -1);
    dist[0] = 0;
    dfs(0, -1, adj, dist);

    // finds distances from first endpoint of diameter, and maps distances to node lists
    int end1 = get_furthest(dist);
    vector<int> dist1(n, -1);
    dist1[end1] = 0;
    dfs(end1, -1, adj, dist1);
    auto mp1 = dist_to_map(dist1);

    // finds distances from second endpoint of diameter, and maps distances to node lists
    int end2 = get_furthest(dist1);
    vector<int> dist2(n, -1);
    dist2[end2] = 0;
    dfs(end2, -1, adj, dist2);
    auto mp2 = dist_to_map(dist2);

    // iterates backward through each distance value, using a flag for each node to see if it's been
    // absorbed into the main component already
    int comps = n;
    vector<bool> processed(n, false);  // basically functions as a "visited" array
    processed[end1] = true;  // why? we don't want to double-count the process of connecting end1 and end2.
    vector<int> ans(n+1, 1);
    for (int i = n; i >= 1; --i) {
        // iterates through nodes at this distance from end1
        if (mp1.find(i) != mp1.end()) {
            for (auto node : mp1[i]) {
                if (!processed[node]) {
                    comps -= 1;
                    processed[node] = true;
                }
            }
        }

        // iterates through nodes at this distance from end2
        if (mp2.find(i) != mp2.end()) {
            for (auto node : mp2[i]) {
                if (!processed[node]) {
                    comps -= 1;
                    processed[node] = true;
                }
            }
        }

        // breaks if we can't get any fewer components
        ans[i] = comps;
        if (comps == 1) break;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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
