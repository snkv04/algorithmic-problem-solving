#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<ll> mem, mem2;
vector<vector<int>> adj;
vector<int> depth;
int maxdepth;
vector<vector<int>> bydepth;

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

void dfs(int node) {
    if (depth[node] == bydepth.size()) bydepth.push_back(vector<int>());
    bydepth[depth[node]].push_back(node);
    maxdepth = max(maxdepth, depth[node]);

    for (int next : adj[node]) {
        depth[next] = depth[node] + 1;
        dfs(next);
    }
}

void solve() {
    int n;
    cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 1; i < n; ++i) {
        int pi;
        cin >> pi;
        --pi;
        adj[pi].push_back(i);
    }

    depth = vector<int>(n, 0);
    maxdepth = 0;
    bydepth = vector<vector<int>>();
    dfs(0);

    mem = vector<ll>(n, 0);
    mem2 = vector<ll>(maxdepth + 1, 0);
    for (int d = maxdepth; d >= 0; --d) {
        for (int node : bydepth[d]) {
            ll fromchild = 0;
            for (int next : adj[node]) {
                fromchild += mem[next];
                fromchild %= MOD;
            }

            if (d == maxdepth) {
                mem[node] = 1;
            } else if (d == 0) {
                mem[node] = 1 + fromchild;
            } else {
                mem[node] = 1 + (mem2[d + 1] - fromchild) + MOD;
            }
            mem2[d] += mem[node];

            mem[node] %= MOD;
            mem2[d] %= MOD;
        }
    }
    cout << mem[0] << endl;
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
