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

void dfs(int node, vector<vector<int>> &adj, vector<int> &subtree_sizes) {
    // computes the subtree sizes
    int size = 1;
    for (int next : adj[node]) {
        dfs(next, adj, subtree_sizes);
        size += subtree_sizes[next];
    }
    subtree_sizes[node] = size;
}

void shift_up(int node, vector<vector<int>> &adj, int shift, vector<int> &a) {
    // jumps all values in the subtree up by shift
    a[node] += shift;
    for (int next : adj[node]) {
        shift_up(next, adj, shift, a);
    }
}

void bump_up(int node, vector<vector<int>> &adj, int threshold, vector<int> &a) {
    // bumps all values in the subtree up by 1 if they're >= threshold
    if (a[node] >= threshold) a[node] += 1;
    for (int next : adj[node]) {
        bump_up(next, adj, threshold, a);
    }
}

void dfs2(int node, vector<vector<int>> &adj, vector<int> &subtree_sizes, vector<int> &a, vector<int> &c) {
    // all of the children's subtrees have values starting from 0; shift them up so that the values in the
    // entire subtree are contiguous
    int start = 0;
    for (int next : adj[node]) {
        dfs2(next, adj, subtree_sizes, a, c);
        shift_up(next, adj, start, a);
        start += subtree_sizes[next];
    }

    // choose a split point based on c[node], and push the values in the subtree apart to place that split down
    // into a[node].
    for (int next : adj[node]) {
        bump_up(next, adj, c[node], a);
    }
    a[node] = c[node];
}

void solve() {
    /*
    - generalized ideas for the future:
        - when writing recursive functions, determine the post-condition (what can we assume to be true after this function
        terminates?), assume that it's true after making each call to it (within that function's body), and think of how to
        make it true at the end of the function body.
    */

    // reads in input and constructs tree
    int n;
    cin >> n;
    vector<vector<int>> children(n);
    vector<int> c(n);
    int root;
    for (int i = 0; i < n; ++i) {
        int pi;
        cin >> pi >> c[i];
        --pi;
        if (pi < 0) root = i;
        else children[pi].push_back(i);
    }

    // gets all subtree sizes and checks if any c[i] violates the subtree sizes
    vector<int> subtree_sizes(n);
    dfs(root, children, subtree_sizes);
    for (int i = 0; i < n; ++i) if (c[i] >= subtree_sizes[i]) { cout << "NO\n"; return; }

    // performs the O(n^2) shifting logic. in other words, recursively places down a[i] values, shifting around the
    // a[j] values in the subtree.
    // basically, for any given subtree, at the time right before the root R is processed, its nodes should have values
    // in the range [0, subtree_size(R) - 2] in some permutation. if we want the root R to have c[R] nodes X in its subtree
    // whose value a[X] is < a[R], then we can place a[R] := c[R], and then shift the values within the subtree up to accommodate
    // this. (this logic also works if we arbitrarily decide whether to shift nodes' values up or down; the overall interval just
    // needs to be contiguous, and it doesn't matter if both ends are nonnegative or not. basically, instead of splitting up
    // floating-point intervals and the distances between adjacent points can keep getting smaller and smaller, we use only
    // integers and enforce that the distances remain integers, exactly 1, by placing down each point and pushing the points
    // on either side of it away.)
    vector<int> a(n, -1);
    dfs2(root, children, subtree_sizes, a, c);
    cout << "YES\n";
    for (int i = 0; i < n; ++i) cout << a[i] + 1 << ' ';
    cout << '\n';
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
