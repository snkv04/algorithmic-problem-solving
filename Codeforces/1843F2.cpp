#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> sum, prefmax, sufmax, prefmin, sufmin, subarraymax, subarraymin;
int timer;
vector<int> weight;
vector<int> depth;
vector<vector<int>> anc;
int n, logmaxn;
vector<vector<int>> children;

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

void dfs(int node, int parent) {
    anc[node][0] = parent;
    if (parent != -1) {
        sum[node][0] = weight[node];
    }
    for (int i = 1; i <= logmaxn; ++i) {
        int halfway = anc[node][i-1];
        if (halfway != -1) {
            anc[node][i] = anc[halfway][i-1];
            sum[node][i] = sum[node][i-1] + sum[halfway][i-1];
        } else {
            break;
        }
    }

    prefmin[node][0] = sufmin[node][0] = subarraymin[node][0] = min(0, weight[node]);
    prefmax[node][0] = sufmax[node][0] = subarraymax[node][0] = max(0, weight[node]);
    for (int i = 1; i <= logmaxn; ++i) {
        int halfway = anc[node][i-1];
        if (halfway != -1) {
            prefmin[node][i] = min(prefmin[halfway][i-1], sum[halfway][i-1] + prefmin[node][i-1]);
            prefmax[node][i] = max(prefmax[halfway][i-1], sum[halfway][i-1] + prefmax[node][i-1]);
            sufmin[node][i] = min(sufmin[node][i-1], sum[node][i-1] + sufmin[halfway][i-1]);
            sufmax[node][i] = max(sufmax[node][i-1], sum[node][i-1] + sufmax[halfway][i-1]);
            subarraymin[node][i] = min({subarraymin[node][i-1], subarraymin[halfway][i-1], prefmin[node][i-1] + sufmin[halfway][i-1]});
            subarraymax[node][i] = max({subarraymax[node][i-1], subarraymax[halfway][i-1], prefmax[node][i-1] + sufmax[halfway][i-1]});
        } else {
            break;
        }
    }

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
    int curr = 0;
    for (int i = 0; i <= logmaxn; ++i) {
        if ((1 << i) & diff) {
            if (mx) {
                curr = max(prefmax[a][i], sum[a][i] + curr);
            } else {
                curr = min(prefmin[a][i], sum[a][i] + curr);
            }
            a = anc[a][i];
        }
    }
    return curr;
}

int kadanes(int a, int c, bool mx) {
    int diff = depth[a] - depth[c];
    int currpref = 0, best = 0;
    for (int i = 0; i <= logmaxn; ++i) {
        if ((1 << i) & diff) {
            if (mx) {
                best = max({best, subarraymax[a][i], currpref + sufmax[a][i]});
                currpref = max(prefmax[a][i], sum[a][i] + currpref);
            } else {
                best = min({best, subarraymin[a][i], currpref + sufmin[a][i]});
                currpref = min(prefmin[a][i], sum[a][i] + currpref);
            }
            a = anc[a][i];
        }
    }
    return best;
}

void solve() {
    /*
    solution:
    - for any two nodes a and b, we want to be able to quickly check if we can make a subarray of sum k of the path
    between a and b.
    - since all of the weights on the tree are unit weights (+1 and -1), if we know the min path sum and max path sum
    between a and b, then we know that we can get every value in between. why? if we start with the path having the
    min sum, then to move it to the path with max sum, every operation we make (shifting around an endpoint of the
    subarray) either adds or subtracts 1, making it so that we cover every value in between.
    - therefore, we want to find the max and min subarray sum across every path. how to do that? binary lifting.
    the min and max cases are symmetric, so let's look at the max case.
    - to get the max sumarray sum for a path from a to b on a tree, let's first assign c = lca(a, b). the value is
    either going to be the max subarray sum on the path from a to c, the max subarray sum on the path from b to c,
    or the max subarray sum crossing c.
    - for the first and second cases, we can examine all paths of lengths 1, 2, 4, 8, etc. extending above each node
    in the tree. for these paths, we can get the max prefix sum and max suffix sum, which is easy if we also compute
    the total sum for each of these paths. then, for the max subarray sum, for a given size, either the max-sum
    subarray is entirely on the left (so we get it from the smaller subproblem), entirely on the right (so we get it
    from the smaller subproblem), or crosses through the middle (so we get the max suffix from the left and the max
    prefix from the right). now, we have gotten the max subarray sum for all vertical paths of power-2 lengths. to get
    it for an arbitrary length, we basically perform the same logic by merging information from adjacent segments of
    different lengths but both having power-2 lengths (think of the case 21, which can be decomposed into 1+4+16).
    this merging logic is a generalization of kadane's algorithm, which merges two segments of length n-1 and 1 instead
    of two power-2-length segments.
    - for the third case, we get the max prefix from c to a, the max prefix from c to b, and the value of c itself.
    we just sum those up. this is more straightforward.

    generalizable ideas for the future:
    - i was thinking that to get the maximum subarray sum for an arbitrary length, we could just use the max prefix sum
    and max suffix sum for lengths that are powers of 2. it turns out that we also need the maximum subarray sub for lengths
    that are powers of 2 to get the same quantity for arbitrary lengths. more generally, if we have a property that we want
    to find out for arbitrary lengths where the basic idea involves using segments of lengths that are powers of 2, try
    seeing how to calculate that property for lengths that are powers of 2, as it might be the case that calculating that
    property for arbitrary lengths requires calculating that property for power-2 lengths and can't just be done by directly
    using other properties for power-2 lengths.
    - in this problem, we are given weights on nodes. this is slightly annoying, because typically in LCA-type problems (namely,
    those that involve computing information about edges between a node i and its 2^j'th parent), we are concerned with weights
    on edges, not nodes. this can actually be easily fixed by adding a dummy node above the root, and shifting all node weights
    to be edge weights on the edges connecting each node to its parent (where the new root is the exception, since it doesn't
    have a parent). more generally, try to see if the current representation in the problem can be slightly shifted into a more
    familiar representation that is easier to work with.
        - now, we only have to deal with special edge cases only when combining 2 vertical paths, but that is easily dealt with.
        if a and b have lca c, then the node c is used on the path from a to b, but the edge corresponding to c is not present
        on the path (as it's right above the meeting point, c). we can just manually take this into consideration when joining
        two paths together. IN OTHER WORDS: when computing information about the path from node i to i's 2^j'th parent, we treat
        the edges as normal. when using this information to join paths together that go down from a node, we have to consider that
        the weight corresponding to node c is on the edge right above c.
        - by making this shift, among all the nodes that we care about (1 to n+1, inclusive), none of their LCAs will ever be
        the sentinel node, node 0. this is good.
        - a benefit of this is that for a given vertical line in a tree, we can split it into two pieces such that the weights
        are partitioned into the two segments and no weight is shared in both. that is just the nature of looking at edges and
        not nodes, when paths have a start and end node.
    - in kadane's algorithm, we want the maximum subarray sum across all subarrays of an array. if we simply want the
    maximum prefix sum for a fixed start node, then we need to ensure that we do not take the best prefix across all
    nodes on a path, but only take the best prefix (the length can vary, but the start node can't) starting at that
    fixed node.
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
    anc[1][0] = 0;
    sum = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
    prefmin = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
    sufmin = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
    subarraymin = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
    prefmax = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
    sufmax = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
    subarraymax = vector<vector<int>>(n+2, vector<int>(logmaxn+1, 0));
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
