#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<int> pre, low;
vector<set<int>> sccs;
stack<int> stk;
vector<bool> onstk;
int timer;
vector<int> a;
vector<int> color;
vector<bool> vis;

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
    pre[node] = low[node] = timer++;
    stk.push(node);
    onstk[node] = true;

    for (int next : adj[node]) {
        if (next == parent) continue;
        if (pre[next] == -1) dfs(next, node);
        if (onstk[next]) low[node] = min(low[node], low[next]);
    }

    if (pre[node] == low[node]) {
        int top = -1;
        sccs.push_back(set<int>());
        do {
            top = stk.top();
            stk.pop();
            onstk[top] = false;
            sccs.back().insert(top);
        } while (top != node);
    }
}

bool is_bipartite(set<int> &nodes) {
    if (nodes.size() == 1) return true;

    queue<int> q;
    int start = *nodes.begin();
    q.push(start);
    color[start] = 0;
    while (q.size()) {
        int node = q.front();
        q.pop();
        if (vis[node]) continue;

        vis[node] = true;
        for (int next : adj[node]) {
            if (!nodes.count(next)) continue;  // only stays within this component

            if (color[next] == -1) {
                color[next] = color[node] ^ 1;
                q.push(next);
            } else if (color[next] == color[node]) {
                return false;
            }
        }
    }
    return true;
}

void solve() {
    int n, m, v;
    cin >> n >> m >> v;
    adj = vector<vector<int>>(n);
    a = vector<int>(n);
    cin >> a;
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    pre = vector<int>(n, -1);
    low = pre;
    onstk = vector<bool>(n, false);
    timer = 0;
    sccs = vector<set<int>>();
    dfs(0, -1);

    ll ans = 1;
    color = vector<int>(n, -1);
    vis = vector<bool>(n, false);
    for (auto scc : sccs) {
        set<int> values;
        for (int node : scc) if (a[node] != -1) values.insert(a[node]);
        bool bipartite = is_bipartite(scc);

        if (values.size() > 1) {
            ans = 0;
            break;
        } else if (values.size() == 1) {
            if (!bipartite) {
                if (*values.begin() != 0) {
                    ans = 0;
                    break;
                }
            } else {
                // multiply by 1 (i.e., do nothing)
            }
        } else {
            if (bipartite) {
                ans *= v;
                ans %= MOD;
            } else {
                // do nothing!
            }
        }
    }
    cout << ans << endl;
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
