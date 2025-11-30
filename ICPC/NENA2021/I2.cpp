#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, adj2;
vector<int> pre, low, scc, pre2;
vector<vector<int>> comps;
vector<bool> onstack;
stack<int> stk;
int timer;
vector<set<int>> reachable;
string ans;

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const set<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

void dfs(int node) {
    pre[node] = low[node] = timer++;
    stk.push(node);
    onstack[node] = true;

    for (int next : adj[node]) {
        if (pre[next] == -1) dfs(next);

        if (onstack[next]) low[node] = min(low[node], low[next]);
    }

    if (pre[node] == low[node]) {
        while (true) {
            int top = stk.top();
            stk.pop();
            onstack[top] = false;
            scc[top] = node;
            comps[node].push_back(top);

            if (node == top) return;
        }
    }
}

void dfs2(int node, int root) {
    reachable[root].insert(node);
    pre2[node] = 1;
    for (int next : adj2[node]) {
        if (!pre2[next]) {
            dfs2(next, root);
        }
    }
}

void dfs3(int node) {
    // cout << "on node " << node << endl;
    pre[node] = 1;
    if (ans[node / 2] == ' ') {
        // cout << "empty for node " << node << endl;
        if (node % 2) {
            ans[node / 2] = 'F';
        } else {
            ans[node / 2] = 'T';
        }
    }

    for (int next : adj[node]) {
        if (!pre[next]) dfs3(next);
    }
}

void solve() {
    /*
    generalizable ideas for the future:
    - if we just want to find some assignment that meets the constraints, then we can just check for each
    variable if true implies false or false implies true. however, what we're doing in this problem is, among
    all the assignments that meet the constraints, we want to select a specific one. so, what we can do is
    first assign the variables that MUST follow some assignment due to constraints (true is reachable from
    false or vice versa). then, for the free variables, we can assign them according to our desired scheme
    AS LONG AS all direct or indirect implication paths are met. we can do this by DFSing whenever a variable
    is assigned, and assigning all unassigned variables on the way during the DFS.
        - a quick note: suppose A and notA are such that neither implies the other, but in one DFS, A is reached,
        then in a later DFS, notA is reached. by keeping track of the assignment of the variable A itself (as either
        a true or false flag, which can straightforwardly be accessed through either the "true" node or "false" node),
        we only assign that variable once because we can check if it's already assigned by the time we process
        the other node.
    - feel free to modify standard algorithms to fit a problem as much as you want. every problem is an
    ad-hoc problem.
    */

    int n, k;
    cin >> n >> k;
    adj.resize(2*k);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int p = 0; p < k; ++p) {
            for (int q = p+1; q < k; ++q) {
                if (s[p] != 'X' && s[q] != 'X') {
                    bool val1 = s[p] == 'F', val2 = s[q] == 'F';

                    // 2*idx = true, 2*idx+1 = false
                    int idx1 = 2 * p + (!val1), idx2 = 2*q + (!val2);
                    adj[idx1 ^ 1].push_back(idx2);
                    adj[idx2 ^ 1].push_back(idx1);
                    // cout << "edge from " << (idx1^1) << " to " << idx2 << endl;
                    // cout << "edge from " << (idx2^1) << " to " << idx1 << endl;
                }
            }
        }
    }

    timer = 0;
    pre = vector<int>(2*k, -1);
    low = vector<int>(2*k, -1);
    onstack = vector<bool>(2*k, false);
    scc = vector<int>(2*k, -1);
    comps.resize(2*k);
    for (int i = 0; i < 2*k; ++i) {
        if (pre[i] == -1) {
            dfs(i);
        }
    }
    // cout << "scc = " << scc << endl;

    for (int i = 0; i < k; ++i) {
        if (scc[2*i] == scc[2*i+1]) {
            cout << "-1\n";
            return;
        }
    }

    adj2.resize(2*k);
    for (int i = 0; i < 2*k; ++i) {
        for (int next : adj[i]) {
            if (scc[i] != scc[next]) {
                adj2[scc[i]].push_back(scc[next]);
            }
        }
    }
    reachable = vector<set<int>>(2*k);
    pre = vector<int>(2*k, 0);
    for (int i = 0; i < 2*k; ++i) {
        if (pre[scc[i]] == 0) {
            pre[scc[i]] = 1;
            pre2 = vector<int>(2*k, 0);
            dfs2(scc[i], scc[i]);
        }
    }
    // for (int i = 0; i < 2*k; ++i) {
    //     cout << "reachable["<<i<<"] = " << reachable[i] << endl;
    // }

    ans = string(k, ' ');
    for (int i = 0; i < k; ++i) {
        int a = scc[2*i], b = scc[2*i+1];
        if (reachable[a].find(b) != reachable[a].end()) {
            ans[i] = 'F';
        } else if (reachable[b].find(a) != reachable[b].end()) {
            ans[i] = 'T';
        }
    }
    pre = vector<int>(2*k, 0);
    for (int i = 0; i < k; ++i) {
        if (ans[i] == 'F') {
            if (!pre[2*i+1]) dfs3(2*i+1);
        } else if (ans[i] == 'T') {
            if (!pre[2*i]) dfs3(2*i);
        } else {
            ans[i] = 'F';
            dfs3(2*i+1);
        }
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
