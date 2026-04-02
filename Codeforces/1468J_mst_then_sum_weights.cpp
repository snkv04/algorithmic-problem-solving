#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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

struct DSU {
    DSU(int n) : n(n), comp_size(n, 1) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int node1, int node2) {
        int root1 = find(node1), root2 = find(node2);
        if (root1 != root2) {
            if (comp_size[root1] >= comp_size[root2]) {
                parent[root2] = root1;
                comp_size[root1] += comp_size[root2];
            } else {
                parent[root1] = root2;
                comp_size[root2] += comp_size[root1];
            }
        }
    }

    int size(int node) {
        return comp_size[find(node)];
    }

private:
    int n;
    std::vector<int> parent, comp_size;
};

struct Edge {
    int u, v, w;
};

void solve() {
    /*
    - problem:
        - we have a weighted, undirected graph
        - we want to remove edges so that a spanning tree remains, and we want the maximum edge weight
        of the spanning tree to be exactly k
        - suppose we can perform some operations, where each operation increases or decreases an edge
        weight by 1.
        - across all choices of {what operations we perform} and {what edges we remove}, what is the
        minimum number of operations we need to perform?
    - solution:
        - first, notice that there's no need to perform operations on edges that we're going to remove
        - second, suppose that our final spanning tree is fixed. if there exist edges with weight >= k,
        then we'll have to drop all of those down to k, but if there don't, then we only have to bring
        one edge up to k. so, intuitively, we'd want most (though not necessarily all) of the edges to
        have low weight
        - so, we can take the minimum spanning tree, and deal with 2 cases:
            - if there are edges in the MST with weight >= k, then the MST is already optimal; taking
            larger edges will only mean more weights to drop. so, we just calculate the answer
            - if there aren't, then that means that we are able to connect the whole graph with edges
            having weight <= k. then, we can take a single edge with weight as close to k as possible,
            add it to the MST, and remove an edge from the MST to get our final optimal spanning tree
    - details:
        - instead of getting the MST from the original edges then summing up the weights of the MST's
        edges based on a particular rule, we can reassign the edges' weights by that rule and then take
        the MST using those new edges. why? the ordering of edges by weight does not change, so the MST
        itself does not change, but this version is more logically aligned with the standard idea of
        finding an MST and summing up its edge weights. so, in a way, it's more modular: reassign all
        edge weights, then run classical MST algorithm + take sum of weights. this version is implemented
        in the other solution.
    - generalized ideas for the future:
        - we can observe that in the first case, it's easy but important to mentally prove that the MST
        is optimal. to do this, assume that there's a better tree, and show that it can't be true. proof
        by contradiction is super useful for intuition!
        - in the second case, the logic of "just take one edge close in weight to k, and that's enough"
        jumps right out of the fact that (1) the graph is fully connectable using edges whose weight we
        don't need to operate on (because they're <= k), so we can just leave most of the tree as-is and
        not even change it if we don't have to, and (2) the MST is a TREE, meaning that we can add one
        edge to create a cycle and remove another edge to keep it a tree. more generally, if we are examining
        a particular case or situation, it is much easier to explore the properties of that case if we
        clearly lay out the facts.
    */

    // reads in the edges
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        --edges[i].u; --edges[i].v;
    }

    // builds the MST
    DSU dsu(n);
    sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) { return e1.w < e2.w; });
    vector<Edge> mst;
    for (auto e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.join(e.u, e.v);
            mst.push_back(e);
        }
    }

    // if the max weight of the MST is >= k, then we can't do better, so just sum up the discrepancies.
    // otherwise, pick an edge as close to the k threshold as possible, and replace some edge in the MST with it.
    if (mst.back().w >= k) {
        ll ans = 0;
        for (auto e : mst) ans += max(0, e.w - k);
        cout << ans << endl;
    } else {
        int closest = -1e9;
        for (auto e : edges) if (abs(e.w - k) < abs(closest - k)) closest = e.w;
        cout << abs(closest - k) << endl;
    }
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
