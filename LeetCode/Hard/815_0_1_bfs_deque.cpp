class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        // constructs the graph
        int n = 1e6, num_routes = routes.size();
        vector<vector<pair<int, int>>> adj(n + num_routes);
        for (int i = 0; i < routes.size(); ++i) {
            int route_idx = n + i;
            for (int bus : routes[i]) {
                adj[bus].push_back(make_pair(route_idx, 0));
                adj[route_idx].push_back(make_pair(bus, 1));
            }
        }

        // finds shortest path
        vector<int> dist(n + num_routes, 1e9);
        dist[source] = 0;
        deque<pair<int, int>> d;
        d.push_back(make_pair(source, 0));
        while (d.size()) {
            // processes the node
            auto [node, distance] = d.front();
            d.pop_front();
            if (distance > dist[node]) continue;

            // processes adjacent nodes
            for (auto [next, weight] : adj[node]) {
                if (distance + weight < dist[next]) {
                    dist[next] = distance + weight;
                    if (weight) {
                        d.push_back(make_pair(next, dist[next]));
                    } else {
                        d.push_front(make_pair(next, dist[next]));
                    }
                }
            }
        }
        return dist[target] == 1e9 ? -1 : dist[target];
    }
};
