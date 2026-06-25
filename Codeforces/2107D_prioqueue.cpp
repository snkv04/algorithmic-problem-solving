#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<set<int>> adj;
vector<bool> visited;
vector<int> dist, previous;
vector<int> curr;

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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

void dfs(int node, int parent) {
    curr.push_back(node);
    for (int next : adj[node]) {
        if (next == parent) continue;

        dist[next] = dist[node] + 1;
        dfs(next, node);
    }
}

int get_endpoint() {
    int maxd = -1;
    for (int node : curr) maxd = max(maxd, dist[node]);

    int result = -1;
    for (int node : curr) {
        if (dist[node] == maxd) result = max(result, node);
    }
    return result;
}

int maxd() {
    int result = -1;
    for (int node : curr) result = max(result, dist[node]);
    return result;
}

array<int, 3> diam(int start) {
    dist[start] = 0;
    curr.clear();
    dfs(start, -1);
    start = get_endpoint();

    dist[start] = 0;
    curr.clear();
    dfs(start, -1);
    int u = get_endpoint();

    dist[u] = 0;
    curr.clear();
    dfs(u, -1);
    int v = get_endpoint();

    if (u < v) swap(u, v);
    return {maxd() + 1, u, v};
}

void dfs2(int node, int parent) {
    for (int next : adj[node]) {
        if (next == parent) continue;
        previous[next] = node;
        dfs2(next, node);
    }
}

set<int> get_path(int u, int v) {
    dfs2(u, -1);
    set<int> path;
    int curr = v;
    while (curr != -1) {
        path.insert(curr);
        curr = previous[curr];
    }
    return path;
}

void solve() {
    int n;
    cin >> n;
    adj = vector<set<int>>(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    visited = vector<bool>(n, false);
    priority_queue<array<int, 3>> diams;
    dist = vector<int>(n, -1);
    previous = vector<int>(n, -1);
    diams.push(diam(0));
    while (diams.size()) {
        auto endpoints = diams.top();
        diams.pop();
        for (int i = 0; i < 3; ++i) cout << endpoints[i] + static_cast<bool>(i) << " ";

        previous[endpoints[1]] = -1;
        auto path = get_path(endpoints[1], endpoints[2]);
        vector<int> nexts;
        for (int node : path) {
            visited[node] = true;
            for (int next : adj[node]) {
                adj[next].erase(node);
                if (path.count(next) == 0) {
                    nexts.push_back(next);
                }
            }
            adj[node].clear();
        }

        for (int next : nexts) {
            diams.push(diam(next));
        }
    }
    cout << "\n";
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
