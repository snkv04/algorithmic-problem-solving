#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Info {
    priority_queue<int> ids;
};

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<Info>> segments;
vector<int> depth;
int n, logmaxn;
vector<vector<int>> graph, people, anc;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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

Info merge(const Info &left, const Info &right) {
    priority_queue<int> copy = left.ids, copy2 = right.ids;
    while (copy.size()) {
        copy2.push(copy.top());
        copy.pop();
    }
    while (copy2.size() > 10) {
        copy2.pop();
    }
    return Info{copy2};
}

void dfs(int node, int parent) {
    // base case is shortest possible segment
    if (parent != -1) depth[node] = depth[parent] + 1;
    anc[node][0] = parent;
    for (int person : people[node]) {
        segments[node][0].ids.push(person);
    }
    while (segments[node][0].ids.size() > 10) {
        segments[node][0].ids.pop();
    }

    // recursive cases are based on smaller segments
    for (int i = 1; i <= logmaxn; ++i) {
        int halfway = anc[node][i-1];
        if (halfway != -1) {
            anc[node][i] = anc[halfway][i-1];
            segments[node][i] = merge(segments[halfway][i-1], segments[node][i-1]);
        } else {
            break;
        }
    }

    // preorder DFS to child nodes
    for (int next : graph[node]) {
        if (next == parent) continue;

        dfs(next, node);
    }
}

pair<int, Info> jump(int node, int k) {
    if (k > depth[node]) return make_pair(-1, Info{});

    Info segment;
    for (int i = 0; i <= logmaxn; ++i) {
        if ((1<<i) & k) {
            segment = merge(segment, segments[node][i]);
            node = anc[node][i];
        }
    }
    return make_pair(node, segment);
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    int diff = depth[b] - depth[a];
    b = jump(b, diff).first;
    if (a == b) return a;

    for (int i = logmaxn; i >= 0; --i) {
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i];
            b = anc[b][i];
        }
    }
    return anc[a][0];
}

void solve() {
    int m, q;
    cin >> n >> m >> q;
    logmaxn = std::ceil(std::log2(n+2));
    graph.clear();
    graph.resize(n+1);
    graph[0].push_back(1); graph[1].push_back(0); // pretty much creates the sentinel node
    people.clear();
    people.resize(n+1);

    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= m; ++i) {
        int ci;
        cin >> ci;
        people[ci].push_back(i);
    }

    depth = vector<int>(n+1, 0);
    anc = vector<vector<int>>(n+1, vector<int>(logmaxn+1, -1));
    segments = vector<vector<Info>>(n+1, vector<Info>(logmaxn+1));
    depth[0] = 0; // node 0 is basically a sentinel node
    dfs(0, -1);

    while (q--) {
        int v, u, a;
        cin >> v >> u >> a;
        int lowest = lca(v, u);
        Info segment = segments[lowest][0];
        segment = merge(segment, jump(v, depth[v] - depth[lowest]).second);
        segment = merge(segment, jump(u, depth[u] - depth[lowest]).second);

        set<int> ids;
        while (segment.ids.size()) {
            ids.insert(segment.ids.top());
            segment.ids.pop();
        }

        int k = min((int) ids.size(), a);
        cout << k << " ";
        while (k--) {
            cout << *ids.begin() << " ";
            ids.erase(*ids.begin());
        }
        cout << "\n";
    }
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
