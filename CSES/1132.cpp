#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<int> mem, ans;
vector<multiset<int>> child_mems;

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

void dfs(int node, int parent) {
    for (int next : adj[node]) {
        if (next == parent) continue;

        dfs(next, node);
        child_mems[node].insert(mem[next]);
    }

    int height = 1 + *child_mems[node].rbegin();
    mem[node] = height;
}

void dfs2(int node, int parent) {
    ans[node] = mem[node];
    for (int next : adj[node]) {
        if (next == parent) continue;

        child_mems[node].erase(child_mems[node].find(mem[next]));
        mem[node] = 1 + *child_mems[node].rbegin();
        child_mems[next].insert(mem[node]);
        mem[next] = 1 + *child_mems[next].rbegin();

        dfs2(next, node);

        child_mems[next].erase(child_mems[next].find(mem[node]));
        mem[next] = 1 + *child_mems[next].rbegin();
        child_mems[node].insert(mem[next]);
        mem[node] = 1 + *child_mems[node].rbegin();
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

    mem.resize(n);
    child_mems.resize(n);
    for (int i = 0; i < n; ++i) child_mems[i].insert(-1);  // -1 + 1 = 0 for leaves
    dfs(0, -1);

    ans.resize(n);
    dfs2(0, -1);
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << '\n';
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
