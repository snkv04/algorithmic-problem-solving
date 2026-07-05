#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n;
vector<ll> a, depth, max_depth, sum, weighted_sum, orig, ans, best_delta;
vector<vector<int>> adj;

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
    sum[node] = a[node];
    weighted_sum[node] = a[node] * depth[node];
    max_depth[node] = depth[node];
    for (int next : adj[node]) {
        if (next == parent) continue;

        depth[next] = depth[node] + 1;
        dfs(next, node);
        max_depth[node] = max(max_depth[node], max_depth[next]);
        sum[node] += sum[next];
        weighted_sum[node] += weighted_sum[next];
    }
    orig[node] = weighted_sum[node] - sum[node] * depth[node];
}

void dfs2(int node, int parent) {
    multiset<ll> sums, max_depths;
    for (int next : adj[node]) {
        if (next == parent) continue;

        sums.insert(sum[next]);
        max_depths.insert(max_depth[next]);
        dfs2(next, node);
    }

    best_delta[node] = 0;
    for (int next : adj[node]) {
        if (next == parent) continue;

        best_delta[node] = max(best_delta[node], best_delta[next]);
        max_depths.erase(max_depths.find(max_depth[next]));
        if (max_depths.size()) {
            best_delta[node] = max(best_delta[node], (*max_depths.rbegin() - depth[node]) * sum[next]);
        }
        max_depths.insert(max_depth[next]);
    }
    ans[node] = orig[node] + best_delta[node];
}

void solve() {
    cin >> n;
    a.resize(n);
    cin >> a;
    adj.clear();
    adj.resize(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth = vector<ll>(n, 0);
    max_depth = depth; sum = depth; orig = depth; weighted_sum = depth;
    dfs(0, -1);

    ans = vector<ll>(n, 0);
    best_delta = vector<ll>(n, 0);
    dfs2(0, -1);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i == n - 1];
    }
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
