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

struct DijkstrasEntry {
    int node;
    bool flipped;
    ll dist;
};

struct Comp {
    bool operator()(const DijkstrasEntry &e1, const DijkstrasEntry &e2) {
        return e1.dist > e2.dist;
    }
};

void solve() {
    // reads in input and makes both original and transpose graph
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n), adjT(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back(make_pair(v, w));
        adjT[v].push_back(make_pair(u, w));
    }

    // runs dijkstra's on the augmented graph
    vector<vector<ll>> dist(n, vector<ll>(2, 1e18));
    priority_queue<DijkstrasEntry, vector<DijkstrasEntry>, Comp> pq;
    dist[0][0] = 0;
    pq.push({0, false, 0});
    while (pq.size()) {
        // load entry on top of prioqueue
        auto [node, flipped, distance] = pq.top();
        pq.pop();
        if (distance > dist[node][flipped]) continue;

        // if we haven't moved to the flipped graph yet, then we can stay with the original directions or move to it,
        // but if we're already flipped, then we can't go back
        if (!flipped) {
            for (auto [next, weight] : adj[node]) {
                if (dist[next][0] > distance + weight) {
                    dist[next][0] = distance + weight;
                    pq.push({next, 0, dist[next][0]});
                }
            }
        }
        for (auto [next, weight] : adjT[node]) {
            if (dist[next][1] > distance + weight) {
                dist[next][1] = distance + weight;
                pq.push({next, 1, dist[next][1]});
            }
        }
    }

    // gets shortest path to all nodes except start, as required
    for (int i = 1; i < n; ++i) {
        ll ans = min(dist[i][0], dist[i][1]);
        cout << (ans == 1e18 ? -1 : ans) << ' ';
    }
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
