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
    /*
    - generalized ideas for the future:
        - in traditional 2-coloring, we want each node to have a different color from its adjacent nodes. in this problem,
        each edge either says that two adjacent nodes need to be the same or different. in order to transform this problem
        to traditional 2-coloring, we can add an extra node in the middle of each "same" edge, so that all pairs of adjacent
        nodes really have to have different colors; this just simplifies the color-checking logic into that of standard
        2-coloring.
        - if we add extra nodes like this, then when counting nodes of interest (such as for component size or number of
        impostors), then make sure to only count the real, original nodes
    */

    // reads in input
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    int added = 0;
    while (m--) {
        int i, j;
        string c;
        cin >> i >> j >> c;
        --i; --j;
        if (c == "crewmate") {
            int new_node = adj.size();
            ++added;
            adj.push_back(vector<int>());

            adj[i].push_back(new_node);
            adj[new_node].push_back(i);
            adj[new_node].push_back(j);
            adj[j].push_back(new_node);
        } else {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }

    // does a BFS to color every component
    vector<int> color(n + added, -1);
    vector<bool> visited(n + added, false);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            // arbitrarily color this start node as an impostor
            int impostors = 1, comp_size = 0;
            color[i] = 1;

            // BFS, coloring all nodes (and also keeping track of impostors)
            queue<int> q;
            q.push(i);
            while (q.size()) {
                // visit the node
                int node = q.front();
                q.pop();
                if (visited[node]) continue;
                visited[node] = true;
                if (node < n) comp_size += 1;

                // check adjacent nodes
                for (int next : adj[node]) {
                    int next_color = color[node] ^ 1;
                    if (color[next] == -1) {
                        color[next] = next_color;
                        if (next < n) impostors += next_color;
                        q.push(next);
                    } else if (color[next] != next_color) {
                        cout << "-1\n";
                        return;
                    }
                }
            }

            // add maximum number of impostors (which will either be the count of impostors we colored
            // or the complement)
            ans += max(impostors, comp_size - impostors);
        }
    }
    cout << ans << '\n';
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
