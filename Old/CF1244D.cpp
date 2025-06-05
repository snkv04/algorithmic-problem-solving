#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXN = 100005;
vector<int> adj[MAXN];

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void dfs(int node, vector<int> &order, vector<bool> &visited) {
    visited[node] = true;
    order.push_back(node);
    for (int next : adj[node]) {
        if (!visited[next]) dfs(next, order, visited);
    }
}

void solve() {
    int n;
    cin >> n;
    int c[3][n];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c[i][j];
        }
    }

    set<int> ends; for (int i = 0; i < n; ++i) ends.insert(i);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        if (adj[a].size() == 3 || adj[b].size() == 3) {
            cout << "-1\n";
            return;
        }
        if (adj[a].size() == 2) {
            ends.erase(a);
        }
        if (adj[b].size() == 2) {
            ends.erase(b);
        }
    }

    // print_container(ends, "ends = ");
    int start = *ends.begin();
    vector<int> order;
    vector<bool> visited(n, false);
    dfs(start, order, visited);
    assert(adj[order[0]].size() == 1);
    assert(adj[order[n-1]].size() == 1);
    // print_container(order, "order = ");

    ll costs[6];
    fill(costs, costs+6, 0);
    for (int i = 0; i < n; ++i) {
        int node = order[i];
        for (int j = 0; j < 6; ++j) {
            int color; // selects the color based on i (and j) for the pattern to work
            if (j < 3) {
                color = (i + j) % 3;
            } else {
                color = (n + 4 - i - j) % 3;
            }
            costs[j] += c[color][node]; // gets the cost based on the node (from the order) having that color
            // cout << color << "\t";
        }
        // cout << "\n";
    }

    ll ans = 1e18, best = -1;
    for (int i = 0; i < 6; ++i) {
        if (costs[i] < ans) {
            ans = costs[i];
            best = i;
        }
    }
    cout << ans << "\n";
    int idxtocolor[n];
    for (int i = 0; i < n; ++i) {
        int node = order[i];
        int color; // selects the color based on i
        if (best < 3) {
            color = ((i + best) % 3) + 1;
        } else {
            color = ((n + 4 - i - best) % 3) + 1;
        }
        idxtocolor[node] = color; // sets the color for the node from the order
    }
    for (int i = 0; i < n; ++i) {
        cout << idxtocolor[i] << " ";
    }
    cout << endl;
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
