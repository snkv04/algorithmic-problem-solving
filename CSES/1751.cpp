#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<int> t;
stack<int> stk;
vector<bool> onstack, visited;
vector<vector<int>> cycles;

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
    visited[node] = onstack[node] = true;
    stk.push(node);

    int next = t[node];
    if (!visited[next]) {
        dfs(next);
    }

    if (onstack[next]) {
        vector<int> cycle;
        while (true) {
            int top = stk.top();
            stk.pop();
            onstack[top] = false;
            cycle.push_back(top);
            if (top == next) break;
        }
        cycles.push_back(cycle);
    } else if (stk.size() && stk.top() == node) {
        stk.pop();
        onstack[node] = false;
    }
}

void solve() {
    // gets graph and transpose graph
    int n;
    cin >> n;
    t = vector<int>(n);
    cin >> t;
    for (int i = 0; i < n; ++i) --t[i];
    vector<vector<int>> r(n);
    for (int i = 0; i < n; ++i) r[t[i]].push_back(i);

    // finds cycles
    onstack = vector<bool>(n, false);
    visited = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // maps each node to its representative node and gets cycle sizes
    vector<int> rep(n, -1);
    map<int, int> cycle_size;
    for (auto cycle : cycles) {
        for (int node : cycle) {
            rep[node] = cycle[0];
        }
        cycle_size[cycle[0]] = cycle.size();
    }

    // does BFS to get distances from cycle as well as representative node of cycle it's connected to
    vector<int> dist(n, 0);
    vector<int> rep2(n, -1);
    for (int i = 0; i < n; ++i) {
        if (rep[i] != -1) {
            queue<int> q;
            q.push(i);
            while (q.size()) {
                int node = q.front();
                q.pop();
                
                for (int next : r[node]) {
                    if (rep[next] == -1) {
                        // sets rep of tree node to same rep as cycle
                        // rep2 is for tree nodes, rep is for cycle nodes
                        rep2[next] = rep[i];
                        dist[next] = dist[node] + 1;
                        q.push(next);
                    }
                }
            }
        }
    }

    // gets answer for each node
    for (int i = 0; i < n; ++i) {
        if (rep[i] != -1) {
            cout << cycle_size[rep[i]] << " ";
        } else {
            cout << cycle_size[rep2[i]] + dist[i] << " ";
        }
    }
    cout << "\n";
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
