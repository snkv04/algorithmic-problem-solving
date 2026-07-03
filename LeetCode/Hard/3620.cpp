#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int l = 0, r = 1e9, ans = -1, n = online.size();
        while (l <= r) {
            int m = (l + r) / 2;

            vector<vector<pair<int, int>>> adj(n);
            for (int i = 0; i < edges.size(); ++i) {
                int a = edges[i][0], b = edges[i][1], c = edges[i][2];
                if (c >= m) {
                    adj[a].push_back({b, c});
                }
            }

            vector<long long> dist(n, 1e18);
            dist[0] = 0;
            priority_queue<pair<long long, int>> pq;
            pq.push({0, 0});
            while (pq.size()) {
                auto [node_dist, node] = pq.top();
                pq.pop();
                node_dist *= -1;
                if (node_dist > dist[node]) continue;

                for (auto [next_node, weight] : adj[node]) {
                    if (
                        online[next_node] &&
                        dist[next_node] > dist[node] + weight
                    ) {
                        dist[next_node] = dist[node] + weight;
                        pq.push({-dist[next_node], next_node});
                    }
                }
            }

            if (dist[n - 1] <= k) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    }
};
