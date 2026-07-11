#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<bool> visited;

    pair<int, int> dfs(
        int node,
        vector<bool> &visited,
        vector<vector<int>> &adj
    ) {
        pair<int, int> result = {1, 0};
        visited[node] = true;
        for (int next : adj[node]) {
            result.second += 1;
            if (!visited[next]) {
                pair<int, int> from_next = dfs(next, visited, adj);
                result.first += from_next.first;
                result.second += from_next.second;
            }
        }
        return result;
    }

public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        visited = vector<bool>(n, false);
        adj = vector<vector<int>>(n);
        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i][0], b = edges[i][1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                pair<int, int> p = dfs(i, visited, adj);
                if (p.second == p.first * (p.first - 1)) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};
