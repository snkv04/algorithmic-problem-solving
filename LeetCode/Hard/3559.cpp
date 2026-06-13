#include <bits/stdc++.h>
using namespace std;

class Solution {
    const int LOGMAXN = 17;
    vector<vector<int>> adj;
    vector<vector<int>> anc;
    vector<int> depth;

    void dfs(int node, int parent) {
        anc[0][node] = parent;
        for (int i = 1; i <= LOGMAXN; ++i) {
            int halfway = anc[i - 1][node];
            if (halfway != -1) {
                anc[i][node] = anc[i - 1][halfway];
            }
        }

        for (int next : adj[node]) {
            if (next == parent) continue;

            depth[next] = depth[node] + 1;
            dfs(next, node);
        }
    }

    int jump(int node, int k) {
        if (k > depth[node]) return -1;

        for (int i = LOGMAXN; i >= 0; --i) {
            if ((k >> i) & 1) {
                node = anc[i][node];
            }
        }
        return node;
    }

    int dist(int a, int b) {
        if (depth[a] > depth[b]) swap(a, b);

        int diff = depth[b] - depth[a];
        b = jump(b, diff);
        if (a == b) return diff;

        int ans = diff;
        for (int i = LOGMAXN; i >= 0; --i) {
            if (anc[i][a] != anc[i][b]) {
                a = anc[i][a];
                b = anc[i][b];
                ans += 1 << (i + 1);
            }
        }
        ans += 2;
        return ans;
    }

public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        adj = vector<vector<int>>(n);
        for (int i = 0; i < n - 1; ++i) {
            int a = edges[i][0] - 1, b = edges[i][1] - 1;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        anc = vector<vector<int>>(LOGMAXN + 1, vector<int>(n, -1));
        depth = vector<int>(n, 0);
        dfs(0, -1);

        vector<int> pow2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % static_cast<int>(1e9 + 7);
        }

        int q = queries.size();
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            int u = queries[i][0], v = queries[i][1];
            if (u == v) {
                ans[i] = 0;
            } else {
                --u; --v;
                int len = dist(u, v);
                ans[i] = pow2[len - 1];
            }
        }
        return ans;
    }
};
