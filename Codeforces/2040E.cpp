#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<int> par;
vector<int> preorder;

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
    preorder.push_back(node);
    for (int next : adj[node]) {
        if (next == parent) continue;

        par[next] = node;
        dfs(next, node);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    adj = vector<vector<int>>(n + 1);
    par = vector<int>(n + 1, -1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preorder.clear();
    dfs(1, -1);
    // cout << adj << " " << preorder << endl;

    ll mem[n + 1][2][n + 1];
    for (int i = 0; i <= n; ++i) for (int j = 0; j < 2; ++j) fill(mem[i][j], mem[i][j] + n + 1, 1e18);
    for (int node : preorder) {
        if (node == 1) {
            mem[node][1][0] = mem[node][0][0] = 0;
        } else {
            mem[node][1][0] = 1 + mem[par[node]][0][0];
            mem[node][0][0] = 2 * adj[node].size() - 1 + mem[par[node]][1][0];
        }
    }
    for (int c = 1; c <= n; ++c) {
        for (int node : preorder) {
            if (node == 1) {
                mem[node][0][c] = mem[node][1][c] = 0;
            } else {
                mem[node][1][c] = (1 + mem[par[node]][0][c]) % MOD;
                mem[node][0][c] = min(
                    2 * (ll) adj[node].size() - 1 + mem[par[node]][1][c],
                    1 + mem[par[node]][1][c - 1]
                ) % MOD;
            }
        }
    }

    while (q--) {
        int v, p;
        cin >> v >> p;
        cout << mem[v][1][p] << endl;
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
