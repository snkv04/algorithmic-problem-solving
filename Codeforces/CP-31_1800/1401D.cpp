#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
vector<ll> path_counts;
int subtree_sizes[MAXN];

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

void dfs(int node, int parent, int n) {
    int size = 1;
    for (int next : adj[node]) {
        if (next == parent) continue;

        dfs(next, node, n);
        path_counts.push_back(1LL * subtree_sizes[next] * (n - subtree_sizes[next]));
        size += subtree_sizes[next];
    }
    subtree_sizes[node] = size;
}

void solve() {
    /*
    - problem:
        - we are given a large-ass number (by its prime factors) and a tree
        - we want to assign a weight to each edge in the tree such that the weights all multiply up to the
        given number, and the sum across {all pairs of nodes} of {the sum of weights on the path between
        that pair of nodes} is maximized
            - why did i use curly braces here? parentheses would be used for grouping up words that are
            unnecessary for the sentence and which form an appositive (or "parenthetical phrase"), and
            square brackets would be used for grouping up words that don't exist in an original quoted
            excerpt and are only inserted into the quote. here, i just wanted to delimit the phrases to
            make it easier to understand the high-level idea of what phrase maps to what part of the
            mathematical expression, so i just picked some delimiters
    - solution:
        - by rearranging the sum, we can find that we're trying to maximize the sum across {all edges} of
        {that edge's weight times the number of paths that edge is within}, so we can greedily assign
        high weights to high-frequency edges
        - for the weights, we can assign them in increasing order to edges, with excess factors assigned
        to the highest-frequency edge
        - for the path counts, we can assume each edge connects a subtree (where the tree is rooted) to the
        rest of the tree, and multiply the size of the subtree to the size of the rest of the tree
    - details:
        - why is it important that the number is given by its prime factors and not just regular factors
        that multiply up to the number? if we got regular factors of k, we would want to break k down into
        prime factors so that we could apportion as little as possible to the low-frequency edges. we are
        given the prime factorization of k, though, so we can skip that step
    */

    // reads in tree
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // gets the number of times each edge is included in a path, then sorts the edges by path inclusion count
    // implementation detail: sort BEFORE modding (so don't mod in DFS), to ensure correct arithmetic
    path_counts.clear();
    fill(subtree_sizes, subtree_sizes + n, 0);
    dfs(0, -1, n);
    sort(path_counts.begin(), path_counts.end());
    for (int i = 0; i < n-1; ++i) path_counts[i] %= MOD;

    // sort all the prime factors, and greedily assign as many factors as possible to the most
    // frequently-included-in-paths edges
    int m; cin >> m;
    vector<ll> p(m); cin >> p; sort(p.begin(), p.end());
    vector<ll> edges(n-1, 1);
    if (m < n-1) {
        for (int i = n-m-1; i < n-1; ++i) {
            edges[i] = p[i-(n-m-1)];
        }
    } else {
        for (int i = 0; i < n-1; ++i) {
            edges[i] = p[i];
        }
        for (int i = n-1; i < m; ++i) {
            edges[n-2] = (edges[n-2] * p[i]) % MOD;
        }
    }

    // multiply each edge's path count by its assigned weight
    ll ans = 0;
    for (int i = 0; i < n-1; ++i) {
        ans = (ans + path_counts[i] * edges[i]) % MOD;
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
