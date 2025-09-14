class Solution {
private:
    void dfs(
        int node,
        int parent,
        vector<vector<int>> &adj,
        vector<int> &num_nodes,
        vector<int> &sum_dists
    ) {
        num_nodes[node] = 1;
        for (int next : adj[node]) {
            if (next == parent) continue;

            dfs(next, node, adj, num_nodes, sum_dists);

            num_nodes[node] += num_nodes[next];
            sum_dists[node] += num_nodes[next] + sum_dists[next];
        }
    }

    void dfs2(
        int node,
        int parent,
        vector<vector<int>> &adj,
        vector<int> &num_nodes,
        vector<int> &sum_dists,
        vector<int> &final_dists
    ) {
        for (int next : adj[node]) {
            if (next == parent) continue;

            // traverse
            num_nodes[node] -= num_nodes[next];
            sum_dists[node] -= sum_dists[next] + num_nodes[next];
            num_nodes[next] += num_nodes[node];
            sum_dists[next] += sum_dists[node] + num_nodes[node];

            // process
            final_dists[next] = sum_dists[next];
            dfs2(next, node, adj, num_nodes, sum_dists, final_dists);

            // backtrack
            sum_dists[next] -= sum_dists[node] + num_nodes[node];
            num_nodes[next] -= num_nodes[node];
            sum_dists[node] += sum_dists[next] + num_nodes[next];
            num_nodes[node] += num_nodes[next];
        }
    }

public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        for (const vector<int> &edge : edges) {
            int a = edge[0], b = edge[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> num_nodes(n, 0), sum_dists(n, 0);
        dfs(0, -1, adj, num_nodes, sum_dists);

        vector<int> final_dists(n, 0);
        final_dists[0] = sum_dists[0];
        dfs2(0, -1, adj, num_nodes, sum_dists, final_dists);
        return final_dists;
    }
};
