#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Info {
    int sum, prefmax, prefmin, sufmax, sufmin, subarraymax, subarraymin;
};

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<Info>> segments;
vector<int> weight, depth;
int n, logmaxn, timer;
vector<vector<int>> children, anc;

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
    return Info{
        left.sum + right.sum,
        max(left.prefmax, left.sum + right.prefmax),
        min(left.prefmin, left.sum + right.prefmin),
        max(right.sufmax, right.sum + left.sufmax),
        min(right.sufmin, right.sum + left.sufmin),
        max({left.subarraymax, right.subarraymax, left.sufmax + right.prefmax}),
        min({left.subarraymin, right.subarraymin, left.sufmin + right.prefmin})
    };
}

void dfs(int node, int parent) {
    // base case is shortest possible segment
    anc[node][0] = parent;
    segments[node][0].sum = weight[node];
    segments[node][0].prefmax = segments[node][0].sufmax = segments[node][0].subarraymax = max(0, weight[node]);
    segments[node][0].prefmin = segments[node][0].sufmin = segments[node][0].subarraymin = min(0, weight[node]);

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
    for (int next : children[node]) {
        depth[next] = depth[node] + 1;
        dfs(next, node);
    }
}

int jump(int node, int k) {
    if (k > depth[node]) return -1;

    for (int i = 0; i <= logmaxn; ++i) {
        if ((1<<i) & k) {
            node = anc[node][i];
        }
    }
    return node;
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    int diff = depth[b] - depth[a];
    b = jump(b, diff);
    if (a == b) return a;

    for (int i = logmaxn; i >= 0; --i) {
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i];
            b = anc[b][i];
        }
    }
    return anc[a][0];
}

int bestprefixsum(int a, int c, bool mx) {
    int diff = depth[a] - depth[c];
    Info segment{};
    for (int i = 0; i <= logmaxn; ++i) {
        if ((1 << i) & diff) {
            segment = merge(segments[a][i], segment);
            a = anc[a][i];
        }
    }
    return mx ? segment.prefmax : segment.prefmin;
}

int kadanes(int a, int c, bool mx) {
    int diff = depth[a] - depth[c];
    Info segment{};
    for (int i = 0; i <= logmaxn; ++i) {
        if ((1 << i) & diff) {
            segment = merge(segments[a][i], segment);
            a = anc[a][i];
        }
    }
    return mx ? segment.subarraymax : segment.subarraymin;
}

void solve() {
    /*
    generalizable ideas for the future:
    - previously, i stored information for all possible power-2-length segments for every node in separate
    arrays. however, we can store the information for every such segment in a single struct. why is this
    beneficial? by making a merge function, that merges two adjacent segments, it can be cleanly used for:
    (1) merging two adjacent segments of equal length in order to construct the information for a segment
    with its length being the next power of 2 (so it is even used in the precomputation), and (2) merging
    two adjacent segments of non-equal length, which lets you get information about arbitrary-length segments
    (so it is used at query-time).
        - intuitively, we can easily get all possible information that we need for any arbitrary segment in
        a neatly-organized struct this way. it's just like a segment tree, but over vertical paths in a tree
        instead of over segments in an array.
    - for multidimensional vectors, store the longest dimension last, as that ends up needing fewer heap
    allocations. even if using arrays that are allocated on the stack, C++ always places elements that are
    adjacent in row-major order into contiguous slots in memory, so in many use cases (probably not for
    graphs/trees though), there will probably be better cache locality.
    */

    cin >> n;
    logmaxn = std::ceil(std::log2(n+2));
    timer = 2;
    children.clear();
    children.resize(n+2);
    children[0].push_back(1); // pretty much creates the sentinel node
    weight = vector<int>(n+2, 0);
    weight[1] = 1;
    vector<array<int, 3>> queries;
    for (int i = 0; i < n; ++i) {
        char op;
        cin >> op;
        if (op == '+') {
            int v, x;
            cin >> v >> x;
            // --v;
            int node = timer++;
            children[v].push_back(node);
            weight[node] = x;
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            // --u; --v;
            queries.push_back({u, v, k});
        }
    }

    depth = vector<int>(n+2, 0);
    anc = vector<vector<int>>(n+2, vector<int>(logmaxn+1, -1));
    segments = vector<vector<Info>>(n+2, vector<Info>(logmaxn+1));
    depth[0] = 0; // node 0 is basically a sentinel node
    dfs(0, -1);

    for (auto &q : queries) {
        int a = q[0], b = q[1], k = q[2];
        if (k == 0) {
            cout << "YES\n";
            continue;
        }
        
        int c = lca(a, b);
        if (c == 0) {
            throw std::runtime_error("huh?");
        }
        int mx = max({kadanes(b, c, true), kadanes(a, c, true), bestprefixsum(a, c, true) + bestprefixsum(b, c, true) + weight[c]});
        int mn = min({kadanes(b, c, false), kadanes(a, c, false), bestprefixsum(a, c, false) + bestprefixsum(b, c, false) + weight[c]});
        cout << (k >= mn && k <= mx ? "YES" : "NO") << "\n";
    }
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
