#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXN = 500005;
vector<int> adj[MAXN];

void dfs(int node, vector<int> &visited, vector<int> &depth, vector<int> &maxdepths) {
    visited[node] = true;
    int maxdepth = depth[node];
    for (int next : adj[node]) {
        if (!visited[next]) {
            depth[next] = depth[node] + 1;
            dfs(next, visited, depth, maxdepths);
            maxdepth = max(maxdepth, maxdepths[next]);
        }
    }
    maxdepths[node] = maxdepth;
}

void solve() {
    /*
    what's the goal here? we want to find the minimum operations of removing a leaf needed
    for all of the remaining leaves to be at the same depth. note that if a subtree is removed
    through this form of operations, then the number of operations needed is just equal to the
    number of nodes in that subtree, since each operation removes exactly one node and one
    edge. what's one way to brute-force this? we can look over all possible final depths of
    leaves, which there are at most n different values of and which have a max value of n (or
    n-1, depending on the definition of depth being used), and see the total number of nodes
    needed to be removed for that final depth. one important observation here is that it's
    obviously suboptimal to remove any more nodes than necessary, so for a given final depth,
    every single node that is at that level should be kept. the ones that are kept along with
    those are every ancestor of those, so the ones that are deleted are nodes with a depth
    greather than that depth and the nodes that are not ancestors of nodes at that depth.
    one key idea here is that we can, for a given final depth d, denote all the nodes that
    are kept as simply those with depth <= d whose subtrees reach down to a depth >= d; this
    considers all possible cases: every single node with depth d, those with depth < d who
    have descendants at depth d, those with depth < d who don't have descendants at depth d,
    and those with depth > d. now, we can reframe the problem: instead of iterating over d
    and finding how many nodes satisfy the not-deleting criteria for d and then taking the
    complement to find how many to delete, we can find the range of possible d values for
    each node (which, more generally, is just the set of d values that meets the not-deleting
    for that node) and see which value of d is in the most intervals. in other words, instead
    of iterating through many points and seeing for each how many intervals it's contained in,
    we can find which point is contained in the most intervals using the standard algorithm
    for "jumping" between endpoints of intervals; the original problem is just mapped onto
    this standard one, and this standard problem is solved efficiently by reframing it from
    iterating through points to iterating through the endpoints of intervals.

    why did i previously get stuck on one incorrect approach?
    just because it involves depths of nodes, i was thinking that i needed to iterate over
    depths of nodes (which i tried to do using bfs) instead of using the same concept of node
    depths in another way (which involves depths of nodes and max depths of subtrees rooted
    at each node).

    what's a key idea from this solution?
    - instead of viewing it as a problem of finding all nodes that remain in the tree for each
    given depth, we can reverse the perspective and find all depths that allow each node to
    remain in the tree. for a given node, if d is too small then the node will be too far
    down and will be part of the bottom portio of the tree that will be cut off, and if d
    is too large then the node doesn't have any descendant at level d that justifies it staying
    in the tree so then it will get pulled off.
    - instead of iterating over all values of x and seeing which elements from y satisfy
    the current x, first decide for each y which values of x it satisfies, then iterate through
    x by jumping between the endpoints of those intervals
    */

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> depth(n, 0), maxdepth(n, 0), visited(n, 0);
    depth[0] = 1;
    dfs(0, visited, depth, maxdepth);
    // for (int i = 0; i < n; ++i) {
    //     cout << "d[" << i << "] = " << depth[i] << ", maxd[" << i << "] = " << maxdepth[i] << "\n";
    // }
    
    map<int, pair<int, int>> intervals;
    for (int i = 0; i < n; ++i) {
        if (intervals.find(depth[i]) == intervals.end()) {
            intervals[depth[i]] = make_pair(0, 0);
        }
        if (intervals.find(maxdepth[i]) == intervals.end()) {
            intervals[maxdepth[i]] = make_pair(0, 0);
        }

        intervals[depth[i]].first += 1;
        intervals[maxdepth[i]].second += 1;
    }

    int ans = 0, curr = 0;
    for (const pair<int, pair<int, int>> &p : intervals) {
        curr += p.second.first;
        ans = max(ans, curr);
        curr -= p.second.second;
    }
    cout << n - ans << "\n";
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
