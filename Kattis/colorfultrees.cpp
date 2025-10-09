#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

vector<int> color;
unordered_map<int, int> total_freqs;
vector<vector<pair<int, int>>> adj;
vector<ll> subtree_ans;
vector<unordered_map<int, int>> subtree_freqs;
vector<ll> ans;

void dfs(int node, int parent, int edge) {
    /*
    generalizable ideas:
    - okay, so when we're processing the current node, we initialize the node's color frequency map
    to just be itself and, more interestingly, we initialize the subtree ans value for this node to
    just be 1 * (total_freqs[color[node]] - 1). why? well, why does this seem odd? because we're only
    counting the color of the node itself, and none of the other nodes in the subtree. however, this
    is actually a good idea, because this makes it so that the node itself and all of its child subtrees
    are logically treated as the same, so that if one is swapped for the other, then all of the same
    logic applies. namely, the "logic" i'm referring to is that the subtree answer (number of pairs
    crossing the edge, as described in the problem) and the subtree's frequency map for any given node
    n specifically deal with nodes in node n's subtree, and the current node's "subtree" before integrating
    all of the child nodes is literally just the node itself. THEREFORE, the "subtree" of the current
    node should be initialized to itself before integrating the child nodes' ACTUAL subtrees, because
    that makes the two sets of nodes (and corresponding frequency maps) symmetric for use cases such as
    swapping.
    - there is a bijective mapping between non-full-tree subtrees and edges.
    - when doing a postorder dfs like this, the two common ways of dealing with it are returning the
    child subtree's answer as the output of the dfs, and storing each subtree's answer in a global
    array. in this case, we choose the latter, due to ease of implementation (because otherwise, we'd
    need to return two things: the scalar count of subtree pairs and the subtree's color frequency map).
    - if computing some scalar value, like an integer or long long, based on the entries in a set or map,
    and we are frequently updating the entries in the map, then we can lazily update the scalar value based
    only on the entries that are being changed in the map. in the code, this lazy update is represented by
    subtracting the number of pairs that were contributed by the color entry that is being changed, updating
    the color entry, then adding the number of pairs contributed by the new color entry.
    - when storing all answers to queries in an array like this, if the answers can each be long longs, then
    when iterating over the answers while printing them out, MAKE SURE that the iteration variable in the
    for-each loop is a long long and NOT an int
    */

    // initialize information for this subtree
    subtree_ans[node] = total_freqs[color[node]] - 1;  // each subtree (except the whole tree) corresponds to an edge
    subtree_freqs[node][color[node]] = 1;

    // iterate through edges
    for (pair<int, int> next : adj[node]) {
        // skip the backward edge
        if (next.first == parent) continue;

        // process the full child subtree first
        dfs(next.first, node, next.second);

        // swap this node's "subtree" (the node itself and all previously-processed child subtrees)
        // with this child's subtree if the map for the child has more entries (i.e., small-to-large
        // merging)
        if (subtree_freqs[node].size() < subtree_freqs[next.first].size()) {
            std::swap(subtree_freqs[node], subtree_freqs[next.first]);
            std::swap(subtree_ans[node], subtree_ans[next.first]);
        }
        
        // update the color frequency map, as well as updating the pair count. the pair count is
        // LAZILY updated only every time an entry is merged into this subtree's information, because
        // otherwise, we'd have to compute the number of pairs based on up to N entries for each of the
        // N nodes, which is too slow
        for (const pair<int, int> color_freq : subtree_freqs[next.first]) {
            int color = color_freq.first, freq = color_freq.second;
            if (subtree_freqs[node].find(color) != subtree_freqs[node].end()) {
                subtree_ans[node] -= (ll) subtree_freqs[node][color] * (ll) (total_freqs[color] - subtree_freqs[node][color]);
            }
            subtree_freqs[node][color] += freq;
            subtree_ans[node] += (ll) subtree_freqs[node][color] * (ll) (total_freqs[color] - subtree_freqs[node][color]);
        }
    }

    // set answer for edge corresponding to this subtree
    if (edge != -1) {
        ans[edge] = subtree_ans[node];
    }
}

void solve() {
    int n;
    cin >> n;

    color.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> color[i];
        total_freqs[color[i]] += 1;
    }

    adj.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(make_pair(b, i));
        adj[b].push_back(make_pair(a, i));
    }

    subtree_ans.resize(n);
    subtree_freqs.resize(n);
    ans.resize(n-1);
    dfs(0, -1, -1);
    for (ll num : ans) cout << num << "\n";
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
