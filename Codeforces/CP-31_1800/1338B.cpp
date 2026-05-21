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

bool check_all_even_dists_from_leaf(vector<vector<int>> &adj) {
    // roots the tree at a leaf
    int n = adj.size();
    int leaf = -1;
    for (int i = 0; i < n; ++i) if (adj[i].size() == 1) { leaf = i; break; }

    // finds all distances to that leaf
    vector<int> dist(n, -1);
    dist[leaf] = 0;
    queue<int> q;
    q.push(leaf);
    while (q.size()) {
        int node = q.front();
        q.pop();

        for (int next : adj[node]) {
            if (dist[next] == -1) {
                dist[next] = dist[node] + 1;
                q.push(next);
            }
        }
    }

    // makes sure all leaves have even distance to that leaf
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() == 1 && dist[i] % 2) return false;
    }
    return true;
}

int find_non_leaf(vector<vector<int>> &adj) {
    for (int i = 0; i < adj.size(); ++i)
        if (adj[i].size() > 1)
            return i;
    throw std::logic_error("Tree with >= 3 nodes must have a non-leaf node");
}

bool check_all_leaf_dists_parity(vector<vector<int>> &adj) {
    // finds a non-leaf node, then gets all distances from that non-leaf node
    int root = find_non_leaf(adj);
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    dist[root] = 0;
    q.push(root);
    while (q.size()) {
        int node = q.front();
        q.pop();

        for (int next : adj[node]) {
            if (dist[next] == -1) {
                dist[next] = dist[node] + 1;
                q.push(next);
            }
        }
    }

    // makes sure all leaves have the same parity of distance from the root
    int parity = -1;
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() == 1) {
            if (parity == -1) parity = dist[i] % 2;
            else if (dist[i] % 2 != parity) return false;
        }
    }
    return true;
}

int dfs(int node, int parent, vector<vector<int>> &adj) {
    // counts number of distinct edge weights we can have in the subtree of `node`
    int num_diff_edges = 0;
    bool seen_leaf = false;
    for (int next : adj[node]) {
        // skip edges going upward
        if (next == parent) continue;

        // add number of distinct edge weights from the child node's subtree
        num_diff_edges += dfs(next, node, adj);

        // add 1 to our result if the child isn't a leaf or it's the first leaf we've seen
        // (so that we don't count multiple leaves adjacent to this node)
        // if (adj[next].size() == 1) {
        //     if (!seen_leaf) {
        //         num_diff_edges += 1;
        //         seen_leaf = true;
        //     }
        // } else {
        //     num_diff_edges += 1;
        // }
        if (adj[next].size() > 1) {
            num_diff_edges += 1;
        } else if (!seen_leaf) {
            num_diff_edges += 1;
            seen_leaf = true;
        }
    }
    return num_diff_edges;
}

void solve() {
    /*
    - problem:
        - we are given a tree, and we can assign edge weights to it (with arbitrary magnitude)
        - suppose we need to make the XOR of every path between 2 leaves 0. what is the minimum number
        of distinct edge weights we can have, and what's the maximum number of distinct edge weights
        we can have?
    - solution:
        - for minimum:
            - if all pairs of leaves have an even distance between them, then we can obviously just
            use the same edge weight for every edge, so the answer is 1
            - otherwise, we have at least one pair of leaves whose distance is odd.
            then the answer is 3. why? we can show this by construction.
            first off, in a simple path with length 3 and no other nodes, we can't do better than 3.
            now, if we have a more complex tree with an odd-length path and possibly even length paths,
            then let node i be a non-leaf node. the XOR sum from node i to EVERY leaf must have the same
            value; suppose it is equal to "target" \in {1, 2, 3}. let's focus on node i = root node.
            if we set target = 1, then for leaves an even distance away, we can set the edges to 1-1-1-1-...-1-1-2-3.
            for leaves an odd distance away, we can set the edges to 1-1-...-1. we may encounter branching points
            between the root and a leaf; in that case, the XOR sum from branch to any leaf OUTSIDE the subtree
            must be the same as the XOR sum from branch to any leaf INSIDE the subtree, so we just update target
            (which will stay in the same closed set {1, 2, 3}) and then run the same algorithm for leaves inside
            the subtree, using edge weights in that same set {1, 2, 3}.
        - for maximum:
            - root the tree at a non-leaf.
                - why? it just makes sure that we process all leaves as child nodes; the only node that
                is never processed as a "next"/child node is the root.
            - then, for any node i, all leaves L in its subtree must have the same xor_sum(i, L). fix this
            to "target". then, for leaves that are adjacent to i, they must all have those edge weights equal
            to target. but, for non-leaves (corresponding to subtrees) that are children of i, we can make that
            edge equal to target plus some random bit, and the new target for that subtree is that random bit.
            - therefore, we can basically make almost all edges have different weights, but when we have multiple
            leaves that are all adjacent to a non-leaf node, then they are forced to have the same weight. so, for
            a given node, we count all edges connecting it to a leaf as a single edge for the purpose of incrementing
            the number of distinct edge weights we can have.
    - core idea:
        - suppose two paths (a - b - c) and (a - b - d) share a common segment (a - b). then the non-shared
        parts, which are (b - c) and (b - d), will share some information.
            - if we know xor_sum(a, b), then xor_sum(b, c) == xor_sum(b, d) == xor_sum(a, b).
            - if we know that path_length_parity(a, L) is even for all leaves L, then we know that it's even for
            all pairs (L_1, L_2), because if we let b = LCA(L_1, L_2), then
            path_length_parity(a, b) == path_length_parity(b, L_1) == path_length_parity(b, L_2),
            so then path_length_parity(L_1, L_2) = 0, as required.
        - we have that 1 XOR 2 == 3. it's an XOR triple, so to speak. this can be useful, as in this problem.
    - details:
        - when the problem has to do with bitwise operations, it can help to simply think of numbers as
        arrangements of 0s and 1s
        - alternatively, instead of rooting the tree at a leaf and making sure all distances from that leaf
        to other leaves are even, we can root the tree at a non-leaf, and make sure all distances from that
        node to leaves have the same parity
    */

    // reads in the tree
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // gets minimum value
    // bool even_dists_between_leaves = check_all_even_dists_from_leaf(adj);
    bool even_dists_between_leaves = check_all_leaf_dists_parity(adj);
    int mn = even_dists_between_leaves ? 1 : 3;

    // gets maximum value
    int root = find_non_leaf(adj);
    int mx = dfs(root, -1, adj);

    // outputs both answers
    cout << mn << ' ' << mx << '\n';
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
