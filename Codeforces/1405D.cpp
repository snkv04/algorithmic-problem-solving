#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
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

vector<int> get_dists(int start) {
    int n = adj.size();
    vector<int> dists(n, -1);
    dists[start] = 0;
    queue<int> q;
    q.push(start);
    while (q.size()) {
        int node = q.front();
        q.pop();

        for (int next : adj[node]) {
            if (dists[next] == -1) {
                dists[next] = dists[node] + 1;
                q.push(next);
            }
        }
    }
    return dists;
}

pair<int, int> get_farthest(vector<int> &dists) {
    pair<int, int> result = {-1, 0};
    for (int i = 0; i < dists.size(); ++i) {
        if (dists[i] > result.second) {
            result.first = i;
            result.second = dists[i];
        }
    }
    return result;
}

void solve() {
    int n, a, b, da, db;
    cin >> n >> a >> b >> da >> db;
    --a; --b;
    adj.resize(n); for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> distsa = get_dists(a);
    int initdist = distsa[b];
    auto [farnode, fardist] = get_farthest(distsa);
    vector<int> dists_from_end = get_dists(farnode);
    auto [_, diameter] = get_farthest(dists_from_end);
    cout << ((db > 2 * da && diameter > 2 * da && initdist > da) ? "Bob" : "Alice") << endl;
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
