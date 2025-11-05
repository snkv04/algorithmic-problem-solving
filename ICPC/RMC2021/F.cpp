#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int n, smax;
vector<vector<int>> adj, children;
vector<int> weight, val;
vector<vector<bool>> possible;
vector<vector<int>> knapsack;
vector<bool> visited;

void merge_knapsacks(
    vector<bool> &p1, vector<int> &k1, vector<bool> &p2, vector<int> &k2
) {
    vector<bool> p3 = p1;
    vector<int> k3 = k1;
    for (int i = 0; i < k1.size(); ++i) {
        if (p1[i]) {
            for (int j = 0; j < k2.size() && i+j < k1.size(); ++j) {
                if (p2[j]) {
                    p3[i+j] = true;
                    k3[i+j] = max(k3[i+j], k1[i] + k2[j]);
                }
            }
        }
    }
    p1 = p3;
    k1 = k3;
}

void dfs(int node) {
    visited[node] = true;
    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next);
            children[node].push_back(next);
        }
    }
}

void dfs2(int node) {
    for (int child : children[node]) {
        dfs2(child);
    }

    // consider using this node
    vector<bool> possible2(smax+1, false);
    vector<int> knapsack2(smax+1, 0);
    possible2[0] = true;
    if (weight[node] <= smax) {
        possible2[weight[node]] = true;
        knapsack2[weight[node]] = val[node];
    }

    // consider grandchildren
    for (int child : children[node]) {
        for (int gc : children[child]) {
            merge_knapsacks(possible2, knapsack2, possible[gc], knapsack[gc]);
        }
    }

    // without using either this node or its grandchildren, consider child
    possible[node][0] = true;
    for (int child : children[node]) {
        merge_knapsacks(possible[node], knapsack[node], possible[child], knapsack[child]);
    }

    // merge all results
    for (int i = 0; i <= smax; ++i) {
        possible[node][i] = possible[node][i] || possible2[i];
        knapsack[node][i] = max(knapsack[node][i], knapsack2[i]);
    }
}

int main() {
    /*
    generalizable ideas for the future:
    - we are doing a knapsack DP problem on every node in the tree.
    - normally, if we have a knapsack, then we maintain an array saying the max value for each weight, and then
    for each item that we are able to use, we check every possible weight sum that could happen if it's used and
    get the max value. we do this loop backward to ensure that the item isn't used multiple times. if we have a
    knapsack saying the max value for each weight, and we want to try merging another knapsack saying the max value
    for each weight using a different set of items, then we can't just loop backward because the primary problem
    (of using the same item more than once) can still occur. therefore, we create a new knapsack array to apply all
    of our updates to, and don't merge it into our main knapsack array until all possible ways to use that other
    set of items (considering all possible starting positions of using 0 elements, and therefore 0 weight, from the
    other set of items) have been processed. in other words, we separate it into an old knapsack and new knapsack,
    where the old is used for reading and the new is used for writing, and update the old with the new at the end.
    - this problem also involves the idea of not using any adjacent nodes in a tree, and optimizing something using
    DP under that constraint. so, for each node, if we want to get the maximum value for each weight by using items
    in that subtree, then we compute separately the max value per weight of (using this node and none of its children,
    only its grandchildren) and of (using only the children but not using this node). then, afterward, we can get
    the max value per each weight across both of these. why can we just directly merge these two resulting arrays?
    the important part is that for each weight, the value that we get can't violate any of the constraints (no item,
    or in this case node, can be used more than once as is classical in knapsack DP, and a node cannot use both
    itself and its children). so, we can directly merge these two knapsack arrays because we want, for each node,
    to say the max value per weight when using nodes in that node's subtree, and under that definition, we can
    calculate it the way we did (at a high level making sure not to use results from adjacent nodes, and at a low
    level making sure to merge knapsacks correctly).
    */

    cin >> n >> smax;
    weight = vector<int>(n);
    val = vector<int>(n);
    for (int i = 0; i < n; ++i) {
        cin >> weight[i] >> val[i];
    }
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    visited = vector<bool>(n, false);
    children = vector<vector<int>>(n);
    dfs(0);
    // for (int i = 0; i < n; ++i) {
    //     cout << "children[" << i << "] = ";
    //     for (int child : children[i]) cout << child << " ";
    //     cout << endl;
    // }
    possible = vector<vector<bool>>(n, vector<bool>(smax+1, false));
    knapsack = vector<vector<int>>(n, vector<int>(smax+1, 0));
    dfs2(0);
    int ans = 0;
    for (int i = 0; i <= smax; ++i) {
        if (possible[0][i]) ans = max(ans, knapsack[0][i]);
    }
    cout << ans << endl;
}
