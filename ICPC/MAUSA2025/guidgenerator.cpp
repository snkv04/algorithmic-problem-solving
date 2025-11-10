#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> graph;
vector<ll> P = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009};
set<pair<ll, ll>> hashes;
string s;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

void dfs(int node, int parent, pair<ll, ll> prevhash) {
    pair<ll, ll> hash = prevhash;
    hash.first = (P[0] * hash.first + s[node]) % MOD[0];
    hash.second = (P[1] * hash.second + s[node]) % MOD[1];
    hashes.insert(hash);

    for (int next : graph[node]) {
        if (next == parent) continue;

        dfs(next, node, hash);
    }
}

void solve() {
    int n;
    cin >> n;
    cin >> s;
    graph.resize(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    hashes = set<pair<ll, ll>>();
    for (int i = 0; i < n; ++i) {
        dfs(i, -1, make_pair(0, 0));
    }
    cout << hashes.size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
