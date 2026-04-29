#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<bool> visited, onstack;
stack<int> stk;
vector<int> ans;

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

bool dfs(int node, int parent) {
    visited[node] = true;
    stk.push(node);
    onstack[node] = true;

    for (int next : adj[node]) {
        if (next == parent) continue;

        if (!visited[next]) {
            if (dfs(next, node)) {
                return true;
            }
        } else {
            if (onstack[next]) {
                // extracts cycle
                ans.push_back(next);
                while (true) {
                    int top = stk.top();
                    ans.push_back(top);
                    stk.pop();
                    if (top == next) {
                        break;
                    }
                }
                return true;
            }
        }
    }

    stk.pop();
    onstack[node] = false;
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    adj = vector<vector<int>>(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    visited = vector<bool>(n, false);
    onstack = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, -1);
        }

        if (ans.size()) {
            break;
        }
    }

    if (ans.size()) {
        cout << ans.size() << endl;
        for (int node : ans) cout << node + 1 << ' ';
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
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
