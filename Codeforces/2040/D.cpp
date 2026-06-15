#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<set<int>> available;
vector<int> color;

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
    for (int next : adj[node]) {
        if (next == parent) continue;

        // c - 1
        int below = color[node] - 1;
        if (available[below % 2].count(below)) {
            color[next] = below;
            // cout << "colored node " << next + 1 << " with " << color[next] << endl;
            available[below % 2].erase(below);
            continue;
        }

        // c + 1
        int above = color[node] + 1;
        if (available[above % 2].count(above)) {
            color[next] = above;
            // cout << "colored node " << next + 1 << " with " << color[next] << endl;
            available[above % 2].erase(above);
            continue;
        }

        // all colors of same parity > 2 away
        auto it = available[color[node] % 2].begin();
        while (true) {
            if (abs(color[node] - *it) > 2) {
                color[next] = *it;
                // cout << "colored node " << next + 1 << " with " << color[next] << endl;
                available[color[node] % 2].erase(it);
                break;
            } else {
                ++it;
            }
        }
    }

    for (int next : adj[node]) {
        if (next == parent) continue;
        dfs(next, node);
    }
}

void solve() {
    int n;
    cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    available = vector<set<int>>(2);
    for (int i = 1; i <= 2 * n; ++i) available[i % 2].insert(i);
    color = vector<int>(n, -1);
    color[0] = 2;
    available[0].erase(2);
    dfs(0, -1);
    for (int i = 0; i < n; ++i) cout << color[i] << " ";
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
