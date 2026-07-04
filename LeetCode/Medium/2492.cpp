#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < roads.size(); ++i) {
            int a = roads[i][0], b = roads[i][1], c = roads[i][2];
            --a; --b;
            adj[a].push_back(make_pair(b, c));
            adj[b].push_back(make_pair(a, c));
        }

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        int ans = 1e9;
        while (q.size()) {
            int node = q.front();
            q.pop();
            if (visited[node]) continue;

            visited[node] = true;
            for (auto [next, weight] : adj[node]) {
                if (!visited[next]) {
                    q.push(next);
                    ans = min(ans, weight);
                }
            }
        }
        return ans;
    }
};
