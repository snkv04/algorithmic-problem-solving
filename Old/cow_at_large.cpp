#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

const int MAXN = 100005;
vector<int> adj[MAXN];
int depth[MAXN];
int mldis[MAXN]; // min leaf-depth in subtree
int ans[MAXN];

void dfs(int node, int parent, int d) {
    depth[node] = d;
    int mindepth = 1e9;
    for (int next : adj[node]) {
        if (next == parent) {
            continue;
        }

        dfs(next, node, d + 1);
        mindepth = min(mindepth, mldis[next]);
    }

    if (mindepth == 1e9) {
        mindepth = depth[node];
    }
    mldis[node] = mindepth;
}

void dfs2(int node, int parent) {
    if (mldis[node] - depth[node] <= depth[node]) {
        ans[node] = 1;
        return;
    }

    int sum = 0;
    for (int next : adj[node]) {
        if (next == parent) {
            continue;
        }

        dfs2(next, node);
        sum += ans[next];
    }
    // if (sum == 0) {
    //     sum = 1;
    // }
    ans[node] = sum;
}

void solve() {
    ifstream fin("atlarge.in");
    ofstream fout("atlarge.out");

    int n, k;
    fin >> n >> k;
    --k;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        fin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (adj[k].size() == 1) {
        fout << "1\n";
        return;
    }

    dfs(k, -1, 0);
    dfs2(k, -1);

    fout << ans[k] << "\n";
}

int main() {
    /**
     * first, the maximum number of farmers needed to catch bessie is just the number
     * of leaves in the graph. however, there are some cases in which one leaf is very
     * close to the path that bessie takes to other leaves, and a farmer starting on
     * that single leaf can stop bessie from going anywhere in whole portions of the
     * tree, which we can treat as subtrees by rooting the tree at bessie's
     * starting location. we can then treat this as a dp problem. how can a farmer
     * block bessie's path to any exits? given any node, if a farmer (starting from
     * a leaf) has a shorter shortest path to that node than bessie, then bessie
     * cannot go anywhere into the subtree without first being caught. so, we can just
     * calculate the depths of each node as well as the minimum depth of a leaf node
     * within each subtree, using those minimum depths to cut off bessie from reaching
     * into deeper within the subtree. if bessie can go past the root of a subtree,
     * then the number of farmers needed to prevent bessie from reaching any exits
     * within that subtree is just the sum of the answers for each child of the root
     * of that subtree. the base case is, again, when bessie can't go further
     * into the subtree (and all leaves are contained in this case).
     */

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
