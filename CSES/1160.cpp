#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int LOGMAXN;

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

void dfs(int node, int rep, vector<int> &comp, vector<bool> &visited, vector<set<int>> &adj) {
    comp[node] = rep;
    visited[node] = true;
    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next, rep, comp, visited, adj);
        }
    }
}

vector<int> get_comps(vector<int> &forward, vector<vector<int>> &backward) {
    int n = forward.size();
    vector<set<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        adj[i].insert(forward[i]);
        for (int j : backward[i]) adj[i].insert(j);
    }

    vector<int> comp(n);
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, i, comp, visited, adj);
        }
    }
    return comp;
}

void dfs2(
    int node,
    vector<int> &forward,
    vector<bool> &visited,
    stack<int> &stk,
    vector<bool> &on_stack,
    vector<vector<int>> &cycles
) {
    visited[node] = on_stack[node] = true;
    stk.push(node);

    int next = forward[node];
    if (!visited[next]) dfs2(next, forward, visited, stk, on_stack, cycles);

    if (on_stack[next]) {
        vector<int> cycle;
        while (stk.size()) {
            int top = stk.top();
            stk.pop();
            on_stack[top] = false;
            cycle.push_back(top);
            if (top == next) break;
        }
        reverse(cycle.begin(), cycle.end());
        cycles.push_back(cycle);
    } else {
        if (stk.size() && stk.top() == node) {
            stk.pop();
            on_stack[node] = false;
        }
    }
}

vector<vector<int>> build_cycles(vector<int> &forward) {
    int n = forward.size();
    vector<bool> visited(n, false);
    vector<vector<int>> cycles;
    stack<int> stk;
    vector<bool> on_stack(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs2(i, forward, visited, stk, on_stack, cycles);
        }
    }
    return cycles;
}

pair<vector<int>, vector<int>> get_cycle_info(vector<vector<int>> &cycles, int n) {
    vector<int> idx_in_cycle(n, -1), cycle_size(n, 0);
    for (auto cycle : cycles) {
        int idx = 0;
        for (int node : cycle) {
            idx_in_cycle[node] = idx++;
            cycle_size[node] = cycle.size();
        }
    }
    return make_pair(idx_in_cycle, cycle_size);
}

vector<int> get_depths(vector<vector<int>> &backward, vector<int> &cycle_size) {
    int n = backward.size();
    vector<int> depth(n, 0);
    for (int i = 0; i < n; ++i) {
        if (cycle_size[i]) {
            queue<int> q;
            q.push(i);
            while (q.size()) {
                int node = q.front();
                q.pop();
                for (int next : backward[node]) {
                    if (cycle_size[next]) continue;
                    
                    depth[next] = depth[node] + 1;
                    q.push(next);
                }
            }
        }
    }
    return depth;
}

vector<vector<int>> get_binary_jumping_array(vector<int> &forward) {
    int n = forward.size();
    vector<vector<int>> ancestor(n, vector<int>(LOGMAXN + 1, -1));
    for (int i = 0; i < n; ++i) ancestor[i][0] = forward[i];
    for (int b = 1; b <= LOGMAXN; ++b) {
        for (int i = 0; i < n; ++i) {
            int halfway = ancestor[i][b - 1];
            ancestor[i][b] = ancestor[halfway][b - 1];
        }
    }
    return ancestor;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> forward(n);
    vector<vector<int>> backward(n);
    cin >> forward;
    for (int i = 0; i < n; ++i) --forward[i];
    for (int i = 0; i < n; ++i) backward[forward[i]].push_back(i);

    vector<int> comp = get_comps(forward, backward);
    vector<vector<int>> cycles = build_cycles(forward);
    auto [cycle_idx, cycle_size] = get_cycle_info(cycles, n);  // cycle_size will also tell us if a node is in a cycle
    vector<int> depths = get_depths(backward, cycle_size);
    LOGMAXN = std::ceil(std::log2(n));
    vector<vector<int>> ancestor = get_binary_jumping_array(forward);

    while (q--) {
        int a, b;
        cin >> a >> b;
        --a; --b;

        if (comp[a] != comp[b]) {
            cout << "-1\n";
        } else {
            if (cycle_size[a] && cycle_size[b]) {
                int length = (cycle_idx[b] - cycle_idx[a] + cycle_size[a]) % cycle_size[a];
                cout << length << "\n";
            } else if (!cycle_size[a] && !cycle_size[b]) {
                if (depths[b] > depths[a]) {
                    cout << "-1\n";
                } else {
                    int length = depths[a] - depths[b];
                    for (int i = 0; i <= LOGMAXN; ++i) {
                        if ((length >> i) & 1) a = ancestor[a][i];
                    }
                    if (a != b) {
                        cout << "-1\n";
                    } else {
                        cout << length << "\n";
                    }
                }
            } else if (cycle_size[a]) {
                cout << "-1\n";
            } else {
                int length1 = depths[a];
                for (int i = 0; i <= LOGMAXN; ++i) {
                    if ((length1 >> i) & 1) a = ancestor[a][i];
                }
                int length2 = (cycle_idx[b] - cycle_idx[a] + cycle_size[a]) % cycle_size[a];
                cout << length1 + length2 << "\n";
            }
        }
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
