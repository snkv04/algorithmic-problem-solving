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

int jump(int node, int k, const vector<int> &p) {
    for (int i = 0; i < k; ++i) node = p[node];
    return node;
}

void remove_subtree(int node, const vector<vector<int>> &children, const vector<int> &depth, vector<bool> &removed) {
    queue<int> q;
    q.push(node);
    while (q.size()) {
        int node = q.front();
        q.pop();
        removed[node] = true;

        for (int next : children[node]) {
            if (!removed[next]) {
                q.push(next);
            }
        }
    }
}

int num_ops(
    const vector<int> &p,
    const vector<vector<int>> &children,
    const vector<int> &depth,
    const vector<int> &sorted_by_depth,
    int max_depth
) {
    int n = p.size(), ops = 0, idx = 0;
    vector<bool> removed(n, false);
    while (depth[sorted_by_depth[idx]] > max_depth) {
        int node = sorted_by_depth[idx++];
        int u = jump(node, max_depth - 1, p);
        remove_subtree(u, children, depth, removed);
        while (removed[sorted_by_depth[idx]]) {  // idx will always be valid, since node 0 (last in order) will never be removed
            ++idx;
        }

        ++ops;
    }
    return ops;
}

void solve() {
    /*
    - generalized ideas for the future:
        - when doing problems with trees, think both about properties of (e.g., distance from) the root
        (or the root of a given subtree) and properties of leaves.
        in this problem, the greedy algorithm for getting the height of the subtree to be K is hard to
        think of when going down from the root, because cutting off the edges below the nodes of distance K
        from the root might actually be worse than cutting off edges below the nodes of distance K-1 from the
        root. namely, farthest isn't always best.
        however, it is much easier to think of when going up from leaves: we need each leaf to be placed in a
        subtree of height K, and the edge farthest up for that leaf is best. that's it.
        basically, our goal is to cut the fewest number of edges. if we start at the root, there are lots of
        different edges to consider (up to a distance of K downward) to ensure that no leaf is too far. if we
        start at a leaf, then there's only one edge that is clearly best: the farthest one up, because any edge
        closer to the leaf than that is strictly worse.
        so, in the future, think both from the perspective of top-down and bottom-up, because one might be
        much easier for the problem at hand.
        - in general, if you have to compute something, think about if it can be precomputed. in this problem,
        we don't have to precompute each node's distance-K-upward-ancestor, but it's feasible that a precomputation
        like that could help, based on the problem.
        - if you're performing operations on subtrees, think about if the subtrees overlap, and if they do,
        then think about if the same node needs to be processed more than once. in this problem, it doesn't,
        so we check if each node has been processed before putting it into the BFS queue.
    */

    int n, k;
    cin >> n >> k;
    vector<int> p(n, -1);
    vector<vector<int>> children(n);
    vector<int> depth(n, 0);
    for (int i = 1; i < n; ++i) {
        int pi;
        cin >> pi;
        --pi;
        p[i] = pi;
        children[pi].push_back(i);
        depth[i] = depth[pi] + 1;
    }

    vector<int> sorted_by_depth(n);
    for (int i = 0; i < n; ++i) sorted_by_depth[i] = i;
    sort(sorted_by_depth.begin(), sorted_by_depth.end(), [&](int a, int b) { return depth[a] > depth[b]; });

    int l = 1, r = n - 1, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (num_ops(p, children, depth, sorted_by_depth, m) <= k) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << endl;
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
