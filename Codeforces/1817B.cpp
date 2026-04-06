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

    // iterates through each node u with degree >= 4
    for (int u = 0; u < n; ++u) {
        if (adj[u].size() >= 4) {
            // let {v_1, v_2, ..., v_k} be the nodes adjacent to u
            // we BFS out from u, keeping track of the path each node i takes back to one of the v's
            // using prev[i].first as well as which v started that path using prev[i].second
            vector<pair<int, int>> prev(n, make_pair(-1, -1));
            queue<int> q;
            for (int v : adj[u]) {
                prev[v] = make_pair(v, v);
                q.push(v);
            }

            // as soon as two paths from different v's converge, then we have a cycle
            // think of it like two trees end up having a leaf from each tree being adjacent to each other
            vector<pair<int, int>> fish;
            while (q.size()) {
                int node = q.front();
                q.pop();
                
                for (int next : adj[node]) {
                    if (next == u) continue;

                    if (prev[next].first == -1) {
                        prev[next] = make_pair(node, prev[node].second);
                        q.push(next);
                    } else if (prev[next].second != prev[node].second) {
                        // it's now confirmed that a fish graph exists
                        // add the edge that joins the 2 paths to the result
                        fish.push_back(make_pair(node, next));
                        break;
                    }
                }
                if (fish.size()) {
                    break;
                }
            }

            if (fish.size()) {
                // trace back the two paths that converged; they join together to create a cycle with u
                auto trace = [&](int node) {
                    while (prev[node].first != node) {
                        fish.push_back(make_pair(node, prev[node].first));
                        node = prev[node].first;
                    }
                    return node;
                };
                int v1 = trace(fish[0].first);
                fish.push_back(make_pair(u, v1));
                int v2 = trace(fish[0].second);
                fish.push_back(make_pair(u, v2));

                // find the "tail" nodes (of the fish) that are adjacent to u
                int cnt = 0;
                for (int v : adj[u]) {
                    if (v != v1 && v != v2) {
                        ++cnt;
                        fish.push_back(make_pair(u, v));

                        if (cnt == 2) break;
                    }
                }

                // output the fish graph
                cout << "YES\n";
                cout << fish.size() << '\n';
                for (auto [a, b] : fish) {
                    cout << a + 1 << ' ' << b + 1 << '\n';
                }
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
