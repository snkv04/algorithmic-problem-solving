#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<int> subtree_size;
vector<ll> sum_dists;
ll ans;

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

void dfs(int node, int parent) {
    subtree_size[node] = 1;
    for (int next : adj[node]) {
        if (next == parent) continue;

        dfs(next, node);
        subtree_size[node] += subtree_size[next];
        sum_dists[node] += sum_dists[next] + (subtree_size[next] - 1) + 2;
    }
}

void dfs2(int node, int parent) {
    ans += sum_dists[node];
    for (int next : adj[node]) {
        if (next == parent) continue;

        sum_dists[node] -= sum_dists[next] + subtree_size[next] + 1;
        subtree_size[node] -= subtree_size[next];
        subtree_size[next] += subtree_size[node];
        sum_dists[next] += sum_dists[node] + subtree_size[node] + 1;

        dfs2(next, node);

        sum_dists[next] -= sum_dists[node] + subtree_size[node] + 1;
        subtree_size[next] -= subtree_size[node];
        sum_dists[node] += sum_dists[next] + subtree_size[next] + 1;
        subtree_size[node] += subtree_size[next];
    }
}

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;

    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll i) {
    return mod_pow(i, MOD - 2);
}

ll mod_div(ll num, ll denom) {
    return num * mod_inv(denom) % MOD;
}

void solve() {
    // reads in input
    int n, k;
    cin >> n >> k;
    if (k % 2) {
        cout << 1 << endl;
        return;
    }

    // builds tree
    assert(k == 2);
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // finds sum of distances from node 0 to all other nodes
    subtree_size = vector<int>(n, 0);
    sum_dists = vector<ll>(n, 0);
    dfs(0, -1);

    // does tree rerooting DP to find sum of distances from each node to all other nodes
    ans = 0;
    dfs2(0, -1);
    ans /= 2;
    ans %= MOD;

    // finds final answer with O(1) calculation
    ll num_pairs = 1LL * n * (n - 1) / 2;
    num_pairs %= MOD;  // always make all operands within the mod range ASAP
    ans = mod_div(ans, num_pairs);
    cout << ans << '\n';
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
