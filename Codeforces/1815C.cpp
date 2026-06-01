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

void solve() {
    int n, m;
    cin >> n >> m;
    if (n == 1) {
        assert(m == 0);
        cout << "FINITE\n1\n1\n";
        return;
    }

    vector<vector<int>> adj(n + 1);
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (a != 1) {
            adj[b].push_back(a);
        }
    }
    
    vector<int> dist(n + 1, 1e9);
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    while (q.size()) {
        int node = q.front();
        q.pop();
        if (vis[node]) continue;

        vis[node] = true;
        for (int next : adj[node]) {
            if (dist[next] == 1e9) {
                dist[next] = dist[node] + 1;
                q.push(next);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            cout << "INFINITE\n";
            return;
        }
    }

    map<int, set<int>> groups;
    for (int i = 1; i <= n; ++i) groups[dist[i]].insert(i);
    vector<vector<int>> groups_list;
    for (auto [k, v] : groups) {
        groups_list.push_back(vector<int>());
        for (int node : v) {
            groups_list.back().push_back(node);
        }
    }

    vector<int> ans;
    for (int i = groups_list.size() - 1; i >= 0; --i) {
        for (int j = i; j < groups_list.size(); ++j) {
            for (int node : groups_list[j]) {
                ans.push_back(node);
            }
        }
    }

    cout << "FINITE\n";
    cout << ans.size() << "\n";
    for (int node : ans) cout << node << " ";
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
