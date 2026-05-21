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

vector<ll> dijkstras(int start, vector<vector<pair<int, int>>> &adj, vector<bool> &horse, int n) {
    /*
    - basically, we are simply doing dijkstras on an augmented graph, where each node has a state of
    "have seen horse" or "have not seen horse"
    - to remember for future: we create an augmented graph implicitly (using same edges as original graph),
    run SSSP on that augmented graph, then use it to reason about the original graph
    */

    // initializes distances based on whether start node had a horse or not
    vector<ll> dist(2*n, 1e18);
    priority_queue<pair<ll, int>> pq;
    if (horse[start]) {
        pq.push(make_pair(0, 2*start + 1));
        dist[2*start+1] = 0;
    } else {
        pq.push(make_pair(0, 2*start));
        dist[2*start] = 0;
    }

    // runs dijkstra's
    while (pq.size()) {
        auto [negdist, augmented] = pq.top();  // augmented = node idx in new graph
        pq.pop();
        int base = augmented / 2;  // base = node idx in original graph (so in [0, n-1])
        ll distance = -negdist;
        if (distance > dist[augmented]) continue;

        for (auto [nextbase, weight] : adj[base]) {
            ll newweight, nextaug;
            if (augmented % 2) {
                newweight = weight / 2;
                nextaug = nextbase * 2 + 1;
            } else {
                newweight = weight;
                if (horse[nextbase]) {
                    nextaug = nextbase * 2 + 1;
                } else {
                    nextaug = nextbase * 2;
                }
            }

            if (distance + newweight < dist[nextaug]) {
                dist[nextaug] = distance + newweight;
                pq.push(make_pair(-dist[nextaug], nextaug));
            }
        }
    }

    // collapses information from different states of a node into a single state per node
    vector<ll> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = min(dist[2*i], dist[2*i+1]);
    }
    return res;
}

void solve() {
    // reads in input
    int n, m, h;
    cin >> n >> m >> h;
    vector<bool> horse(n, false);
    while (h--) {
        int hi;
        cin >> hi;
        --hi;
        horse[hi] = true;
    }
    vector<vector<pair<int, int>>> adj(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    // gets distance of every node if start node is 0 and start node is n-1,
    // assuming we take a horse as soon as possible
    vector<ll> dist1 = dijkstras(0, adj, horse, n), dist2 = dijkstras(n-1, adj, horse, n);

    // checks all meeting points
    ll ans = 1e18;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, max(dist1[i], dist2[i]));  // the other person will wait at the meeting node
    }
    cout << (ans == 1e18 ? -1 : ans) << '\n';
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
