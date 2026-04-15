#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n;
vector<int> a;
vector<vector<int>> adj;

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

int get_bit(int i, int b, const vector<int> &a) {
    return (a[i] >> b) & 1;
}

void dfs(
    int node,
    int parent,
    int b,
    vector<vector<ll>> &mem,
    vector<int> &ss,
    const vector<vector<int>> &adj,
    const vector<int> &a
) {
    int subtree = 1;
    int bit = get_bit(node, b, a);
    for (int next : adj[node]) {
        if (next == parent) continue;

        dfs(next, node, b, mem, ss, adj, a);
        subtree += ss[next];
        mem[node][bit] += mem[next][bit];
    }
    ss[node] = subtree;
    mem[node][bit ^ 1] = mem[node][bit] + ss[node];
}

void dfs2(
    int node,
    int parent,
    int b,
    vector<vector<ll>> &mem,
    vector<int> &ss,
    vector<ll> &bit_ans,
    const vector<vector<int>> &adj,
    const vector<int> &a
) {
    int bit = get_bit(node, b, a);
    bit_ans[node] = mem[node][bit];
    for (int next : adj[node]) {
        if (next == parent) continue;

        ss[node] -= ss[next];
        mem[node][bit] -= mem[next][bit];
        mem[node][bit ^ 1] = mem[node][bit] + ss[node];
        int next_bit = get_bit(next, b, a);
        ss[next] += ss[node];
        mem[next][next_bit] += mem[node][next_bit];
        mem[next][next_bit ^ 1] = mem[next][next_bit] + ss[next];

        dfs2(next, node, b, mem, ss, bit_ans, adj, a);

        // don't need to "reverse" the operations from before the DFS, necessarily.
        // only real rule to follow is to make everything logically correct.
        // value for (bit ^ 1) is just dependent on value for bit as well as subtree size,
        // and those 2 aren't dependent on each other. so, we can always update in (ss, mem for bit,
        // mem for opposite bit) order, and it's logically correct. if you want a general rule,
        // just draw it out and figure out the correct order of updates.
        ss[next] -= ss[node];
        mem[next][next_bit] -= mem[node][next_bit];
        mem[next][next_bit ^ 1] = mem[next][next_bit] + ss[next];
        ss[node] += ss[next];
        mem[node][bit] += mem[next][bit];
        mem[node][bit ^ 1] = mem[node][bit] + ss[node];
    }
}

void solve() {
    /*
    - useful ideas:
        - can completely separate costs across bits. what this means is that, given a fixed root, we can
        go through each bit and do our operations on various nodes, and the total cost sum is the same as
        if we went through each node and did our operations for all bits at once on each node.
        - the optimal strategy, given a fixed root, is a bottom-up strategy. since we change everything
        in the subtree at once, we don't even have to look at the nodes above the current subtree to tell
        what operations we need to perform on the nodes within the subtree.
        - when rerooting, we just need for all relevant values (for both node and next) to be updateable
        in O(1) using only the information from node and next.
            - it turns out that mem[node][bit ^ 1] is purely only dependent on mem[node][bit] and
            subtree_size[node]. therefore, when rerooting, it is possible that some of the values we update
            are literally just assigned, not incremented or decremented. interesting case. in other words,
            the best strategy to make the entire subtree into the opposite bit is to make the entire subtree
            into the current bit at the root of the subtree, then flip the entire subtree at once. why? because
            we have to make sure everything within the subtree already aligns with the root, since operations
            on the root will flip everything in the subtree as well. namely, if we want the entire subtree to
            have 1 but the root has 0, we can't let some subtrees remain 1; we make those subtrees into 0, then
            flip the entire subtree into 1, because we have to.
        - we can store an array representing the answers for the bit that we're currently on. it just
        makes things visually clearer and more modular to mentally parse. the "ans[i] += bit_ans[i] << b"
        logic is very intuitive and straightforward.
    */

    cin >> n;
    a.resize(n);
    cin >> a;
    adj.resize(n);
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // mem[i][j] := minimum cost sum to make subtree of node i all have value j in bit b,
    // where the definition of what nodes constitute the subtree will depend on the current root.
    vector<ll> ans(n, 0);
    vector<int> ss(n, 0);
    vector<vector<ll>> mem(n, vector<ll>(2, 0));
    vector<ll> bit_ans(n, 0);
    for (int b = 0; b < 20; ++b) {
        // gets subtree sizes and costs if tree is rooted at 0
        for (int i = 0; i < n; ++i) fill(mem[i].begin(), mem[i].end(), 0);
        fill(ss.begin(), ss.end(), 0);
        dfs(0, -1, b, mem, ss, adj, a);

        // reroots the tree to get all costs for this bit
        fill(bit_ans.begin(), bit_ans.end(), 0);
        dfs2(0, -1, b, mem, ss, bit_ans, adj, a);

        // adds costs for this bit to overall costs
        for (int i = 0; i < n; ++i) ans[i] += bit_ans[i] << b;
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    cout << "\n";
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
