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
std::ostream& operator<<(std::ostream &os, const std::set<T> &c) {
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

int solve(int start, const vector<int> &color, const vector<vector<int>> &adj) {
    int n = color.size();
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j : adj[i]) {
            ++indegree[j];
        }
    }

    vector<set<int>> pending(3);
    for (int i = 0; i < color.size(); ++i) {
        if (!indegree[i]) {
            pending[color[i]].insert(i);
        }
    }

    int ans = 0;
    int curr = start;
    int total_visited = 0;
    vector<bool> visited(n, false);
    while (total_visited < n) {
        if (total_visited) ans += 1;  // don't want to increment it on every iter, only on iters where curr color changes
        while (pending[curr].size()) {
            int node = *pending[curr].begin();
            pending[curr].erase(node);
            visited[node] = true;
            ++total_visited;

            for (int next : adj[node]) {
                --indegree[next];
                if (!visited[next] && !indegree[next]) {
                    pending[color[next]].insert(next);
                }
            }
        }
        curr = (curr + 1) % 3;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> color(n);
    cin >> color;
    for (int i = 0; i < n; ++i) --color[i];
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        while (k--) {
            int node;
            cin >> node;
            --node;
            adj[node].push_back(i);
        }
    }

    int ans = 1e9;
    for (int i = 0; i < 3; ++i) {
        ans = min(ans, n + solve(i, color, adj));
    }
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
