#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj, adj2;
vector<int> low, pre, scc, coins;
vector<ll> weight, mem;
int timer;
stack<int> stk;
vector<bool> onstk;

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

void dfs(int node) {
    low[node] = pre[node] = timer++;
    stk.push(node);
    onstk[node] = true;

    for (int next : adj[node]) {
        if (pre[next] == -1) dfs(next);

        if (onstk[next]) low[node] = min(low[node], low[next]);
    }

    if (pre[node] == low[node]) {
        int top = -1;
        do {
            top = stk.top();
            stk.pop();
            onstk[top] = false;
            scc[top] = node;
            weight[node] += coins[top];
        } while (top != node);
    }
}

void dfs2(int node) {
    pre[node] = 1;
    mem[node] = weight[node];
    for (int next : adj2[node]) {
        if (!pre[next]) dfs2(next);
        mem[node] = max(mem[node], mem[next] + weight[node]);
    }
}

void solve() {
    // almost the same problem as https://open.kattis.com/problems/thirtynineteen :)

    int n, m;
    cin >> n >> m;
    coins.resize(n);
    cin >> coins;
    adj.resize(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
    }

    low = vector<int>(n, -1);
    pre = low;
    scc = low;
    timer = 0;
    onstk = vector<bool>(n, false);
    weight = vector<ll>(n, 0);
    for (int i = 0; i < n; ++i) {
        if (pre[i] == -1) dfs(i);
    }

    adj2.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j : adj[i]) {
            if (scc[i] != scc[j]) {
                adj2[scc[i]].push_back(scc[j]);
            }
        }
    }

    pre = vector<int>(n, 0);  // not really a preorder, and actually more of a postorder, but doesn't matter
    mem = vector<ll>(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!pre[i] && scc[i] == i) dfs2(i);
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) ans = max(ans, mem[i]);
    cout << ans << endl;
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
