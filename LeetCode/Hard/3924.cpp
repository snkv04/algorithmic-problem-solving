class Solution {
public:
    int minimumThreshold(int n, vector<vector<int>>& edges, int source, int target, int k) {
        int l = 0, r = 1e9, ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            vector<vector<pair<int, int>>> adj(n);
            for (int i = 0; i < edges.size(); ++i) {
                int a = edges[i][0], b = edges[i][1], w = edges[i][2];
                adj[a].push_back({b, w > m});
                adj[b].push_back({a, w > m});
            }

            vector<int> dist(n, 1e9);
            dist[source] = 0;
            priority_queue<pair<int, int>> pq;
            pq.push({0, source});
            while (pq.size()) {
                auto [distance, node] = pq.top();
                distance *= -1;
                pq.pop();
                if (distance > dist[node]) continue;

                for (auto [next, weight] : adj[node]) {
                    if (dist[next] > dist[node] + weight) {
                        dist[next] = dist[node] + weight;
                        pq.push({-dist[next], next});
                    }
                }
            }

            if (dist[target] == 1e9) {
                return -1;
            }
            if (dist[target] <= k) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }
};
