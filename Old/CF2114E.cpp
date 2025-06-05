#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<ll> mn, mx, a;
const int maxn = 200005;
vector<int> adj[maxn];

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void dfs(int node, int parent) {
    mx[node] = max(a[node], a[node] - mn[parent]);
    mn[node] = a[node] - mx[parent];

    for (int next : adj[node]) {
        if (next != parent) {
            dfs(next, node);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    mn.resize(n+1);
    mx.resize(n+1);
    a.resize(n+1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        adj[i].clear();
    }
    for (int i = 1; i <= n-1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << mx[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
