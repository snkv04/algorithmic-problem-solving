#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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

vector<int> get_max_except(vector<vector<int>> &adj, int n) {
    vector<int> result(n + 1, 0);

    // just use lambda functions to make code cleaner, since they can capture local variables
    // however, for recursive functions, have to pass itself in as an argument to itself, and use that argument inside the function
    // (also, using a set here is actually unnecessary, but it demonstrates the need for a return type when writing recursive lambdas)
    auto dfs = [&](int node, int parent, auto self) -> set<int> {
        set<int> nodes = {0};
        for (int next : adj[node]) {
            if (next == parent) continue;

            set<int> other_nodes = self(next, node, self);  // we use the argument inside the function definition
            if (other_nodes.size() > nodes.size()) swap(nodes, other_nodes);
            for (int i : other_nodes) nodes.insert(i);
        }

        result[node] = *nodes.rbegin();
        nodes.insert(node);
        return nodes;
    };
    dfs(n, -1, dfs);  // when you call dfs, you pass in dfs as an arg
    return result;
}

vector<bool> get_can_move(vector<vector<int>> &adj, int n) {
    vector<int> root_child(n + 1);
    auto dfs = [&](int node, int parent, int child, auto self) -> void {
        root_child[node] = child;
        for (int next : adj[node]) {
            if (next == parent) continue;

            self(next, node, child, self);
        }
    };
    for (int c : adj[n]) dfs(c, n, c, dfs);

    set<int> maxes;
    vector<int> mx(n + 1);
    auto dfs2 = [&](int node, int parent, auto self) -> void {
        mx[node] = node;
        for (int next : adj[node]) {
            if (next == parent) continue;

            self(next, node, self);
            mx[node] = max(mx[node], mx[next]);
        }
        if (parent == n) maxes.insert(mx[node]);
    };
    dfs2(n, -1, dfs2);

    vector<bool> result(n + 1, false);
    for (int i = 1; i < n; ++i) {
        int c = root_child[i];
        maxes.erase(mx[c]);
        if (*maxes.rbegin() < i) {
            result[i] = true;
        }
        maxes.insert(mx[c]);
    }
    return result;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int leaves = 0, x_start = -1;
    for (int i = 1; i <= n; ++i) {
        leaves += adj[i].size() == 1;
        if (adj[i].size() == 1) {
            x_start = max(x_start, i);
        }
    }
    if (leaves == 2 || adj[n].size() == 1) {
        cout << "1\n";
        return;
    }

    vector<int> max_except = get_max_except(adj, n);
    // cout << "max_except = " << max_except << endl;
    vector<bool> can_move = get_can_move(adj, n);
    // cout << "can_move = " << can_move << endl;
    vector<ll> mem(n + 1, 0), mem_pref(n + 1, 0);
    mem[x_start] = mem_pref[x_start] = 1;
    for (int i = x_start + 1; i < n; ++i) {
        if (max_except[i] < i - 1) {
            mem[i] = (mem_pref[i - 1] - mem_pref[max_except[i]] + MOD) % MOD;
        }
        mem_pref[i] = (mem_pref[i - 1] + mem[i]) % MOD;
    }
    for (int i = 1; i < n; ++i) {
        if (can_move[i]) {
            mem[n] += mem[i];
            mem[n] %= MOD;
        }
    }
    cout << mem[n] << endl;
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
