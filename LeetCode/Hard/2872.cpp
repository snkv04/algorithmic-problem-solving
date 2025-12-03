class Solution {
    void dfs(
        int node,
        int parent,
        int &ans,
        vector<set<int>> &adj,
        vector<int> &values,
        int k
    ) {
        for (int next : adj[node]) {
            if (next == parent) continue;

            dfs(next, node, ans, adj, values, k);
            values[node] = (values[node] + values[next]) % k;
        }

        if (values[node] == 0) {
            ++ans;
            values[node] = 0;
        }
    }

public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<set<int>> adj(n);
        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i][0], b = edges[i][1];
            adj[a].insert(b);
            adj[b].insert(a);
        }

        for (int i = 0; i < n; ++i) {
            values[i] %= k;
        }
        
        int ans = 0;
        dfs(0, -1, ans, adj, values, k);
        return ans;
    }
};
