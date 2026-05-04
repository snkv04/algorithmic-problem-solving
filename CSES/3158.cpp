#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
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
    int n, m;
    cin >> n >> m;
    vector<ll> c(m);
    cin >> c;
    
    vector<vector<pair<int, int>>> adj(n + m);
    for (int i = 0; i < m; ++i) {
        int idx = n + i;
        int k;
        cin >> k;
        vector<int> cities(k);
        cin >> cities; for (int j = 0; j < k; ++j) --cities[j];

        for (int j = 0; j < k; ++j) {
            adj[cities[j]].push_back(make_pair(idx, c[i]));
            adj[idx].push_back(make_pair(cities[j], 0));
        }
    }

    vector<ll> dist(n + m, 1e15);
    dist[0] = 0;
    priority_queue<pair<int, ll>> pq;
    pq.push({0, 0});
    while (pq.size()) {
        auto [node, d] = pq.top();
        d *= -1;
        pq.pop();
        if (d > dist[node]) continue;

        for (auto [next, weight] : adj[node]) {
            if (dist[next] > dist[node] + weight) {
                dist[next] = dist[node] + weight;
                pq.push({next, -dist[next]});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << dist[i] << " ";
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
