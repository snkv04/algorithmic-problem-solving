#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
int cnt;
vector<int> depth, parity, pre_sum;

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
    if (adj[node].size() == 1) {
        cnt += 1;
        parity[node] = 1;
    }

    for (int next : adj[node]) {
        if (next == parent) continue;

        depth[next] = depth[node] + 1;
        dfs(next, node);
        parity[node] ^= parity[next];
    }
}

void dfs2(int node, int parent) {
    pre_sum[node] = parity[node] + (parent == -1 ? 0 : pre_sum[parent]);

    for (int next : adj[node]) {
        if (next == parent) continue;
        dfs2(next, node);
    }
}

void solve() {
    int n;
    cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root;
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() > 1) {
            root = i;
            break;
        }
    }

    cnt = 0;
    depth = vector<int>(n, 0);
    parity = vector<int>(n, 0);
    dfs(root, -1);
    pre_sum = vector<int>(n, 0);
    dfs2(root, -1);

    int sum = 0;
    for (int i = 0; i < n; ++i) sum += parity[i];
    if (cnt & 1) {
        int ans = 1e9;
        for (int i = 0; i < n; ++i) {
            if (adj[i].size() == 1) {
                int odd = pre_sum[i], even = depth[i] + 1 - odd;
                ans = min(ans, sum - odd + even);
            }
        }
        cout << ans << endl;
    } else {
        cout << sum << endl;
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
