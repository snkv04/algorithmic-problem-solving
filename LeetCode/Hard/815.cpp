class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        vector<vector<int>> adj(1e6 + 505);
        for (int i = 0; i < routes.size(); ++i) {
            int route_idx = i + 1e6;
            for (int j = 0; j < routes[i].size(); ++j) {
                int bus = routes[i][j];
                adj[bus].push_back(route_idx);
                adj[route_idx].push_back(bus);
            }
        }

        vector<int> dist(1e6 + 505, 1e9);
        dist[source] = 0;
        queue<int> q;
        q.push(source);
        while (q.size()) {
            int node = q.front();
            q.pop();

            for (int next : adj[node]) {
                if (dist[next] > dist[node] + 1) {
                    dist[next] = dist[node] + 1;
                    q.push(next);
                }
            }
        }

        if (dist[target] == 1e9) return -1;
        else return dist[target] / 2;
    }
};
