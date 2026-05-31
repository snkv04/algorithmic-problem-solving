#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n, k;
vector<int> w, c;
vector<vector<int>> adj;
vector<set<int>> colors;
ll ans = 0;

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
    set<int> collisions;
    for (int next : adj[node]) {
        if (next == parent) continue;

        dfs(next, node);
        if (colors[next].size() > colors[node].size()) std::swap(colors[node], colors[next]);
        for (int c : colors[next]) {
            if (colors[node].count(c)) {
                collisions.insert(c);
            }
            colors[node].insert(c);
        }
    }

    if (collisions.size() > 1) {
        ans += w[node];
        if (!c[node]) c[node] = *collisions.begin();
    } else if (collisions.size() == 1) {
        if (c[node]) {
            if (c[node] == *collisions.begin()) {
                // answer does not increase
                // don't have to color node
            } else {
                ans += w[node];
            }
        } else {
            c[node] = *collisions.begin();
        }
    } else {
        if (!c[node] && colors[node].size()) {
            c[node] = *(colors[node].begin());
        }
    }

    if (c[node]) colors[node].insert(c[node]);
}

void dfs2(int node, int parent) {
    for (int next : adj[node]) {
        if (next == parent) continue;

        if (!c[next]) c[next] = c[node];
        dfs2(next, node);
    }
}

void solve() {
    cin >> n >> k;
    w = vector<int>(n); c = vector<int>(n);
    cin >> w >> c;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // base case
    int cnt0 = 0;
    for (int i = 0; i < n; ++i) cnt0 += c[i] == 0;
    if (cnt0 == n) {
        cout << "0\n";
        for (int i = 0; i < n; ++i) cout << "1 ";
        cout << "\n";
        return;
    }

    // up-propagation
    ans = 0;
    colors = vector<set<int>>(n);
    dfs(0, -1);

    // down-propagation
    dfs2(0, -1);

    cout << ans << "\n";
    for (int i = 0; i < n; ++i) cout << c[i] << " ";
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
