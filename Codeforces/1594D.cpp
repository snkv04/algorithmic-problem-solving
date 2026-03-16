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
        - for a given edge (u, v), we can change the determination of which value (0/1) v should take based
        on u and the edge's type FROM being absolute (v is 0 or v is 1) TO being relative (v is the same as u
        or v is different from u), and vice versa; it's just a perspective shift
        - we can simply transform the directed edges into undirected edges, since they actually enforce
        constraints both ways (as either both nodes must be the same or they must be different)
        - why do we need both `visited` and `color`? because when we step onto a node, its color is guaranteed
        to have already been set, so we can't use that for checking visited status.
    */

    // reads in input
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, bool>>> adj(n);
    while (m--) {
        int i, j;
        string c;
        cin >> i >> j >> c;
        --i; --j;
        bool weight = c == "imposter";
        adj[i].push_back(make_pair(j, weight));
        adj[j].push_back(make_pair(i, weight));
    }

    // does a BFS to color every component
    vector<int> color(n, -1);
    vector<bool> visited(n, false);
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
                int node = q.front();
                q.pop();
                if (visited[node]) continue;
                visited[node] = true;
                comp_size += 1;

                for (auto [next, weight] : adj[node]) {
                    int next_color = color[node] ^ ((int) weight);
                    if (color[next] == -1) {
                        color[next] = next_color;
                        impostors += next_color;
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
