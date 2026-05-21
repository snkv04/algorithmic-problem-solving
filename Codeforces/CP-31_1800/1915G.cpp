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
    int node_idx, slowness;
    ll distance;
};

bool operator<(const DijkstrasEntry &e1, const DijkstrasEntry &e2) {
    return e1.distance > e2.distance;
}

void solve() {
    // reads in input
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    vector<int> s(n);
    cin >> s;

    // runs Dijkstra's on the augmented graph (graph modeling with state graphs)
    vector<vector<ll>> dist(n, vector<ll>(1001, 1e18));
    priority_queue<DijkstrasEntry> pq;
    dist[0][s[0]] = 0;
    pq.push(DijkstrasEntry{0, s[0], 0});
    while (pq.size()) {
        auto [node_idx, slowness, distance] = pq.top();
        pq.pop();
        if (dist[node_idx][slowness] < distance) continue;

        for (auto [next_idx, weight] : adj[node_idx]) {
            ll time = weight * slowness;
            int new_slowness = min(slowness, s[next_idx]);
            if (distance + time < dist[next_idx][new_slowness]) {
                dist[next_idx][new_slowness] = distance + time;
                pq.push({next_idx, new_slowness, dist[next_idx][new_slowness]});
            }
        }
    }

    // finds min dist across all slowness values at destination node
    ll ans = 1e18;
    for (int i = 0; i <= 1000; ++i) ans = min(ans, dist[n-1][i]);
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
