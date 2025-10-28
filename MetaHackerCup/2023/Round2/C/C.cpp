#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
// const int MAXN = 1e6+5;
// vector<int> adj[MAXN];
vector<vector<int>> adj;
vector<unordered_set<string>> words;
int leaves;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

// void dfs_recursive(int node) {
//     while (adj[node].size() == 1) {
//         int child = adj[node][0];
//         adj[node] = adj[child];
//         adj[child].clear();
//         for (string w : words[child]) {
//             words[node].insert(w);
//         }
//         words[child].clear();
//     }

//     if (adj[node].empty()) {
//         ++leaves;
//         return;
//     }

//     for (int next : adj[node]) {
//         dfs_recursive(next);
//     }
// }

void dfs_iterative(int node) {
    stack<int> stk;
    stk.push(node);
    while (stk.size()) {
        int top = stk.top();
        stk.pop();

        while (adj[top].size() == 1) {
            int child = adj[top][0];
            adj[top] = adj[child];
            adj[child].clear();
            for (string w : words[child]) {
                words[top].insert(w);
            }
            words[child].clear();
        }

        if (adj[top].empty()) {
            ++leaves;
        } else {
            for (int next : adj[top]) {
                stk.push(next);
            }
        }
    }
}

int dfs2(int node, string &word) {
    if (adj[node].size() == 0) {
        if (words[node].find(word) == words[node].end()) {
            return 0;
        } else {
            return 1;
        }
    }

    int numchildren = adj[node].size();
    int numfound = 0;
    for (int child : adj[node]) {
        int result = dfs2(child, word);
        if (result == -1) {
            return -1;
        } else {
            numfound += result;
        }
    }

    if (numfound == numchildren) {
        return 1;
    } else if (numfound < numchildren - 1) {
        return -1;
    } else {
        if (words[node].find(word) == words[node].end()) {
            return 0;
        } else {
            return 1;
        }
    }
}

void solve() {
    /*
    - in general, it's clear that we want to minimize the number of paths. this is so that an instance
    of a word can propagate through the path for as long as possible before another instance of the word
    is required for a new path. if a node has 1 child, then there's no point in having a break in the path
    between that node and the child; just have one continuous path going through them. if a node has > 1
    child, there's no point in having a break for all the children; just have one of the children's path
    go through the node as well. this part was clear; the obvious corollary that i missed was that, doing
    this is equivalent to saying "every path has its bottom end on a leaf", so then the number of paths
    is equal to the number of leaves.
    - as a result of the above observation that there's no point in breaking a path somewhere in the middle
    of a path from a node to a leaf unless it's required, we can notice that long chains of nodes with no
    other children can be condensed as a preprocessing step. this part is intuitive and i figured it seemed
    like a generally good idea so that we can process fewer nodes later, but in this problem, it is actually
    required. why? it makes it so that the number of nodes is on the order of the number of leaves; namely,
    by forcing each node to either be a leaf or have >= 2 children, it ensures that N < 2*L. this is useful
    for the below analysis
    - if we naively check each word, using the logic of "number of child subtrees holding the word needs to
    be enough" that's given in dfs2() above, then it's O(N * M).
    however, we can impose a simple, dumb filter that literally improves the time complexity, and by a
    significant amount.
    we know that the word has to be in each path, and there are L (where L = # of leaves) paths, so each
    word must show up across the whole tree at least L times. therefore, we can only check those words that
    show up at least L times, which cuts down the number of words that we end up checking from sum(M_i)
    to sum(M_i) / L.
    also, the time needed to check each word, if we perform the path compression, is still O(N), but by
    doing the compression, O(N) is a subset of O(L).
    as a result, our time complexity gets cut down from O(M * N), which is too slow, to O(M / L * L) = O(M),
    which fits under the time limit. put simply, the number of things that we check gets cut down, and the
    time needed to check each also gets cut down. the core idea here is that even by doing a simple, dumb
    filter like that, which is not sufficient but absolutely necessary, there's a large speedup. since each
    element needs to show up L times, instead of checking all M words, we only look at M/L.

    generalizable ideas for the future:
    - when checking each element in some set to see if it meets some condition, see if they can be filtered
    out before doing the thorough checking. it might end up being true that the number of things that pass
    the filter is not just an arbitrary number but can literally be of a different time complexity than the
    total number of things.
    - to find these filters, think of conditions that are not sufficient but necessary for an element to
    meet the more in-depth condition.
    - by removing the nodes that aren't either a leaf or have multiple children, we make our tree into at
    least a binary tree (where "at least" refers to the number of children per node). the benefit, then,
    of doing this path compression is that we can therefore meet the conditions to apply the Full Binary
    Tree Theorem, which basically puts the number of nodes into the same complexity class as the number
    of leaves.
    - when thinking about the concept of paths from the root of a tree, see if the concept of leaves in a
    tree is relevant, because paths of interest often go from leaves to the root.
    */

    int n;
    cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 1; i < n; ++i) {
        int pi;
        cin >> pi;
        --pi;
        adj[pi].push_back(i);
    }
    words = vector<unordered_set<string>>(n);
    for (int i = 0; i < n; ++i) {
        int mi;
        cin >> mi;
        while (mi--) {
            string s;
            cin >> s;
            words[i].insert(s);
        }
    }
    leaves = 0;
    dfs_iterative(0);
    // for (int i = 0; i < n; ++i) {
    //     cout << "adj[" << i << "] = ";
    //     for (int node : adj[i]) cout << node << " ";
    //     cout << endl;
    // }

    map<string, int> candidates;
    for (int i = 0; i < n; ++i) {
        for (string s : words[i]) {
            candidates[s] += 1;
        }
    }

    int ans = 0;
    for (const pair<string, int> &entry : candidates) {
        if (entry.second < leaves) {
            continue;
        }

        string word = entry.first;
        if (dfs2(0, word) == 1) {
            ++ans;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
