#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Comp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

int n;
vector<vector<int>> adj;
vector<int> mxnum, val;
vector<priority_queue<pair<int, int>, vector<pair<int, int>>, Comp>> best;

void dfs(int node) {
    for (int next : adj[node]) {
        mxnum[next] = min(mxnum[next], mxnum[node]);
        dfs(next);
    }
}

void dfs2(int node) {
    for (int next : adj[node]) {
        dfs2(next);
    }

    best[node].push(make_pair(node, val[node]));
    for (int next : adj[node]) {
        if (best[next].size() > best[node].size()) {
            swap(best[node], best[next]);
        }

        while (best[next].size()) {
            pair<int, int> top = best[next].top();
            best[next].pop();
            best[node].push(top);
        }
    }

    while (best[node].size() > mxnum[node]) {
        best[node].pop();
    }
}

void solve() {
    /*
    observations:
    - for a given node i, the value b_i states how many times a trade route can pass through it. in other words,
    the number of times that we can select a trade route's starting node from within node i's subtree is at most
    b_i.
        - as a result, we can make each node's b_i be the min of itself and all b_i's on the path from that node
        to the root, though this isn't strictly necessary in the solution.
    - if a node i is used as the start of a trade route, then all of the nodes from i to the root (inclusive) are
    used as well, so the b_i for all of those nodes are subsequently decreased by 1. if we want to reapply the min
    thing for all of those nodes' subtrees, then conceptually it would not be wrong to do so, but that would be
    too slow in the code.
        - by the way, this does NOT mean that the b_i is subtracted by 1 for all nodes in the subtree. that is
        literally a fake observation, and is wrong. to avoid being a dumbass and spreading misinformation in my
        own brain like i did during this contest, if i think that there is an example to support some claim or
        a counterexample to refute some claim, then draw out that concrete example on paper. i might just have
        been wrong.
    - ideally, if a node can select at most b_i nodes from its subtree, then we select the ones with highest
    value, as long as it obeys the constraints required from all subtrees within the subtree. however, if we know
    that we've already gotten the best nodes from all the child subtrees and followed their constraints, then we
    can just pick the best nodes from those (including the current node), making sure we don't exceed b_i for the
    current node i. this is basically the solution. we just speed up the priority queue merging with small-to-large
    merging.

    generalizable ideas for the future:
    - draw out concrete cases to visualize and verify my assumptions.
    - if we want to greedily take something from a subtree but this requires following the same constraints for
    all child subtrees of the current node's subtree, then just do postorder DFS. this makes sure that by the time
    we are getting values from the child subtrees, those values have already passed all the constraints of their
    entire subtrees, so we can just do a greedy algorithm from among those values.
    */

    cin >> n;
    adj.resize(n);
    for (int i = 1; i < n; ++i) {
        int pi;
        cin >> pi;
        --pi;
        adj[pi].push_back(i);
    }

    mxnum.resize(n);
    val.resize(n);
    for (int i = 0; i < 2*n; ++i) {
        int num;
        cin >> num;
        if (i < n) {
            mxnum[i] = num;
        } else {
            val[i-n] = num;
        }
    }

    dfs(0); // optional
    best.resize(n);
    dfs2(0);

    ll ans = 0;
    set<int> nodes;
    while (best[0].size()) {
        pair<int, int> top = best[0].top();
        best[0].pop();
        ans += top.second;
        nodes.insert(top.first);
    }
    cout << ans << endl;
    cout << nodes.size();
    for (int node : nodes) cout << " " << (node + 1);
    cout << endl;
}

int main() {
    solve();
    return 0;
}